#include "UIManager.h"
#include "Application/Item/ItemStockManager.h"
#include"Application/Chara/Player.h"

void UIManager::Init()
{
}

void UIManager::Update()
{
}

void UIManager::DrawTitleUI()
{
	// BOX 仮表示
	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
	SHADER.m_spriteShader.DrawBox(0, 310, 640, 50, &Math::Color(0, 0, 0, 1));
	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
	SHADER.m_spriteShader.DrawBox(0, -310, 640, 50, &Math::Color(0, 0, 0, 1));
}

void UIManager::DrawResultUI(int score)
{
	// BOX 仮表示
	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
	SHADER.m_spriteShader.DrawBox(0, 300, 640, 60, &Math::Color(0, 0, 0, 1));
	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
	SHADER.m_spriteShader.DrawBox(0, -300, 640, 60, &Math::Color(0, 0, 0, 1));
}

void UIManager::DrawHPBar(int hp, int maxHp, float width, float alpha)
{
	float rate =
		ToFloat(hp) / maxHp;

	float Width = width * rate;

	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);

	SHADER.m_spriteShader.DrawBox(-2, 212, width + 3, 10, &Math::Color(1, 1, 1, alpha));
	SHADER.m_spriteShader.DrawBox(-0, 212, width, 8, &Math::Color(0.1f, 0.1f, 0.1f, alpha));
	SHADER.m_spriteShader.DrawBox(-0 - (width - Width), 212, Width, 8, &Math::Color(1, 0.2f, 0.2f, alpha));
}

