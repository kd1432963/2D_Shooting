#include "GameScene.h"

#include"Application/Scene/SceneManager.h"

#include"Application/Scene/Result/ResultScene.h"

#include"Application/GameObject/HitBox.h"

#include"Application/Chara/Player.h"
#include"Application/Enemy/EnemyManager.h"
#include"Application/Enemy/EnemySpawner.h"
#include"Application/Bullet/BulletManager.h"
#include"Application/UI/UIManager.h"
#include"Application/Effect/EffectManager.h"
#include"Application/Collision/CollisionManager.h"
#include"Application/Item/ItemDropManager.h"
#include"WaveManager.h"

#include"Application/Effect/HitEffect/HitEffect.h"
#include"Application/Effect/ExplosionEffect/ExplosionEffect.h"

GameScene::GameScene()
{
	mp_player			= new Player();
	mp_enemyManager		= new EnemyManager();
	mp_enemySpawner		= new EnemySpawner();
	mp_bulletManager	= new BulletManager();
	mp_uiManager		= new UIManager();
	mp_effectManager	= new EffectManager();
	mp_itemDropManager	= new ItemDropManager();
	mp_waveManager		= new WaveManager();
}

GameScene::~GameScene()
{
	if (mp_player)
	{
		delete mp_player;
		mp_player = nullptr;
	}
	if (mp_enemyManager)
	{
		delete mp_enemyManager;
		mp_enemyManager = nullptr;
	}
	if (mp_enemySpawner)
	{
		delete mp_enemySpawner;
		mp_enemySpawner = nullptr;
	}
	if (mp_bulletManager)
	{
		delete mp_bulletManager;
		mp_bulletManager = nullptr;
	}
	if (mp_uiManager)
	{
		delete mp_uiManager;
		mp_uiManager = nullptr;
	}
	if (mp_effectManager)
	{
		delete mp_effectManager;
		mp_effectManager = nullptr;
	}
	if (mp_itemDropManager)
	{
		delete mp_itemDropManager;
		mp_itemDropManager = nullptr;
	}
	if (mp_waveManager)
	{
		delete mp_waveManager;
		mp_waveManager = nullptr;
	}
}

//+++++++++++++++++++++++++++++++++++++++++
// シーンができたときに一度だけ通る関数
//+++++++++++++++++++++++++++++++++++++++++
void GameScene::OnEnter()
{
	// 敵生成
	mp_enemySpawner->StartWave(1);

	// ホーミング用に登録
	mp_bulletManager->SetPlayer(mp_player);
	mp_bulletManager->SetEnemyManager(mp_enemyManager);

	m_score = 0;
}

//+++++++++++++++++++++++++++++++++++++++++
// シーンが終わるときに一度だけ通る関数
//+++++++++++++++++++++++++++++++++++++++++
void GameScene::OnExit()
{

}

//+++++++++++++++++++++++++++++++++++++++++
// シーンが最上位じゃなくなるときに一度だけ通る関数
//+++++++++++++++++++++++++++++++++++++++++
void GameScene::OnPause()
{

}

//+++++++++++++++++++++++++++++++++++++++++
// シーンが最上位に戻るときに一度だけ通る関数
//+++++++++++++++++++++++++++++++++++++++++
void GameScene::OnResume()
{

}

//+++++++++++++++++++++++++++++++++++++++++
// 更新処理（毎フレーム）
//+++++++++++++++++++++++++++++++++++++++++
void GameScene::Update()
{
	mp_waveManager->Update(*mp_enemyManager,*mp_enemySpawner);
	mp_enemySpawner->Update(*mp_enemyManager,mp_player);

	if (KEY.IsTrigger(VK_RETURN))
	{
		SCENE_MANAGER.RequestChange(std::make_unique<ResultScene>());
	}

	// プレイヤー行動決定
	mp_player->Action();

	// 玉発射
	if (mp_player->WantToShot())
	{
		mp_player->Shot(*mp_bulletManager);
	}

	// 敵行動決定
	mp_enemyManager->Action();

	mp_enemyManager->Shot(*mp_bulletManager);


	// 弾更新
	mp_bulletManager->Update();

	// アイテム更新
	mp_itemDropManager->Update();

	// 当たり判定
	CheckCollision();

	// エフェクト更新
	mp_effectManager->Update();

	// 死亡処理
	mp_bulletManager->DeleteDead();
	mp_itemDropManager->DeleteDead();

	// エネミーは消す前にエフェクトをたく
	for (auto& e : mp_enemyManager->GetEnemies())
	{
		if (e->IsDead())
		{
			auto effect = std::make_unique<ExplosionEffect>(e->GetPos());
			mp_effectManager->AddEffect(std::move(effect));
			m_score += 50;

			if (RandomChance(0.1f))
			{
				mp_itemDropManager->DropItemRandom(e->GetPos());
			}
		}
	}

	mp_enemyManager->DeleteDead();

	// UI 更新
	mp_uiManager->Update();

	// 敵更新
	mp_enemyManager->Update();

	// プレイヤー更新
	mp_player->Update();
}

//+++++++++++++++++++++++++++++++++++++++++
// 描画処理（毎フレーム）
//+++++++++++++++++++++++++++++++++++++++++
void GameScene::Draw2D()
{
	//=== 背景 ===========================================================================================
	static float x = 0;

	x -= 5;

	if (x <= -2560) x += 2560;

	Math::Matrix S = Math::Matrix::CreateScale(5.0f, 3.75f, 1.0f);
	Math::Matrix T = Math::Matrix::CreateTranslation(x, 0, 0);
	SHADER.m_spriteShader.SetMatrix(S * T);
	SHADER.m_spriteShader.DrawTex(ASSET.GetTexture("BackGround1"), ASSET.GetRectangle("BackGround1"));

	T = Math::Matrix::CreateTranslation(x + 1280, 0, 0);
	SHADER.m_spriteShader.SetMatrix(S * T);
	SHADER.m_spriteShader.DrawTex(ASSET.GetTexture("BackGround2"), ASSET.GetRectangle("BackGround2"));

	T = Math::Matrix::CreateTranslation(x + 2560, 0, 0);
	SHADER.m_spriteShader.SetMatrix(S * T);
	SHADER.m_spriteShader.DrawTex(ASSET.GetTexture("BackGround1"), ASSET.GetRectangle("BackGround1"));
	//===================================================================================================

	// 敵描画
	mp_enemyManager->Draw2D();

	// アイテム描画
	mp_itemDropManager->Draw2D();

	// 弾描画
	mp_bulletManager->Draw2D();

	// エフェクト描画
	mp_effectManager->Draw2D();

	// プレイヤー描画
	mp_player->Draw2D();

	// UI 描画
	mp_uiManager->Draw2D(m_score,mp_player->GetItemStockManager(),mp_player->GetItemRecast());

	//SHADER.m_spriteShader.DrawString(0, 0, "Game", Math::Vector4(1, 1, 1, 1));
}

//+++++++++++++++++++++++++++++++++++++++++
// デバッグ画面更新関数
//+++++++++++++++++++++++++++++++++++++++++
void GameScene::ImGuiUpdate()
{

}

//+++++++++++++++++++++++++++++++++++++++++
// 当たり判定呼び出し関数
//+++++++++++++++++++++++++++++++++++++++++
void GameScene::CheckCollision()
{
	CollisionManager::CheckAll(
		*mp_player,
		*mp_enemyManager,
		*mp_bulletManager,
		*mp_effectManager,
		*mp_itemDropManager,
		m_score
	);
}