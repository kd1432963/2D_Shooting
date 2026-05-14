#include "EnemyManager.h"

#include "Application/Bullet/BulletManager.h"

//+++++++++++++++++++++++++++++++++++++++++
// 更新
//+++++++++++++++++++++++++++++++++++++++++
void EnemyManager::Update()
{
	for (auto& e : m_enemies)
	{
		e->Update();
	}
}

//+++++++++++++++++++++++++++++++++++++++++
// 行動
//+++++++++++++++++++++++++++++++++++++++++
void EnemyManager::Action()
{
	for (auto& e : m_enemies)
	{
		e->Action();
	}
}

//+++++++++++++++++++++++++++++++++++++++++
// 描画
//+++++++++++++++++++++++++++++++++++++++++
void EnemyManager::Draw2D()
{
	for (auto& e : m_enemies)
	{
		e->Draw2D();
	}
}

//+++++++++++++++++++++++++++++++++++++++++
// 弾処理
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
// 死亡削除
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
// 中ボスがいるかどうか
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
// ボスがいるかどうか
//+++++++++++++++++++++++++++++++++++++++++
bool EnemyManager::IsBossAlive()
{
	for (auto& e : m_enemies)
	{
		if (e->GetType() == EnemyType::Boss)
		{
			m_bossHP = e->GetHp();
			m_bossMaxHP = e->GetMaxHp();

			// ほんまにごめんなさい
			if (m_bossHP <= 0)SOUND.StopBGM();

			return true;
		}
	}
	return false;
}
