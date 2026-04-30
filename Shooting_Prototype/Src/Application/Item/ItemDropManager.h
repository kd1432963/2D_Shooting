#pragma once

#include"ItemBase.h"

class ItemDropManager
{
public:

	void DropItemRandom(const Math::Vector2& p);

	void Update();
	void Draw2D();
	void DeleteDead();

	const std::vector<std::unique_ptr<ItemBase>>& GetItems() const
	{
		return m_itemDropList;
	}

private:

	std::vector<std::unique_ptr<ItemBase>>m_itemDropList;

};