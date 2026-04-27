#pragma once

#include"Application/Effect/EffectBase.h"

class EffectManager
{
public:

	void AddEffect(std::unique_ptr<EffectBase>&&effect);

	void Update();
	void Draw2D();

private:

	std::vector<std::unique_ptr<EffectBase>>m_effectList;

};