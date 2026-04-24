#pragma once

#include "Src/Application/GameObject/GameObjectBase.h"

class CharaBase : public GameObjectBase
{
public:

	//**********************************
	// 仮想デストラクタ
	//**********************************
	virtual ~CharaBase() = default;

public:

	//**********************************
	// 基本ライフサイクル
	//**********************************
	virtual void Update() override = 0;
	virtual void Draw2D() override = 0;

	// 行動決定（入力・AIなどの処理）
	virtual void Action() = 0;

public:

	//**********************************
	// 状態取得・操作
	//**********************************
	bool WantToShot() const { return m_wantToShot; }

	void TakeDamage(int damage)
	{
		status.hp -= damage;
		if (status.hp < 0) status.hp = 0;
	}

	bool IsDead() const { return status.hp <= 0; }

protected:

	//**********************************
	// 描画補助
	//**********************************
	void DrawChara();

protected:

	//**********************************
	// ステータス情報
	//**********************************
	struct Status
	{
		int hp		= 0;
		int maxHp	= 0;
		int atk		= 0;
		int def		= 0;
	};

protected:

	//**********************************
	// 共通データ
	//**********************************
	Status status = {};

	Math::Rectangle rect = {};

	bool m_wantToShot = false;
};