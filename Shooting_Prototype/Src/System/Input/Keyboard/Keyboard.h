#pragma once

class c_Keyboard
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
	std::array<bool, 256>m_now{};
	std::array<bool, 256>m_prev{};

public:
	//+++++++++++++++++++++++++++++++++++++++++
	// 入力状態取得関数
	//+++++++++++++++++++++++++++++++++++++++++
	bool IsPress(int key) { return m_now[key]; }					// 押している間
	bool IsTrigger(int key) { return (m_now[key] && !m_prev[key]); }// 押された瞬間
	bool IsRelease(int key) { return !m_now[key] && m_prev[key]; }	// 離した瞬間
};