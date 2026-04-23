#pragma once

#include"Application/Scene/Core/SceneBase.h"

#include"Application/Chara/Player.h"



class EnemyManager;
class EnemySpawner;
class BulletManager;

//********************************************************
// ゲームシーンのクラス
//********************************************************
class GameScene :public SceneBase
{
public:

	//+++++++++++++++++++++++++++++++++++++++++
	// コンストラクタ・デストラクタ
	//+++++++++++++++++++++++++++++++++++++++++
	GameScene();
	~GameScene();

public:

	//+++++++++++++++++++++++++++++++++++++++++
	// ライフサイクル（必要な時に 1 フレームだけ）
	//+++++++++++++++++++++++++++++++++++++++++
	void OnEnter()override;	// シーンができたとき
	void OnExit()override;	// シーンがなくなるとき
	void OnPause()override;	// シーンが最上位じゃなくなるとき
	void OnResume()override;// シーンが最上位に戻るとき

public:

	//+++++++++++++++++++++++++++++++++++++++++
	// メイン処理（毎フレーム実行）
	//+++++++++++++++++++++++++++++++++++++++++
	void Update()override;	// 更新処理
	void Draw2D()override;	// 描画処理

	//+++++++++++++++++++++++++++++++++++++++++
	// デバック画面更新処理（毎フレーム実行）
	//+++++++++++++++++++++++++++++++++++++++++
	void ImGuiUpdate()override;

public:

	//+++++++++++++++++++++++++++++++++++++++++
	// 更新、描画処理を止めるかどうか
	//+++++++++++++++++++++++++++++++++++++++++
	bool BlocksBelowUpdate() override { return true; }
	bool BlocksBelowDraw()override { return false; }

private:

	//+++++++++++++++++++++++++++++++++++++++++
	// 当たり判定処理
	//+++++++++++++++++++++++++++++++++++++++++
	void CheckCollision();

private:

	//+++++++++++++++++++++++++++++++++++++++++
	// プレイヤー
	//+++++++++++++++++++++++++++++++++++++++++
	Player m_player;

	//+++++++++++++++++++++++++++++++++++++++++
	// 敵
	//+++++++++++++++++++++++++++++++++++++++++
	EnemyManager* mp_enemyManager = nullptr;
	EnemySpawner* mp_enemySpawner = nullptr;

	//+++++++++++++++++++++++++++++++++++++++++
	// 弾
	//+++++++++++++++++++++++++++++++++++++++++
	BulletManager* mp_bulletManager = nullptr;
};
