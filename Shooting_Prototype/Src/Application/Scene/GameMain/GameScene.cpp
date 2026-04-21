#include "GameScene.h"

#include"Application/Scene/SceneManager.h"

#include"Application/Scene/Result/ResultScene.h"

#include"Application/GameObject/Chara/Enemy/EnemyBase.h"
#include"Application/GameObject/Chara/Enemy/Enemy1/Enemy1.h"

//+++++++++++++++++++++++++++++++++++++++++
// シーンができたときに一度だけ通る関数
//+++++++++++++++++++++++++++++++++++++++++
void GameScene::OnEnter()
{
	// プレイヤー初期化
	m_player.Init();

	// 初期敵生成
	EnemyBase* enemy = new Enemy1();
	mp_enemyList.push_back(enemy);
	mp_enemyList.back()->Init();
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
