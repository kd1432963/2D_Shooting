#pragma once

#include "Application/Bullet/BulletBase.h"

struct BulletConfig;

class PiercingBullet : public BulletBase
{
public:

	//+++++++++++++++++++++++++++++++++++++++++
	// コンストラクタ
	//+++++++++++++++++++++++++++++++++++++++++
	PiercingBullet(const BulletConfig& cfg);

public:

	//+++++++++++++++++++++++++++++++++++++++++
	// 基本処理
	//+++++++++++++++++++++++++++++++++++++++++
	void Update() override;
	void Draw2D() override;

public:

	//+++++++++++++++++++++++++++++++++++++++++
	// 貫通弾なので数回耐える
	//+++++++++++++++++++++++++++++++++++++++++
	void SetDead()override;

private:

	static constexpr int MAX_PIERCE = 4;

	Math::Rectangle m_rect = { 0,0,0,0 };
	int m_pierceCount = 0;
};