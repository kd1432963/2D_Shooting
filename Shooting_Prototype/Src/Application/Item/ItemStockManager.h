#pragma once

#include"ItemType.h"

class ItemStockManager 
{
public:

    void AddItem(ItemType type);
    void UseItem(); 
    bool HasItem() const { return !m_items.empty(); }
    int Count() const { return (int)m_items.size(); }
    ItemType Get(int index) const { return m_items[index]; }

private:

    std::vector<ItemType> m_items;
};
