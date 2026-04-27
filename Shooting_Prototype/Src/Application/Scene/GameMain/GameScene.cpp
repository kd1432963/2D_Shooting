#include "GameScene.h"

#include"Application/Scene/SceneManager.h"

#include"Application/Scene/Result/ResultScene.h"

#include"Application/GameObject/HitBox.h"

#include"Application/Enemy/EnemyManager.h"
#include"Application/Enemy/EnemySpawner.h"
#include"Application/Bullet/BulletManager.h"
#include"Application/UI/UIManager.h"

GameScene::GameScene()
{
	mp_enemyManager = new EnemyManager();
	mp_enemySpawner = new EnemySpawner();
	mp_bulletManager = new BulletManager();
	mp_uiManager = new UIManager();
}

GameScene::~GameScene()
{
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
}

//+++++++++++++++++++++++++++++++++++++++++
// シーンができたときに一度だけ通る関数
//+++++++++++++++++++++++++++++++++++++++++
void GameScene::OnEnter()
{
	// 敵生成
	mp_enemySpawner->SpawnWave1(*mp_enemyManager);

	// ホーミング用に登録
	mp_bulletManager->SetPlayer(&m_player);
	mp_bulletManager->SetEnemyManager(mp_enemyManager);
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
	if (KEY.IsTrigger('M'))
	{
		mp_enemySpawner->RandomSpawn(*mp_enemyManager);
	}

	if (KEY.IsTrigger(VK_SPACE))
	{
		SCENE_MANAGER.RequestChange(std::make_unique<ResultScene>());
	}

	// プレイヤー行動決定
	m_player.Action();

	// 玉発射
	if (m_player.WantToShot())
	{
		m_player.Shot(*mp_bulletManager);
	}

	// 敵行動決定
	mp_enemyManager->Action();

	mp_enemyManager->Shot(*mp_bulletManager);


	// 弾更新
	mp_bulletManager->Update();

	// 当たり判定
	CheckCollision();

	// 死亡処理
	mp_bulletManager->DeleteDead();
	mp_enemyManager->DeleteDead();

	// UI 更新
	mp_uiManager->Update();

	// 敵更新
	mp_enemyManager->Update();

	// プレイヤー更新
	m_player.Update();
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

	// UI 描画
	mp_uiManager->Draw2D();

	// 敵描画
	mp_enemyManager->Draw2D();

	// 弾描画
	mp_bulletManager->Draw2D();

	// プレイヤー描画
	m_player.Draw2D();

	SHADER.m_spriteShader.DrawString(0, 0, "Game", Math::Vector4(1, 1, 1, 1));
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
	//=== 弾 & 敵 =========================

	auto& bullets = mp_bulletManager->GetBullets();
	auto& enemies = mp_enemyManager->GetEnemies();

	for (auto& b : bullets)
	{
		if (b->GetOwner() != BulletOwner::Player)
		{
			if (b->GetHitBox().IsHit(m_player.GetHitBox()))
			{
				m_player.TakeDamage(b->GetAtk());
				b->SetDead();
			}
			continue;
		}

		for (auto& e : enemies)
		{
			if (b->GetHitBox().IsHit(e->GetHitBox()))
			{
				e->TakeDamage(b->GetAtk());
				b->SetDead();
			}
		}
	}

	//===  =========================
}