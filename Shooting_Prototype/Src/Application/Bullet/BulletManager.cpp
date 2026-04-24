#include "BulletManager.h"

#include "Application/Enemy/EnemyManager.h"

#include "Application/Bullet/BulletConfig.h"
#include "Application/Bullet/StraightBullet/StraightBullet.h"
#include "Application/Bullet/HomingBullet/HomingBullet.h"

//+++++++++++++++++++++++++++++++++++++++++
// í«â¡
//+++++++++++++++++++++++++++++++++++++++++
void BulletManager::Add(const BulletConfig& cfg, BulletType type)
{
	m_bullets.emplace_back(CreateBullet(cfg, type));
}

//+++++++++++++++++++++++++++++++++++++++++
// çXêV
//+++++++++++++++++++++++++++++++++++++++++
void BulletManager::Update()
{
	for (auto& b : m_bullets)
	{
		b->Update();
	}

	m_bullets.erase
	(
		std::remove_if
		(
			m_bullets.begin(),
			m_bullets.end(),
			[](const std::unique_ptr<BulletBase>& b)
			{
				return b->IsDead();
			}
		),
		m_bullets.end()
	);
}

//+++++++++++++++++++++++++++++++++++++++++
// ï`âÊ
//+++++++++++++++++++++++++++++++++++++++++
void BulletManager::Draw2D()
{
	for (auto& b : m_bullets)
	{
		b->Draw2D();
	}
}

//+++++++++++++++++++++++++++++++++++++++++
// ê∂ê¨
//+++++++++++++++++++++++++++++++++++++++++
std::unique_ptr<BulletBase> BulletManager::CreateBullet(const BulletConfig& cfg, BulletType type)
{
	switch (type)
	{
	case BulletType::Straight:
		return std::make_unique<StraightBullet>(cfg);

	case BulletType::Homing:
	{
		auto b = std::make_unique<HomingBullet>(cfg);
		b->SetPlayer(mp_player);
		b->SetEnemyManager(mp_enemyManager);
		return b;
	}
	}

	return nullptr;
}