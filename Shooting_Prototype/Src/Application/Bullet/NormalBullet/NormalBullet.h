#pragma once

#include "Application/Bullet/BulletBase.h"

struct BulletConfig;

class NormalBullet : public BulletBase
{
public:

	//+++++++++++++++++++++++++++++++++++++++++
	// コンストラクタ
	//+++++++++++++++++++++++++++++++++++++++++
	NormalBullet(const BulletConfig& cfg);

public:

	//+++++++++++++++++++++++++++++++++++++++++
	// 基本処理
	//+++++++++++++++++++++++++++++++++++++++++
	void Update() override;
	void Draw2D() override;

private:

	Math::Rectangle m_rect = { 0,0,0,0 };
};