#pragma once

#include"Application/GameObject/GameObjectBase.h"

class ItemBase : public GameObjectBase
{
public:

	virtual~ItemBase() = default;

	virtual void Update()override;
	virtual void Draw2D()override;

public:

	//+++++++++++++++++++++++++++++++++++++++++
	// ゲッター
	//+++++++++++++++++++++++++++++++++++++++++
	bool IsDead() const { return isDead; }

public:

	//+++++++++++++++++++++++++++++++++++++++++
	// セッター
	//+++++++++++++++++++++++++++++++++++++++++
	void SetDead() { isDead = true; }

protected:

	bool isDead = false;
	Math::Rectangle rect = {};
};