#pragma once

#include"Application/Scene/Core/SceneBase.h"

class UIManager;
class Button;

//********************************************************
// リザルトシーンのクラス
//********************************************************
class ResultScene :public SceneBase
{
public:

	ResultScene() {};
	ResultScene(int score) { m_score = score; }

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

	void DrawScore();
	void DrawRank();
	void DrawButton();

public:

	UIManager* mp_uiManager = nullptr;

	// 経過時間
	int m_time = 0;
	float m_bottomY = Screen::Height;

	int m_score = 0;

	std::string m_rank = "";
	Math::Color m_color = {};
	Math::Rectangle m_rect = {};

	Button* mp_restartBtn = nullptr;
	Button* mp_backBtn = nullptr;
};
