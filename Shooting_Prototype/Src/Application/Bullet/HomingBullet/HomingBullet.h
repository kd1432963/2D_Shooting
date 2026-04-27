#pragma once

#include "Application/Bullet/BulletBase.h"

struct BulletConfig;
class EnemyManager;
class CharaBase;
class Player;

class HomingBullet : public BulletBase
{
public:

	//+++++++++++++++++++++++++++++++++++++++++
	// コンストラクタ
	//+++++++++++++++++++++++++++++++++++++++++
	HomingBullet(const BulletConfig& cfg);

public:

	//+++++++++++++++++++++++++++++++++++++++++
	// 基本処理
	//+++++++++++++++++++++++++++++++++++++++++
	void Update() override;
	void Draw2D() override;

	void SetPlayer(Player* p) { mp_player = p; }
	void SetEnemyManager(EnemyManager* e) { mp_enemyManager = e; }

private:

	CharaBase* FindTarget();

private:

	Math::Rectangle m_rect = { 0,0,0,0 };

	Player* mp_player = nullptr;
	EnemyManager* mp_enemyManager = nullptr;
	CharaBase* m_target = nullptr;

	Math::Vector2 m_dir = { 0.0f, 0.0f };
	float m_speed = 12.0f;
};