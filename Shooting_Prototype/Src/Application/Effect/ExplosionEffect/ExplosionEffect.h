#pragma once

#include"Application/Effect/EffectBase.h"

class ExplosionEffect : public EffectBase
{
public:

	ExplosionEffect(const Math::Vector2& pos);

	void Update()override;
	void Draw2D()override;

private:

	Math::Vector2 m_pos = {};

};