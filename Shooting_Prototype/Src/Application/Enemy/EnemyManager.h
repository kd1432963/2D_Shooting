#pragma once

#include "EnemyBase.h"

class BulletManager;

class EnemyManager
{
public:

	//**********************************
	// “G’Ç‰Á
	//**********************************
	template <class T, class... Args>
	T* AddEnemy(Args&&... args)
	{
		static_assert(std::is_base_of_v<EnemyBase, T>, "T must inherit EnemyBase");

		auto enemy = std::make_unique<T>(std::forward<Args>(args)...);
		T* raw = enemy.get();

		m_enemies.emplace_back(std::move(enemy));

		return raw;
	}

public:

	//**********************************
	// Šî–{ˆ—
	//**********************************
	void Update();
	void Action();
	void Draw2D();
	void Shot(BulletManager& b);
	void DeleteDead();

public:

	//**********************************
	// “GƒŠƒXƒgæ“¾
	//**********************************
	const std::vector<std::unique_ptr<EnemyBase>>& GetEnemies() const
	{
		return m_enemies;
	}

private:

	std::vector<std::unique_ptr<EnemyBase>> m_enemies;
};