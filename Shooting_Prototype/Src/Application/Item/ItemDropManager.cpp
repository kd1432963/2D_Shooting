#include"ItemDropManager.h"

#include"HomingItem.h"

void ItemDropManager::DropItemRandom(const Math::Vector2&p)
{
	int r = RandomRange(1, 4);

	std::unique_ptr<ItemBase>item;

	if (r < 5)
	{
		item = std::make_unique<HomingItem>(p);
	}
	else if (r < 8)
	{

	}
	else
	{

	}

	m_itemDropList.push_back(std::move(item));
}

void ItemDropManager::Update()
{
	for (auto& item : m_itemDropList)
	{
		item->Update();
	}
}

void ItemDropManager::Draw2D()
{
	for (auto& item : m_itemDropList)
	{
		item->Draw2D();
	}
}

void ItemDropManager::DeleteDead()
{
	m_itemDropList.erase(
		std::remove_if(
			m_itemDropList.begin(),
			m_itemDropList.end(),
			[](const auto& item) { return item->IsDead(); }
		),
		m_itemDropList.end()
	);
}
