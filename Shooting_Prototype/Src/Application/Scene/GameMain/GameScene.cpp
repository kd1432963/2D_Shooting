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
#include"Application/Effect/AfterBurstEffect/AfterBurstEffect.h"

GameScene::GameScene()
{
	mp_player = std::make_shared<Player>();
	mp_enemyManager = new EnemyManager();
	mp_enemySpawner = new EnemySpawner("_Data/EnemyData/EnemySpawnDataNormal.csv");
	mp_bulletManager = new BulletManager();
	mp_uiManager = new UIManager();
	mp_effectManager = new EffectManager();
	mp_itemDropManager = new ItemDropManager();
	mp_waveManager = new WaveManager();
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
	mp_bulletManager->SetPlayer(mp_player.get());
	mp_bulletManager->SetEnemyManager(mp_enemyManager);

	// スコア初期化
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
	//--- 死んでたら --------------------------------------------------
	if (mp_player->IsDead())
	{
		Math::Vector2 pos = mp_player->GetPos();

		if (!m_deadAnimFlg)
		{
			mp_effectManager->AddEffect(std::make_unique<ExplosionEffect>(pos, true));
			m_deadAnimFlg = true;
		}
		mp_effectManager->Update();
		if (mp_effectManager->IsEmpty())
		{
			SCENE_MANAGER.RequestPush(std::make_unique<ResultScene>(m_score));
		}
		return;
	}

	//--- Boss Warning ------------------------------------------------
	if (mp_waveManager->IsBossWarning())
	{
		if (++m_warningTime == 300)
			mp_waveManager->SetBossStarted();
	}

	//--- Wave Update -------------------------------------------------
	if (mp_waveManager->Update(*mp_enemyManager, *mp_enemySpawner, mp_effectManager, mp_player.get()))
	{
		// 全滅ボーナス
		mp_effectManager->SpawnScoreEffect({ 0,0 }, 3000, "EnemyWipe");
		m_score += 3000;
	}

	//--- MidBoss Quick Kill Bonus -----------------------------------
	if (mp_enemyManager->IsMidBossAlive())
	{
		++m_MidBossAliveTime;
	}
	else if (m_MidBossAliveTime > 0)
	{
		int bonus = std::max(0, 5000 - std::max(0, (m_MidBossAliveTime - 500) * 3));
		if (bonus > 0)
		{
			mp_effectManager->SpawnScoreEffect({ -100,0 }, bonus, "QuickKill");
			m_score += bonus;
		}
		m_MidBossAliveTime = 0;
	}

	if (mp_enemyManager->IsBossAlive())
	{
		++m_bossAliveTime;
	}
	else if (m_bossAliveTime > 0)
	{
		int bonus = std::max(0, 50000 - std::max(0, (m_bossAliveTime - 7200) * 2));
		if (bonus > 0)
		{
			mp_effectManager->SpawnScoreEffect({ -150,100 }, bonus, "QuickKill");
			m_score += bonus;
		}
		m_bossAliveTime = 0;
	}

	//--- Enemy Spawner ----------------------------------------------
	mp_enemySpawner->Update(*mp_enemyManager, mp_player.get());

	//--- Scene Change ------------------------------------------------
	if (KEY.IsTrigger(VK_RETURN) ||
		(mp_waveManager->IsWaveAllClear() && mp_effectManager->IsEmpty()))
	{
		SCENE_MANAGER.RequestPush(std::make_unique<ResultScene>(777777));
	}

	//--- Player ------------------------------------------------------
	mp_player->Action();
	if (mp_player->WantToShot())
		mp_player->Shot(*mp_bulletManager);

	//--- Enemy -------------------------------------------------------
	mp_enemyManager->Action();
	mp_enemyManager->Shot(*mp_bulletManager);

	//--- Bullets / Items --------------------------------------------
	mp_bulletManager->Update();
	mp_itemDropManager->Update();

	//--- Collision ---------------------------------------------------
	CheckCollision();

	//--- Effects -----------------------------------------------------
	mp_effectManager->Update();

	//--- Cleanup -----------------------------------------------------
	mp_bulletManager->DeleteDead();
	mp_itemDropManager->DeleteDead();

	// 敵死亡処理（エフェクト・アイテム・スコア）
	for (auto& e : mp_enemyManager->GetEnemies())
	{
		if (e->IsDead())
		{
			++m_enemyKillCnt;

			Math::Vector2 pos = e->GetPos();
			int addScore = 100;

			mp_effectManager->AddEffect(std::make_unique<ExplosionEffect>(pos));
			mp_effectManager->AddEffect(std::make_unique<AfterBurstEffect>(pos));

			if (RandomChance(0.1f) || m_enemyKillCnt == 1 || m_enemyKillCnt % 12 == 0)
				mp_itemDropManager->DropItemRandom(pos);

			if (e->GetType() == EnemyType::Enemy2)
			{
				addScore = 1000;
				mp_itemDropManager->DropHealItem(pos);
			}
			if (e->GetType() == EnemyType::Boss)
			{
				addScore = 30000;
				mp_effectManager->SpawnScoreEffect(pos + Math::Vector2{ -150,200 }, addScore);
				m_score += addScore;
			}
			else
			{
				mp_effectManager->SpawnScoreEffect({ pos.x,pos.y - 30 }, addScore);
				m_score += addScore;
			}
		}

		// ホーミングターゲット解除
		if (e->IsDead() || e->IsSystemDead())
		{
			CharaBase* dead = e.get();
			for (auto& b : mp_bulletManager->GetBullets())
			{
				if (b->IsHoming() && b->GetTarget() == dead)
					b->ClearTarget();
			}
		}
	}

	mp_enemyManager->DeleteDead();

	//--- UI / Final Updates -----------------------------------------
	mp_uiManager->Update();
	mp_enemyManager->Update();
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

	mp_itemDropManager->Draw2D();
	mp_bulletManager->Draw2D();
	mp_enemyManager->Draw2D();
	mp_effectManager->Draw2D();
	mp_player->Draw2D();

	//--- UI ----------------------------------------------------------
	if (SCENE_MANAGER.GetTopScene() == this)
	{
		mp_uiManager->DrawGameUI(
			m_score,
			mp_player->GetItemStockManager(),
			*mp_player.get(),
			mp_waveManager->GetWave(),
			mp_waveManager->IsBossWarning()
		);
	}

	//--- Boss HP Bar -------------------------------------------------
	if (mp_enemyManager->IsMidBossAlive() || mp_enemyManager->IsBossAlive())
	{
		float alpha = 1.0f;

		// HP Bar Width
		int width = mp_enemyManager->IsMidBossAlive() ? 200 : 400;

		// 重なっていれば視認性のために透明度を下げる
		Math::Vector2 p = mp_player->GetPos();
		if (p.x > -width - 10 && p.x < width + 10 && p.y < 230 && p.y > 195)alpha = 0.3f;

		mp_uiManager->DrawHPBar(
			mp_enemyManager->GetBossHP(),
			mp_enemyManager->GetBossMaxHP(),
			width,
			alpha
		);
	}
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