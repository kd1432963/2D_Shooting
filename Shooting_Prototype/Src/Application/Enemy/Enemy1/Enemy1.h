#pragma once

#include"Application/Enemy/EnemyBase.h"

class Enemy1 :public EnemyBase
{
public:

	//**********************************
	// 基本ライフサイクル
	//**********************************
	void Init()override;	// 初期化
	void Update()override;	// 更新
	void Action()override;	// 行動決定
	void Draw2D()override;	// 描画

public:




private:

	//**********************************
	// メンバ変数
	//**********************************


};