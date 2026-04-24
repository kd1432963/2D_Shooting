#pragma once

#include"Application/Enemy/EnemyBase.h"

class BulletManager;

class Enemy1 :public EnemyBase
{
public:

	Enemy1();
	Enemy1(const Math::Vector2 p);


public:

	//**********************************
	// 基本ライフサイクル
	//**********************************
	void Update()override;	// 更新
	void Action()override;	// 行動決定
	void Draw2D()override;	// 描画

public:

	//**********************************
	// 
	//**********************************
	void Shot(BulletManager& b)override;



private:

	//**********************************
	// メンバ変数
	//**********************************
	int t = 0;

};