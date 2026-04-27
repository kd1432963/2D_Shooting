#include"Application/Effect/EffectManager.h"

void EffectManager::AddEffect(std::unique_ptr<EffectBase>&& effect)
{
	m_effectList.emplace_back(std::move(effect));
}

void EffectManager::Update()
{
	for (auto& e : m_effectList)
	{
		e->Update();
	}

	m_effectList.erase(
	std::remove_if(
		m_effectList.begin(),
		m_effectList.end(),
		[](const auto& e) { return e->IsDead(); }
	),
		m_effectList.end()
	);
}

void EffectManager::Draw2D()
{
	for (auto& e : m_effectList)
	{
		e->Draw2D();
	}
}