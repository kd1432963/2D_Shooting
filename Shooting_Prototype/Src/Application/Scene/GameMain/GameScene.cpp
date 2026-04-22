#include "GameScene.h"

#include"Application/Scene/SceneManager.h"

#include"Application/Scene/Result/ResultScene.h"

#include"Application/GameObject/HitBox.h"

#include"Application/GameObject/Chara/Enemy/EnemyBase.h"
#include"Application/GameObject/Chara/Enemy/Enemy1/Enemy1.h"

#include"Application/GameObject/Bullet/BulletBase.h"

//+++++++++++++++++++++++++++++++++++++++++
// シーンができたときに一度だけ通る関数
//+++++++++++++++++++++++++++++++++++++++++
void GameScene::OnEnter()
{
	// プレイヤー初期化
	m_player.Init();

	// 敵生成
	for (int i = 0; i < 5; ++i)
	{
		std::unique_ptr<EnemyBase, EnemyDeleter> enemy(new Enemy1(),EnemyDeleter{});
		mp_enemyList.emplace_back(std::move(enemy));
		mp_enemyList.back()->Init();
	}
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
	if (KEY.IsTrigger(VK_SPACE))
	{
		SCENE_MANAGER.RequestChange(std::make_unique<ResultScene>());
	}

	// プレイヤー行動決定
	m_player.Action();

	// 敵行動決定
	for (auto& e : mp_enemyList)
	{
		e->Action();
	}

	// 当たり判定
	CheckCollition();


	// 敵更新
	for (auto& e : mp_enemyList)
	{
		e->Update();
	}

	// プレイヤー更新
	m_player.Update();
}

//+++++++++++++++++++++++++++++++++++++++++
// 描画処理（毎フレーム）
//+++++++++++++++++++++++++++++++++++++++++
void GameScene::Draw2D()
{
	// 敵描画
	for (auto& e : mp_enemyList)
	{
		e->Draw2D();
	}

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
void GameScene::CheckCollition()
{
	auto bullets = m_player.GetBullets();

	for (auto& b : bullets)
	{
		for (auto& e : mp_enemyList)
		{
			if (b->GetHitBox().IsHit(e->GetHitBox()))
			{
				b->SetDead();
			}
		}
	}

}

void GameScene::EnemyDeleter::operator()(EnemyBase* p)
{
	delete p;
}
