#include "ItemStockManager.h"

void ItemStockManager::AddItem(ItemType type)
{
    if (m_items.size() >= 3) return;
    m_items.push_back(type);
}

void ItemStockManager::UseItem()
{
    if (m_items.empty()) return;

    ItemType t = m_items.front();
    m_items.erase(m_items.begin());
}

