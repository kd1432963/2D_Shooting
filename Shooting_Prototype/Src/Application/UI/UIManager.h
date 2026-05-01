#pragma once

class ItemStockManager;

class UIManager
{
public:

	UIManager() { Init(); }

	void Update();
	void Draw2D(int score, const ItemStockManager& stock);

private:

	void Init();

};