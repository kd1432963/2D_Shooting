#pragma once

#include"Application/Effect/EffectBase.h"

class AfterBurstEffect : public EffectBase
{
public:

	AfterBurstEffect(const Math::Vector2& pos);

	void Update()override;
	void Draw2D()override;

private:

	Math::Vector2 m_pos = {};
	bool m_isPlayer = false;
};