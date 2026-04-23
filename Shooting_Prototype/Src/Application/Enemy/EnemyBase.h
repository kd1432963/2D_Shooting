#pragma once

#include"Application/Chara/CharaBase.h"

class EnemyBase :public CharaBase
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
	virtual void Update()override = 0;	// 更新
	virtual void Draw2D()override = 0;	// 描画
	virtual void Action() = 0;			// 行動決定
	virtual void Init() = 0;			// 初期化

public:

	void TakeDamage(int damage) { status.hp -= damage; }
	bool IsDead()const { return status.hp <= 0; }

protected:

	



};