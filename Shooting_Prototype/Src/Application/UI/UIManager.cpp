#include "UIManager.h"
#include "Application/Item/ItemStockManager.h"

void UIManager::Init()
{
}

void UIManager::Update()
{
}


void UIManager::Draw2D(int score, const ItemStockManager& stock, float itemRecast)
{
	// BOX 仮表示
	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
	SHADER.m_spriteShader.DrawBox(0, 300, 640, 60, &Math::Color(0, 0, 0, 1));
	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
	SHADER.m_spriteShader.DrawBox(0, -300, 640, 60, &Math::Color(0, 0, 0, 1));

	// アイテム枠
	SHADER.m_spriteShader.DrawBox(0, -300, 225, 50, &Math::Color(1, 1, 1, 1), false);
	SHADER.m_spriteShader.DrawLine(-225, -285, 225, -285, &Math::Color(1, 1, 1, 1));

	// 1本目
	SHADER.m_spriteShader.DrawLine(-75, -285, -75, -350, &Math::Color(1, 1, 1, 1));

	// 2本目
	SHADER.m_spriteShader.DrawLine(75, -285, 75, -350, &Math::Color(1, 1, 1, 1));

	// Score仮表示
	SHADER.m_spriteShader.DrawBox(0, 300, 250, 50, &Math::Color(1, 1, 1, 1), false);



	std::string padScore = std::to_string(score);
	while (padScore.size() < 6)
	{
		padScore = "0" + padScore;
	}

	std::string scoreStr = "SCORE：" + padScore;

	SHADER.m_spriteShader.DrawString(-245, 342.5f, scoreStr.c_str(), Math::Vector4(1, 1, 1, 1), 1.3f);

	SHADER.m_spriteShader.DrawString(-55, -240, "ITEMS", Math::Vector4(1, 1, 1, 1), 0.75f);

	SHADER.m_spriteShader.End();
	SHADER.m_spriteShader.Begin();

	// ============================
	//  アイテムストック描画
	// ============================

	const int maxSlots = 3;
	const float startX = -150;   // 左端
	const float slotWidth = 150; // スロット間隔

	for (int i = 0; i < maxSlots; i++)
	{
		float x = startX + i * slotWidth;
		float y = -320;

		// アイテムがある場合だけ描画
		if (i < stock.Count())
		{
			ItemType type = stock.Get(i);

			// アイテムごとにテクスチャを切り替える
			const char* texName = nullptr;

			switch (type)
			{
			case ItemType::Homing:
				texName = "HomingItem";
				break;
				/*  case ItemType::
					  texName = "";
					  break;
				  case ItemType::
					  texName = "";
					  break;*/
			}

			if (texName)
			{
				SHADER.m_spriteShader.SetMatrix(Math::Matrix::CreateScale(2.0f, 2.0f, 1.0f) * Math::Matrix::CreateTranslation(x, y, 0.0f));
				SHADER.m_spriteShader.DrawTex(ASSET.GetTexture(texName), ASSET.GetRectangle(texName));
			}

			// 先頭以外は使用不可とわかるように灰色ボックスを上から描画
			if (i != 0)
			{
				SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
				SHADER.m_spriteShader.DrawBox(x, y, 25, 25, &Math::Color(0, 0, 0, 0.5f));
			}
		}
	}

	if (itemRecast > 0.0f || m_itemGauge > 0.001f)
	{
		float target = itemRecast / 5.0f;

		m_itemGauge += (target - m_itemGauge) * 0.1f;

		float heightF = 50.0f * m_itemGauge;
		int height = (int)ceilf(heightF);

		int centerY = -300 - (50 - height);

		SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
		SHADER.m_spriteShader.DrawBox(0, centerY, 225, height, &Math::Color(1, 1, 1, 0.5f));
	}
}
