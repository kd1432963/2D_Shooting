#pragma once

class c_Mouse
{
public:
	//+++++++++++++++++++++++++++++++++++++++++
	// 入力更新
	//+++++++++++++++++++++++++++++++++++++++++
	void Update();

private:
	//+++++++++++++++++++++++++++++++++++++++++
	// メンバ変数
	//+++++++++++++++++++++++++++++++++++++++++

	POINT m_pos;	// マウス座標
	POINT m_prevPos;// 前フレームのマウス座標
	POINT m_delta;	// マウス座標がどれだけ動いたか

	//=== 左クリック状態 ========================

	bool m_nowLeftBtn = false;	// 現在フレーム
	bool m_prevLeftBtn = false;	// 前フレーム

	//=== 右クリック状態 ========================

	bool m_nowRightBtn = false;	// 現在フレーム
	bool m_prevRightBtn = false;// 前フレーム

	//=== マウスホイール ========================

	int m_wheel = 0;

public:
	//+++++++++++++++++++++++++++++++++++++++++
	// 入力状態取得関数
	//+++++++++++++++++++++++++++++++++++++++++
	bool IsPressLeft() { return m_nowLeftBtn; }
	bool IsTriggerLeft() { return m_nowLeftBtn && !m_prevLeftBtn; }
	bool IsReleaseLeft() { return !m_nowLeftBtn && m_prevLeftBtn; }

	bool IsPressRight() { return m_nowRightBtn; }
	bool IsTriggerRight() { return m_nowRightBtn && !m_prevRightBtn; }
	bool IsReleaseRight() { return !m_nowRightBtn && m_prevRightBtn; }

	//=== マウス座標の移動量を返す ===============

	POINT Delta() const { return m_delta; }

	//=== ホイール回転量 ========================

	int Wheel() const { return m_wheel; }

	//=== マウス座標　===========================

	Math::Vector2 GetPos()const { return Math::Vector2(ToFloat(m_pos.x), ToFloat(m_pos.y)); }
};