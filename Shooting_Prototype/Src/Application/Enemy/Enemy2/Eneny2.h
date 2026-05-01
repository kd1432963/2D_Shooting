#pragma once

#include "Application/Enemy/EnemyBase.h"

class Player;

class Enemy2 : public EnemyBase
{
public:

	Enemy2(const Math::Vector2& p,Player*player);

public:

	//**********************************
	// 基本ライフサイクル
	//**********************************
	void Update() override;
	void Action() override;
	void Draw2D() override;

private:

	Player* mp_player = nullptr;


	Math::Vector2 velocity = {};

};