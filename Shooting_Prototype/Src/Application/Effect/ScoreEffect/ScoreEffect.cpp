#include "ScoreEffect.h"

ScoreEffect::ScoreEffect(const Math::Vector2& pos, int score, BonusType type)
	: m_pos(pos)
{
	// 数字部分
	m_scoreStr = "+ " + std::to_string(score);

	for (const auto& s : m_scoreStr)
	{
		Math::Rectangle rect = {};

		switch (s)
		{
		case '0': rect = { 0,        0,51,59 }; break;
		case '1': rect = { 51 * 1,  0,51,59 }; break;
		case '2': rect = { 51 * 2,  0,51,59 }; break;
		case '3': rect = { 51 * 3,  0,50,59 }; break;
		case '4': rect = { 51 * 4,  0,51,59 }; break;
		case '5': rect = { 51 * 5,  0,51,59 }; break;
		case '6': rect = { 51 * 6,  0,51,59 }; break;
		case '7': rect = { 51 * 7,  0,51,59 }; break;
		case '8': rect = { 51 * 8,  0,51,59 }; break;
		case '9': rect = { 51 * 9,  0,51,59 }; break;
		case '+': rect = { 51 * 10, 0,51,59 }; break;
		}

		m_rectList.push_back(rect);
	}

	// ボーナス名部分
	switch (type)
	{
	case BonusType::EnemyWipe:
		m_bonusStr = "EnemyWipeBonus";
		m_pos = { -100,0 };
		break;

	case BonusType::QuickKill:
		m_bonusStr = "QuickKillBonus";
		m_pos = pos;
		break;

	default:
		m_bonusStr = "";
		break;
	}

	// 10〜5000 → 0〜1 に正規化
	float t = (score - 10) / 4990.0f;
	t = Clamp(t, 0.0f, 1.0f);

	// 色：白 → 赤（分かりやすく強め）
	m_color = {
		1.0f,
		1.0f - t,         // G
		1.0f - 2.0f * t,  // B
		1.0f
	};

	if (score > 5000)
	{
		m_score = score;
		t = 1.2f;
	}

	// 大きさ：10 → 0.5倍、5000 → 2.0倍
	m_scaleBase = 0.3f + t * 1.0f;

	// 出現時の「ポンッ」演出用
	m_scale = m_scaleBase * 1.2f;   // 最初だけ少し大きく
	m_popTimer = 0;

	m_alpha = 1.0f;
}

void ScoreEffect::Update()
{
	// 上昇
	m_pos.y += 1.0f;

	// 出現時の「ポンッ」縮小アニメ
	if (m_popTimer < 20)
	{
		m_scale += (m_scaleBase - m_scale) * 0.5f;
		m_popTimer++;
	}

	// フェードアウト
	m_alpha -= 0.015f;
	m_color.w = m_alpha;

	if (m_alpha <= 0.0f)isDead = true;
}

void ScoreEffect::Draw2D()
{
	SHADER.m_spriteShader.End();
	SHADER.m_spriteShader.Begin();

	for (int i = 0; i < m_rectList.size(); ++i)
	{
		float plusOffset = 0.0f;

		if (m_scoreStr[i] == '+')
		{
			plusOffset = 32 * m_scale;
		}

		float DrawPosX = m_pos.x + plusOffset + (i * 50 * m_scale);

		Math::Matrix S = Math::Matrix::CreateScale(m_scale, m_scale, 1.0f);
		Math::Matrix T = Math::Matrix::CreateTranslation(DrawPosX, m_pos.y, 0);
		SHADER.m_spriteShader.SetMatrix(S * T);
		SHADER.m_spriteShader.DrawTex(ASSET.GetTexture("EffectNumber"),0,0,&m_rectList[i],&m_color);
	}

	if (!m_bonusStr.empty())
	{
		Math::Vector2 scale = { m_scale * 0.2f ,m_scale*0.2f};
		Math::Vector2 drawPos = { m_pos.x + (125),m_pos.y + (50) };

		if (m_score > 5000)
		{
			scale *= 1.3f;
			drawPos= { m_pos.x+250 ,m_pos.y+80};
		}

		Math::Matrix S = Math::Matrix::CreateScale(scale.x, scale.y, 1.0f);
		Math::Matrix T = Math::Matrix::CreateTranslation(drawPos.x, drawPos.y, 0);
		SHADER.m_spriteShader.SetMatrix(S * T);
		SHADER.m_spriteShader.DrawTex(ASSET.GetTexture(m_bonusStr),0,0,&ASSET.GetRectangle(m_bonusStr),&Math::Color(1,1,1,m_alpha));
	}

	SHADER.m_spriteShader.End();
	SHADER.m_spriteShader.Begin();
}
