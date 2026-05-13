#include "EnemyManager.h"

#include "Application/Bullet/BulletManager.h"

//+++++++++++++++++++++++++++++++++++++++++
// XV
//+++++++++++++++++++++++++++++++++++++++++
void EnemyManager::Update()
{
	for (auto& e : m_enemies)
	{
		e->Update();
	}
}

//+++++++++++++++++++++++++++++++++++++++++
// s“®
//+++++++++++++++++++++++++++++++++++++++++
void EnemyManager::Action()
{
	for (auto& e : m_enemies)
	{
		e->Action();
	}
}

//+++++++++++++++++++++++++++++++++++++++++
// •`‰æ
//+++++++++++++++++++++++++++++++++++++++++
void EnemyManager::Draw2D()
{
	for (auto& e : m_enemies)
	{
		e->Draw2D();
	}
}

//+++++++++++++++++++++++++++++++++++++++++
// ’eˆ—
//+++++++++++++++++++++++++++++++++++++++++
void EnemyManager::Shot(BulletManager& b)
{
	for (auto& e : m_enemies)
	{
		if (e->WantToShot())
		{
			e->Shot(b);
		}
	}
}

//+++++++++++++++++++++++++++++++++++++++++
// €–Síœ
//+++++++++++++++++++++++++++++++++++++++++
void EnemyManager::DeleteDead()
{
	m_enemies.erase(
		std::remove_if(
			m_enemies.begin(),
			m_enemies.end(),
			[](const auto& e) { return e->IsDead() || e->IsSystemDead(); }
		),
		m_enemies.end()
	);
}

//+++++++++++++++++++++++++++++++++++++++++
// ’†ƒ{ƒX‚ª‚¢‚é‚©‚Ç‚¤‚©
//+++++++++++++++++++++++++++++++++++++++++
bool EnemyManager::IsMidBossAlive()
{
	for (auto& e : m_enemies)
	{
		if (e->GetType() == EnemyType::Enemy2)
		{
			m_bossHP = e->GetHp();
			m_bossMaxHP = e->GetMaxHp();
			return true;
		}
	}
	return false;
}

//+++++++++++++++++++++++++++++++++++++++++
// ƒ{ƒX‚ª‚¢‚é‚©‚Ç‚¤‚©
//+++++++++++++++++++++++++++++++++++++++++
bool EnemyManager::IsBossAlive()
{
	for (auto& e : m_enemies)
	{
		if (e->GetType() == EnemyType::Boss)
		{
			m_bossHP = e->GetHp();
			m_bossMaxHP = e->GetMaxHp();
			return true;
		}
	}
	return false;
}
