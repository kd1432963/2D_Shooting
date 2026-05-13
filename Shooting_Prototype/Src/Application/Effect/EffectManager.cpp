#include"Application/Effect/EffectManager.h"

#include"Application/Effect/HitEffect/HitEffect.h"
#include"Application/Effect/ScoreEffect/ScoreEffect.h"

void EffectManager::AddEffect(std::unique_ptr<EffectBase>&& effect)
{
	m_effectList.emplace_back(std::move(effect));
}

void EffectManager::SpawnHitEffect(const Math::Vector2& pos)
{
	auto effect = std::make_unique<HitEffect>(pos);
	AddEffect(std::move(effect));
}

void EffectManager::SpawnScoreEffect(const Math::Vector2& pos, int score, const std::string& type)
{
	ScoreEffect::BonusType bonusType = ScoreEffect::BonusType::None;

	if(type=="EnemyWipe")bonusType = ScoreEffect::BonusType::EnemyWipe;
	if(type=="QuickKill")bonusType = ScoreEffect::BonusType::QuickKill;

	auto effect = std::make_unique<ScoreEffect>(pos, score,bonusType);
	AddEffect(std::move(effect));
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