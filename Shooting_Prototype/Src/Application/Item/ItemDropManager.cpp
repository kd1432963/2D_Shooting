#include"ItemDropManager.h"

#include"HomingItem.h"

#include"PiercingItem.h"

void ItemDropManager::DropItemRandom(const Math::Vector2& p)
{
	int r = RandomRange(0, 2);

	std::unique_ptr<ItemBase>item=nullptr;

	if (r < 2)
	{
		item = std::make_unique<HomingItem>(p);
	}
	else if (r < 3)
	{
		item = std::make_unique<PiercingItem>(p);
	}
	else
	{

	}

	if(item)m_itemDropList.push_back(std::move(item));
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
