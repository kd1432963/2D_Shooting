#pragma once

#include"Application/Bullet/BulletBase.h"

struct BulletConfig;
class EnemyManager;
class CharaBase;

class HomingBullet :public BulletBase
{
public:

	//+++++++++++++++++++++++++++++++++++++++++
	// コンストラクタ
	//+++++++++++++++++++++++++++++++++++++++++
	HomingBullet(const BulletConfig& cfg);

public:

	//+++++++++++++++++++++++++++++++++++++++++
	// 基本ライフサイクル 
	//+++++++++++++++++++++++++++++++++++++++++
	void Update()override;
	void Draw2D()override;


	void SetEnemyManager(EnemyManager* e) { m_enemyManager = e; }

private:

	//+++++++++++++++++++++++++++++++++++++++++
	// ターゲット取得関数
	//+++++++++++++++++++++++++++++++++++++++++
	CharaBase* FindTarget();

private:

	// 切り取り範囲
	Math::Rectangle m_rect = { 0,0,0,0 };

	EnemyManager* m_enemyManager = nullptr;

	// ターゲット
	CharaBase* m_target = nullptr;

	Math::Vector2 m_dir;
	float speed = 8.0f;
};