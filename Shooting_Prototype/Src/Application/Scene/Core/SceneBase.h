#pragma once

class SceneBase
{
public:

	//**********************************
	// 仮想デストラクタ
	//**********************************
	virtual ~SceneBase() = default;

public:

	//**********************************
	// 基本ライフサイクル
	//**********************************
	virtual void OnEnter() = 0;		// シーンができるときに最初だけ
	virtual void OnExit() = 0;		// シーンがなくなる最後だけ
	virtual void OnPause() = 0;		// そのシーンが最上位でなくなるとき
	virtual void OnResume() = 0;	// そのシーンが最上位に戻るとき

public:

	//**********************************
	// メイン処理
	//**********************************
	virtual void Update() = 0;		// 更新処理
	virtual void Draw2D() = 0;		// 描画処理
	virtual void ImGuiUpdate() = 0;	// デバック画面更新

public:

	//+++++++++++++++++++++++++++++++++++++++++
	// 更新、描画処理を止めるかどうか
	//+++++++++++++++++++++++++++++++++++++++++
	virtual bool BlocksBelowUpdate() { return true; }
	virtual bool BlocksBelowDraw() { return false; }
};