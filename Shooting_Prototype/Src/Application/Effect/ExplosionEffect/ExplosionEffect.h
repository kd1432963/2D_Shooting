#pragma once

#include"Application/Effect/EffectBase.h"

class ExplosionEffect : public EffectBase
{
public:

	ExplosionEffect(const Math::Vector2& pos);
	ExplosionEffect(const Math::Vector2& pos,bool isPlayer);

	void Update()override;
	void Draw2D()override;

private:

	Math::Vector2 m_pos = {};
	bool m_isPlayer = false;
};