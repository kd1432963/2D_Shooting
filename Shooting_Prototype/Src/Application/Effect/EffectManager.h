#pragma once

#include"Application/Effect/EffectBase.h"

class EffectManager
{
public:

	void AddEffect(std::unique_ptr<EffectBase>&& effect);

	void SpawnHitEffect(const Math::Vector2& pos);
	void SpawnScoreEffect(const Math::Vector2& pos, int score, const std::string& type = "");

	void Update();
	void Draw2D();

	bool IsEmpty()const { return m_effectList.empty(); }

private:

	std::vector<std::unique_ptr<EffectBase>>m_effectList;

};