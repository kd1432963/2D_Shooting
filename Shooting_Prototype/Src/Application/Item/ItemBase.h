#pragma once

#include"Application/GameObject/GameObjectBase.h"

#include"ItemType.h"

class ItemBase : public GameObjectBase
{
public:

	virtual~ItemBase() = default;
	ItemBase(ItemType t);


	virtual void Update()override;
	virtual void Draw2D()override;

public:

	//+++++++++++++++++++++++++++++++++++++++++
	// ゲッター
	//+++++++++++++++++++++++++++++++++++++++++
	bool IsDead() const { return isDead; }
	ItemType GetItemType() const{ return type; }

public:

	//+++++++++++++++++++++++++++++++++++++++++
	// セッター
	//+++++++++++++++++++++++++++++++++++++++++
	void SetDead() { isDead = true; }

protected:

	ItemType type = ItemType::None;
	bool isDead = false;
	Math::Rectangle rect = {};
};