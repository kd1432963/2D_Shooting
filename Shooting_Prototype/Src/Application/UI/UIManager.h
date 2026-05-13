#pragma once

class ItemStockManager;
class Player;

class UIManager
{
public:

	UIManager() { Init(); }

	void Update();
	void DrawTitleUI();
	void DrawGameUI(int score, const ItemStockManager& stock, Player&player,int wave, bool isWarning);
	void DrawResultUI(int score);

	void DrawHPBar(int hp, int maxHp, float width, float alpha = 1.0f);


private:

	void Init();

private:

	// アイテムリキャストゲージ表示用
	float m_itemGauge = 0.0f;

	int m_warningTime = 0;

	float m_warningX = -1254;

	int m_itemTime = 0;
};