#pragma once

#include"Application/Scene/Core/SceneBase.h"

//********************************************************
// タイトルシーンのクラス
// 
// ・開始時に必ず最初に生成されるシーン
//********************************************************
class TitleScene :public SceneBase
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
};
