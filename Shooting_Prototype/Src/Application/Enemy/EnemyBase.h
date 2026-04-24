#pragma once

#include "Application/Chara/CharaBase.h"

class BulletManager;

class EnemyBase : public CharaBase
{
public:

	//**********************************
	// 仮想デストラクタ
	//**********************************
	virtual ~EnemyBase() = default;

public:

	//**********************************
	// 基本ライフサイクル
	//**********************************
	virtual void Update() override = 0;
	virtual void Draw2D() override = 0;
	virtual void Action() override = 0;

public:

	//**********************************
	// 攻撃処理（必要な敵のみ使用）
	//**********************************
	virtual void Shot(BulletManager& bulletManager) {}

};