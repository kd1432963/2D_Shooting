#pragma once

class ItemStockManager;

class UIManager
{
public:

	UIManager() { Init(); }

	void Update();
	void Draw2D(int score, const ItemStockManager& stock,float itemRecast);

private:

	void Init();

private:

	// アイテムリキャストゲージ表示用
	float m_itemGauge = 0.0f;

};