void UIManager::DrawGameUI(int score, const ItemStockManager& stock, Player& player, int wave, bool isWarning)
{
	// UI が隠れたらボス専用に切り替え
	bool isBoss = m_warningTime > 300;

	// BOX 仮表示
	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
	SHADER.m_spriteShader.DrawBox(0, 300, 640, 60, &Math::Color(0.08f, 0.08f, 0.08f, 1));
	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
	SHADER.m_spriteShader.DrawBox(0, -300, 640, 60, &Math::Color(0.08f, 0.08f, 0.08f, 1));

	Math::Color color = { 1.0f,1.0f,1.0f,1.0f };

	if (player.CanUseItem())
	{
		++m_itemTime;

		float t = (sinf(m_itemTime * 0.05f) + 1.0f) * 0.5f;

		color =
		{
			1.0f - t,          // R固定
			1.0f,      // G変化
			1.0f - t,      // B変化
			1.0f
		};
	}
	else
	{
		m_itemTime = 0;
	}

	// アイテム枠
	SHADER.m_spriteShader.DrawBox(0, -300, 225, 50, &Math::Color(0, 0, 0, 1), true);
	SHADER.m_spriteShader.DrawBox(0, -300, 225, 50, &color, false);
	SHADER.m_spriteShader.DrawLine(-225, -285, 225, -285, &Math::Color(1, 1, 1, 1));

	// 1本目
	SHADER.m_spriteShader.DrawLine(-75, -285, -75, -350, &Math::Color(1, 1, 1, 1));

	// 2本目
	SHADER.m_spriteShader.DrawLine(75, -285, 75, -350, &Math::Color(1, 1, 1, 1));

	// Score仮表示
	SHADER.m_spriteShader.DrawBox(0, 300, 250, 50, &Math::Color(1, 1, 1, 1), false);

	Math::Matrix S = Math::Matrix::CreateScale(1.0f, 1.0f, 1.0f);
	Math::Matrix T = Math::Matrix::CreateTranslation(-125.0f, 295, 0);
	SHADER.m_spriteShader.SetMatrix(S * T);
	SHADER.m_spriteShader.DrawTex(ASSET.GetTexture("SCORE"), ASSET.GetRectangle("SCORE"));

	std::string padScore = std::to_string(score);
	while (padScore.size() < 6)
	{
		padScore = "0" + padScore;
	}

	if (isBoss)
	{
		padScore = "??????";
	}

	std::vector<Math::Rectangle>rectList;

	for (const auto& s : padScore)
	{
		Math::Rectangle rect = {};

		switch (s)
		{
		case '0': rect = { 0,        0,87,101 }; break;
		case '1': rect = { 87 * 1,  0,87,101 }; break;
		case '2': rect = { 87 * 2,  0,87,101 }; break;
		case '3': rect = { 87 * 3,  0,87,101 }; break;
		case '4': rect = { 87 * 4,  0,87,101 }; break;
		case '5': rect = { 87 * 5,  0,87,101 }; break;
		case '6': rect = { 88 * 6,  0,87,101 }; break;
		case '7': rect = { 88 * 7,  0,87,101 }; break;
		case '8': rect = { 88 * 8,  0,87,101 }; break;
		case '9': rect = { 88 * 9,  0,87,101 }; break;
		case '?': rect = { 88 * 10, 0,76,101 }; break;
			/*case '0': rect = { 0,        0,160,160 }; break;
			case '1': rect = { 160 * 1,  0,160,160 }; break;
			case '2': rect = { 160 * 2,  0,160,160 }; break;
			case '3': rect = { 160 * 3,  0,160,160 }; break;
			case '4': rect = { 160 * 4,  0,160,160 }; break;
			case '5': rect = { 160 * 5,  0,160,160 }; break;
			case '6': rect = { 160 * 6,  0,160,160 }; break;
			case '7': rect = { 160 * 7,  0,160,160 }; break;
			case '8': rect = { 160 * 8,  0,160,160 }; break;
			case '9': rect = { 160 * 9,  0,160,160 }; break;
			case '?': rect = { 160 * 10, 0,160,160 }; break;*/
		}

		rectList.push_back(rect);
	}

	for (int i = 0; i < rectList.size(); ++i)
	{
		Math::Matrix S = Math::Matrix::CreateScale(0.46f, 0.46f, 1.0f);
		Math::Matrix T = Math::Matrix::CreateTranslation(25 + i * 40.0f, 295, 0);
		SHADER.m_spriteShader.SetMatrix(S * T);
		SHADER.m_spriteShader.DrawTex(ASSET.GetTexture("Number"), rectList[i]);
		/*Math::Matrix S = Math::Matrix::CreateScale(0.38f, 0.38f, 1.0f);
		Math::Matrix T = Math::Matrix::CreateTranslation(30+i*37.5f, 300, 0);
		SHADER.m_spriteShader.SetMatrix(S * T);
		SHADER.m_spriteShader.DrawTex(ASSET.GetTexture("Number"), rectList[i]);*/
	}



	//SHADER.m_spriteShader.DrawString(-245, 342.5f, scoreStr.c_str(), Math::Vector4(1, 1, 1, 1), 1.3f);

	SHADER.m_spriteShader.DrawString(-55, -240, "ITEMS", Math::Vector4(1, 1, 1, 1), 0.75f);

	SHADER.m_spriteShader.End();
	SHADER.m_spriteShader.Begin();

	//============================
	// アイテムストック描画
	//============================

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

			case ItemType::Piercing:
				texName = "PiercingItem";
				break;
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

	float itemRecast = player.GetItemRecast();

	if (itemRecast > 0.0f || m_itemGauge > 0.001f)
	{
		float target = itemRecast / 5.0f;

		m_itemGauge += (target - m_itemGauge) * 0.1f;

		float heightF = 50.0f * m_itemGauge;
		int height = ToInt(ceilf(heightF));

		int centerY = -300 + (50 - height);

		SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
		SHADER.m_spriteShader.DrawBox(0, centerY, 225, height, &Math::Color(1, 1, 1, 0.5f));
	}

	//============================
	// 強化残り時間描画
	//============================
	{
		Math::Matrix S = Math::Matrix::CreateScale(1.25f, 1.25f, 1.0f);
		Math::Matrix T = Math::Matrix::CreateTranslation(325, -300.0f, 0.0f);

		SHADER.m_spriteShader.SetMatrix(S * T);
		SHADER.m_spriteShader.DrawTex(ASSET.GetTexture("HomingIcon"), ASSET.GetRectangle("HomingIcon"));

		S = Math::Matrix::CreateScale(1.25f, 1.25f, 1.0f);
		T = Math::Matrix::CreateTranslation(425, -300.0f, 0.0f);

		SHADER.m_spriteShader.SetMatrix(S * T);
		SHADER.m_spriteShader.DrawTex(ASSET.GetTexture("PiercingIcon"), ASSET.GetRectangle("PiercingIcon"));

		SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);

		float recast = player.GetHomingTime(); // 0.0f ～ 3.0f
		float ratio = 1.0f - (recast / 3.0f);    // 0.0f → 最大、3.0f → 0

		if (ratio > 0.0f)
		{
			float h = 40.0f * ratio;
			float y = -300 - (40.0f - h);

			SHADER.m_spriteShader.DrawBox(
				325, y,
				40, h,
				&Math::Color(0.0f, 0.0f, 0.0f, 0.5f)
			);
		}

		recast = player.GetPiercingTime();
		ratio = 1.0f - (recast / 2.5f);   

		if (ratio > 0.0f)
		{
			float h = 40.0f * ratio;
			float y = -300 - (40.0f - h);

			SHADER.m_spriteShader.DrawBox(
				425, y,
				40, h,
				&Math::Color(0.0f, 0.0f, 0.0f, 0.5f)
			);
		}


		SHADER.m_spriteShader.End();
		SHADER.m_spriteShader.Begin();
	}


	//============================
	// プレイヤーヒットポイント描画
	//============================
	{
		SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
		SHADER.m_spriteShader.DrawString(-637.5f, 335.0f, "HP[                 ]", Math::Color(1, 1, 1, 1), 1.35f);
		SHADER.m_spriteShader.End();
		SHADER.m_spriteShader.Begin();
		for (int i = 0; i < player.GetHp(); ++i)
		{
			Math::Matrix S = Math::Matrix::CreateScale(0.75f, 1.0f, 1.0f);
			Math::Matrix T = Math::Matrix::CreateTranslation(-490.0f + (i * 45), 285.0f, 0.0f);
			SHADER.m_spriteShader.SetMatrix(S * T);
			SHADER.m_spriteShader.DrawTex(ASSET.GetTexture("HPIcon"), ASSET.GetRectangle("HPIcon"));
		}
	}

	//============================
	// 操作方法描画
	//============================

	float baseX = -575;

	// Move
	{
		Math::Matrix S = Math::Matrix::CreateScale(1.6f, 1.6f, 1.0f);
		Math::Matrix R = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(90.0f));
		Math::Matrix T = Math::Matrix::CreateTranslation(baseX, -280.0f, 0.0f);
		SHADER.m_spriteShader.SetMatrix(S * R * T);
		SHADER.m_spriteShader.DrawTex(ASSET.GetTexture("Player"), ASSET.GetRectangle("Player"));

		S = Math::Matrix::CreateScale(0.4f, 0.4f, 1.0f);
		T = Math::Matrix::CreateTranslation(baseX, -310.0f, 0.0f);
		SHADER.m_spriteShader.SetMatrix(S * T);
		SHADER.m_spriteShader.DrawTex(ASSET.GetTexture("W"), ASSET.GetRectangle("W"));

		S = Math::Matrix::CreateScale(0.4f, 0.4f, 1.0f);
		T = Math::Matrix::CreateTranslation(baseX - 20, -330.0f, 0.0f);
		SHADER.m_spriteShader.SetMatrix(S * T);
		SHADER.m_spriteShader.DrawTex(ASSET.GetTexture("A"), ASSET.GetRectangle("A"));

		S = Math::Matrix::CreateScale(0.4f, 0.4f, 1.0f);
		T = Math::Matrix::CreateTranslation(baseX, -330.0f, 0.0f);
		SHADER.m_spriteShader.SetMatrix(S * T);
		SHADER.m_spriteShader.DrawTex(ASSET.GetTexture("S"), ASSET.GetRectangle("S"));

		S = Math::Matrix::CreateScale(0.4f, 0.4f, 1.0f);
		T = Math::Matrix::CreateTranslation(baseX + 20, -330.0f, 0.0f);
		SHADER.m_spriteShader.SetMatrix(S * T);
		SHADER.m_spriteShader.DrawTex(ASSET.GetTexture("D"), ASSET.GetRectangle("S"));

		for (int i = 0; i < 4; ++i)
		{
			S = Math::Matrix::CreateScale(0.35f, 0.35f, 1.0f);
			Math::Matrix R = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(90.0f * i));
			T = Math::Matrix::CreateTranslation(baseX - 30 + (i * 20), -255.0f, 0.0f);
			SHADER.m_spriteShader.SetMatrix(S * R * T);
			SHADER.m_spriteShader.DrawTex(ASSET.GetTexture("Arrow"), ASSET.GetRectangle("Arrow"));
		}




		SHADER.m_spriteShader.End();
		SHADER.m_spriteShader.Begin();
	}

	// Shot
	{
		Math::Matrix S = Math::Matrix::CreateScale(1.6f, 1.6f, 1.0f);
		Math::Matrix R = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(90.0f));
		Math::Matrix T = Math::Matrix::CreateTranslation(baseX + 130, -280.0f, 0.0f);
		SHADER.m_spriteShader.SetMatrix(S * R * T);
		SHADER.m_spriteShader.DrawTex(ASSET.GetTexture("Player"), ASSET.GetRectangle("Player"));

		S = Math::Matrix::CreateScale(1.0f, 1.0f, 1.0f);
		T = Math::Matrix::CreateTranslation(baseX + 160, -280.0f, 0.0f);
		SHADER.m_spriteShader.SetMatrix(S * T);
		SHADER.m_spriteShader.DrawTex(ASSET.GetTexture("Straight"), ASSET.GetRectangle("Straight"));

		S = Math::Matrix::CreateScale(0.75f, 0.75f, 1.0f);
		T = Math::Matrix::CreateTranslation(baseX + 146, -320.0f, 0.0f);
		SHADER.m_spriteShader.SetMatrix(S * T);
		SHADER.m_spriteShader.DrawTex(ASSET.GetTexture("MouseLeft"), ASSET.GetRectangle("MouseLeft"));

		SHADER.m_spriteShader.End();
		SHADER.m_spriteShader.Begin();
	}

	// アイテム使用
	{
		Math::Matrix S = Math::Matrix::CreateScale(1.6f, 1.6f, 1.0f);
		Math::Matrix R = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(90.0f));
		Math::Matrix T = Math::Matrix::CreateTranslation(baseX + 250, -280.0f, 0.0f);
		SHADER.m_spriteShader.SetMatrix(S * R * T);
		SHADER.m_spriteShader.DrawTex(ASSET.GetTexture("Player"), ASSET.GetRectangle("Player"));

		S = Math::Matrix::CreateScale(1.2f, 1.2f, 1.2f);
		T = Math::Matrix::CreateTranslation(baseX + 280, -280.0f, 0.0f);
		SHADER.m_spriteShader.SetMatrix(S * T);
		SHADER.m_spriteShader.DrawTex(ASSET.GetTexture("Homing"), ASSET.GetRectangle("Homing"));

		S = Math::Matrix::CreateScale(1.0f, 1.0f, 1.0f);
		T = Math::Matrix::CreateTranslation(baseX + 300, -280.0f, 0.0f);
		SHADER.m_spriteShader.SetMatrix(S * T);
		SHADER.m_spriteShader.DrawTex(ASSET.GetTexture("Piercing"), ASSET.GetRectangle("Piercing"));
	}

	if (player.CanUseItem())
	{
		SHADER.m_spriteShader.End();
		SHADER.m_spriteShader.Begin();

		Math::Matrix S = Math::Matrix::CreateScale(0.75f, 0.75f, 1.0f);
		Math::Matrix T = Math::Matrix::CreateTranslation(-300.0f, -320.0f, 0.0f);

		SHADER.m_spriteShader.SetMatrix(S * T);
		SHADER.m_spriteShader.DrawTex(ASSET.GetTexture("MouseRight"), 0, 0, &ASSET.GetRectangle("MouseRight"), &color);
	}


	//============================
	// WAVE数描画
	//============================
	{
		std::string Wave = "Wave：" + std::to_string(wave) + " / 15";
		Math::Vector4 color = { 1,1,1,1 };

		if (isBoss)
		{
			Wave = "Wave : 16 / 16";
			color = { 1,0.1,0.1,1 };
			SHADER.m_spriteShader.DrawString(300 + 1.5f, 310 - 1.5f, Wave.c_str(), Math::Vector4(1, 1, 1, 1));
		}

		SHADER.m_spriteShader.DrawString(300, 310, Wave.c_str(), color);
	}

	SHADER.m_spriteShader.End();
	SHADER.m_spriteShader.Begin();

	if (isWarning)
	{
		SHADER.m_spriteShader.End();
		SHADER.m_spriteShader.Begin();


		m_warningTime++;

		Math::Color color = { 1,1,1,1.0f };
		Math::Rectangle rect = { 0, 391, 1672, 160 };
		Math::Matrix S = Math::Matrix::CreateScale(0.75f, 0.75f, 1.0f);

		m_warningX += 10;

		Math::Matrix T = Math::Matrix::CreateTranslation(m_warningX, 300, 0);
		// 上一枚目
		SHADER.m_spriteShader.SetMatrix(S * T);
		SHADER.m_spriteShader.DrawTex(ASSET.GetTexture("WarningEffect"), 0, 0, &rect, &color);

		// 上二枚目
		T = Math::Matrix::CreateTranslation(m_warningX - 1254, 300, 0);
		SHADER.m_spriteShader.SetMatrix(S * T);
		SHADER.m_spriteShader.DrawTex(ASSET.GetTexture("WarningEffect"), 0, 0, &rect, &color);

		// 下一枚目
		S = Math::Matrix::CreateScale(-0.75f, 0.75f, 1.0f);
		T = Math::Matrix::CreateTranslation(m_warningX * -1, -300, 0);
		SHADER.m_spriteShader.SetMatrix(S * T);
		SHADER.m_spriteShader.DrawTex(ASSET.GetTexture("WarningEffect"), 0, 0, &rect, &color);

		// 下二枚目
		T = Math::Matrix::CreateTranslation(m_warningX * -1 + 1254, -300, 0);
		SHADER.m_spriteShader.SetMatrix(S * T);
		SHADER.m_spriteShader.DrawTex(ASSET.GetTexture("WarningEffect"), 0, 0, &rect, &color);
	}
}
