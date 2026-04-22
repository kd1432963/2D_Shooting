#pragma once

#include"Application/Scene/Core/SceneBase.h"

#include"Application//GameObject/Chara/Player/Player.h"

class EnemyBase;

//********************************************************
// ゲームシーンのクラス
//********************************************************
class GameScene :public SceneBase
{
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
	void CheckCollition();

private:

	//+++++++++++++++++++++++++++++++++++++++++
	// プレイヤー
	//+++++++++++++++++++++++++++++++++++++++++
	Player m_player;

	//+++++++++++++++++++++++++++++++++++++++++
	// 敵リスト
	//+++++++++++++++++++++++++++++++++++++++++
	//+++++++++++++++++++++++++++++++++++++++++
	// EnemyBase を前方宣言のまま unique_ptr で保持するため、
	// デフォルトの delete（default_delete）を使わず、
	// 実際の delete 処理を cpp 側で定義するカスタムデリータを使用する。
	// これにより、ヘッダでは EnemyBase の完全型を要求されない。
	//+++++++++++++++++++++++++++++++++++++++++
	struct EnemyDeleter {
		void operator()(EnemyBase* p);
	};
	std::vector<std::unique_ptr<EnemyBase,EnemyDeleter>>mp_enemyList;
};
