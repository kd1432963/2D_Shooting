#pragma once

#include "Application/Enemy/EnemyBase.h"

class BulletManager;

class Enemy1 : public EnemyBase
{
public:

	Enemy1();
	Enemy1(const Math::Vector2& p);

public:

	//**********************************
	// 基本ライフサイクル
	//**********************************
	void Update() override;
	void Action() override;
	void Draw2D() override;

public:

	//**********************************
	// 攻撃処理
	//**********************************
	void Shot(BulletManager& b) override;

private:

	int t = 0;
};