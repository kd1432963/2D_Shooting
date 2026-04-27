#pragma once

#include "BulletBase.h"
#include "BulletType.h"

class EnemyManager;
class Player;

struct BulletConfig;

class BulletManager
{
public:

	//+++++++++++++++++++++++++++++++++++++++++
	// í«â¡
	//+++++++++++++++++++++++++++++++++++++++++
	void Add(const BulletConfig& cfg, BulletType type);

public:

	//+++++++++++++++++++++++++++++++++++++++++
	// äÓñ{èàóù
	//+++++++++++++++++++++++++++++++++++++++++
	void Update();
	void Draw2D();
	void DeleteDead();

public:

	//+++++++++++++++++++++++++++++++++++++++++
	// íeÉäÉXÉgéÊìæ
	//+++++++++++++++++++++++++++++++++++++++++
	const std::vector<std::unique_ptr<BulletBase>>& GetBullets() const
	{
		return m_bullets;
	}

public:

	void SetPlayer(Player* p) { mp_player = p; }
	void SetEnemyManager(EnemyManager* e) { mp_enemyManager = e; }

private:

	std::unique_ptr<BulletBase> CreateBullet(const BulletConfig& cfg, BulletType type);

private:

	std::vector<std::unique_ptr<BulletBase>> m_bullets;

	Player* mp_player = nullptr;
	EnemyManager* mp_enemyManager = nullptr;
};