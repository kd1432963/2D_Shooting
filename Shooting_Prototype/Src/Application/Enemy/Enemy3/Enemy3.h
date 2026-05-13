#pragma once

#include "Application/Enemy/EnemyBase.h"

class Player;

class Enemy3 : public EnemyBase
{
public:

	Enemy3(const Math::Vector2& p, Player* player);

public:

	//**********************************
	// 基本ライフサイクル
	//**********************************
	void Update() override;
	void Action() override;
	void Draw2D() override;

private:

	Player* mp_player = nullptr;

	int waitTimer = 0;
	int chargeTimer = 0;

	bool isCharging = false;

	Math::Vector2 velocity = {};

};