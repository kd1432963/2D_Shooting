#pragma once

#include"Application/Bullet/BulletBase.h"

struct BulletConfig;
class EnemyManager;

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

	// 切り取り範囲
	Math::Rectangle m_rect = { 0,0,0,0 };

	EnemyManager* m_enemyManager = nullptr;
};