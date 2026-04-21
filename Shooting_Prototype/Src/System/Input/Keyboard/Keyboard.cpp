#include "Pch.h"
#include "Keyboard.h"

//+++++++++++++++++++++++++++++++++++++++++
// 入力更新関数
//+++++++++++++++++++++++++++++++++++++++++
void c_Keyboard::Update()
{
	//=== 前フレームの状態を保存 =============

	m_prev = m_now;

	//=== 全キーが今押されているかの確認 ======

	for (int i = 0; i < 256; i++)
	{
		m_now[i] = (GetAsyncKeyState(i) & 0x8000) != 0;
	}
}
