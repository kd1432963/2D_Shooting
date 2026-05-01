#include "ItemStockManager.h"

void ItemStockManager::AddItem(ItemType type)
{
    if (m_items.size() >= 3) return;
    m_items.push_back(type);
}

void ItemStockManager::UseItem()
{
    if (m_items.empty()) return;

    ItemType t = m_items.back();
    m_items.pop_back();
}

