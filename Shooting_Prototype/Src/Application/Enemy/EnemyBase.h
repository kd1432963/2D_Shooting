#pragma once

#include "Application/Chara/CharaBase.h"

#include"EnemyType.h"

class BulletManager;

class EnemyBase : public CharaBase
{
public:

	EnemyBase(EnemyType t)
		:type(t){ }

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
	// 敵の種類のゲッター
	//**********************************
	EnemyType GetType()const { return type; }

public:

	//**********************************
	// システム側のキル
	//**********************************
	bool IsSystemDead()const { return isSystemDead; }
	void SystemKill() { isSystemDead = true; }

public:

	//**********************************
	// 攻撃処理（必要な敵のみ使用）
	//**********************************
	virtual void Shot(BulletManager& bulletManager) {}


protected:

	//**********************************
	// 敵共通変数
	//**********************************

	Math::Vector2 basePos = {};
	bool isSystemDead = false;
	EnemyType type = EnemyType::None;
};