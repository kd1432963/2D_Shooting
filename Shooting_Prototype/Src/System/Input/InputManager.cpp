#include "InputManager.h"

namespace Input
{
	c_Keyboard Keyboard;
	c_Mouse Mouse;

	//+++++++++++++++++++++++++++++++++++++++++
	// 入力更新関数
	//+++++++++++++++++++++++++++++++++++++++++
	void Update()
	{
		Keyboard.Update();
		Mouse.Update();
	}
}

