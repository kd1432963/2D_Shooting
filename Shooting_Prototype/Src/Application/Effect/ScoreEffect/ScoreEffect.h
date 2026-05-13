#pragma once

#include "Application/Effect/EffectBase.h"

class ScoreEffect : public EffectBase
{
public:

	enum class BonusType
	{
		None,
		EnemyWipe,
		QuickKill,
	};

public:
	ScoreEffect(const Math::Vector2& pos, int score, BonusType type = BonusType::None);

	void Update() override;
	void Draw2D() override;

private:
	Math::Vector2 m_pos = {};

	Math::Color m_color = {};
	std::string m_scoreStr;
	std::string m_bonusStr;

	std::vector<Math::Rectangle> m_rectList;

	float m_alpha = 1.0f;

	float m_scale = 1.0f;
	float m_scaleBase = 1.0f;

	int m_score = 0;

	int m_popTimer = 0;
};
