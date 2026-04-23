#include "GameScene.h"

#include"Application/Scene/SceneManager.h"

#include"Application/Scene/Result/ResultScene.h"

#include"Application/GameObject/HitBox.h"
#include"Application/Bullet/BulletBase.h"
#include"Application/Enemy/EnemyManager.h"
#include"Application/Enemy/EnemySpawner.h"

GameScene::GameScene()
{
	mp_enemyManager = new EnemyManager();
	mp_enemySpawner = new EnemySpawner();
}

GameScene::~GameScene()
{
	if (mp_enemyManager)
	{
		delete mp_enemyManager;
	}
	if (mp_enemySpawner)
	{
		delete mp_enemySpawner;
	}
}

//+++++++++++++++++++++++++++++++++++++++++
// シーンができたときに一度だけ通る関数
//+++++++++++++++++++++++++++++++++++++++++
void GameScene::OnEnter()
{
	// プレイヤー初期化
	m_player.Init();

	// 敵生成
	mp_enemySpawner->SpawnWave1(*mp_enemyManager);
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
	mp_enemySpawner->SpawnWave2(*mp_enemyManager);

	if (KEY.IsTrigger(VK_SPACE))
	{
		SCENE_MANAGER.RequestChange(std::make_unique<ResultScene>());
	}

	// プレイヤー行動決定
	m_player.Action();

	// 敵行動決定
	mp_enemyManager->Action();

	// 当たり判定
	CheckCollision();

	// 死亡処理
	mp_enemyManager->DeleteDead();

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
	// 敵描画
	mp_enemyManager->Draw2D();

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

	auto& bullets = m_player.GetBullets();
	auto& enemies = mp_enemyManager->GetEnemies();

	for (auto& b : bullets)
	{
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