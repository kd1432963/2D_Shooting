#pragma once

#include "Application/Enemy/EnemyBase.h"

class BulletManager;

class Enemy4 : public EnemyBase
{
public:

	Enemy4(const Math::Vector2& p);

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

	int m_shotWait = 0;
	int m_aliveTime = 0;
};