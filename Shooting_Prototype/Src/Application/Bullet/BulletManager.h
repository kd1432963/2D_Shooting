#pragma once

#include"BulletBase.h"

#include"BulletType.h"

class EnemyManager;
class Player;
class BulletBase;

struct BulletConfig;

class BulletManager
{
public:

	//+++++++++++++++++++++++++++++++++++++++++
	// 追加関数
	//+++++++++++++++++++++++++++++++++++++++++
	void Add(const BulletConfig& cfg, BulletType type);

	//+++++++++++++++++++++++++++++++++++++++++
	// 基本ライフサイクル
	//+++++++++++++++++++++++++++++++++++++++++
	void Update();
	void Draw2D();

	//+++++++++++++++++++++++++++++++++++++++++
	// 弾リストの参照を返す
	//+++++++++++++++++++++++++++++++++++++++++
	const std::vector<std::unique_ptr<BulletBase>>& GetBullets() const { return m_bullets; }

public:

	//+++++++++++++++++++++++++++++++++++++++++
	// プレイヤーの登録
	//+++++++++++++++++++++++++++++++++++++++++
	void SetPlayer(Player* p) { mp_player = p; }
	//+++++++++++++++++++++++++++++++++++++++++
	// 敵リストの登録
	//+++++++++++++++++++++++++++++++++++++++++
	void SetEnemyManager(EnemyManager* e) { mp_enemyManager = e; }

private:

	//+++++++++++++++++++++++++++++++++++++++++
	// 生成関数
	//+++++++++++++++++++++++++++++++++++++++++
	std::unique_ptr<BulletBase>CreateBullet(const BulletConfig& cfg, BulletType type);

private:

	//+++++++++++++++++++++++++++++++++++++++++
	// 弾リスト
	//+++++++++++++++++++++++++++++++++++++++++
	std::vector<std::unique_ptr<BulletBase>> m_bullets;

	//+++++++++++++++++++++++++++++++++++++++++
	// プレイヤー
	//+++++++++++++++++++++++++++++++++++++++++
	Player* mp_player = nullptr;

	//+++++++++++++++++++++++++++++++++++++++++
	// 敵マネージャー
	//+++++++++++++++++++++++++++++++++++++++++
	EnemyManager* mp_enemyManager = nullptr;
};