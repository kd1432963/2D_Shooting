#include "Mouse.h"

#include"Application/main.h"

void c_Mouse::Update()
{
	//=== カーソルを非表示 ===================================

	// ShowCursor(false);

	//=== 前フレームのボタン状態を保存 =========================
	//	  押した瞬間や離した瞬間の判定に使う ====================

	m_prevPos = m_pos;
	m_prevLeftBtn = m_nowLeftBtn;
	m_prevRightBtn = m_nowRightBtn;

	//=== 現在のマウス座標をスクリーン座標で取得 =================

	GetCursorPos(&m_pos);
	ScreenToClient(APP.m_window.GetWndHandle(), &m_pos);

	//=== ウィンドウのクライアント領域のサイズを取得 ==============

	RECT clientRect;
	GetClientRect(APP.m_window.GetWndHandle(), &clientRect);
	int windowWidth = clientRect.right - clientRect.left;
	int windowHeight = clientRect.bottom - clientRect.top;

	//=== 論理座標系(階層解像度)を設定(例:1280×720) ============

	const int logicalWidht = 1280;
	const int logicalHeight = 720;

	//=== ウィンドウサイズに対するスケールを計算 =================

	float scaleX = static_cast<float>(logicalWidht) / windowWidth;
	float scaleY = static_cast<float>(logicalHeight) / windowHeight;

	//=== 論理座標系に変換 (ウィンドウ中心を(0,0)に変換) =========

	m_pos.x = static_cast<int>((m_pos.x - windowWidth / 2) * scaleX);
	m_pos.y = static_cast<int>((windowHeight / 2 - m_pos.y) * scaleY);

	//=== どれだけ動いたかを計算 ==============================

	m_delta.x = m_pos.x - m_prevPos.x;
	m_delta.y = m_pos.y - m_prevPos.y;

	//=== 左ボタンの押下状態を取得 =============================

	m_nowLeftBtn = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;

	//=== 右ボタンの押下状態を取得 =============================

	m_nowRightBtn = (GetAsyncKeyState(VK_RBUTTON) & 0x8000) != 0;

	//=== 毎フレームホイール量をセット ==========================

	m_wheel = APP.m_window.GetMouseWheelVal();
}
