#pragma once

#include"Keyboard/Keyboard.h"
#include"Input/Mouse/Mouse.h"

namespace Input
{
	extern c_Keyboard Keyboard;
	extern c_Mouse Mouse;


	//+++++++++++++++++++++++++++++++++++++++++
	// 入力更新関数
	//+++++++++++++++++++++++++++++++++++++++++
	void Update();
}

#define KEY Input::Keyboard
#define MOUSE Input::Mouse