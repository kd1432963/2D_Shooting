#pragma once

#include"Application/Bullet/BulletBase.h"

struct BulletConfig;

class StraightBullet :public BulletBase
{
public:

	//+++++++++++++++++++++++++++++++++++++++++
	// コンストラクタ
	//+++++++++++++++++++++++++++++++++++++++++
	StraightBullet(const BulletConfig& cfg);

public:

	//+++++++++++++++++++++++++++++++++++++++++
	// 基本ライフサイクル 
	//+++++++++++++++++++++++++++++++++++++++++
	void Update()override;
	void Draw2D()override;


private:

	// 切り取り範囲
	Math::Rectangle m_rect = { 0,0,0,0 };

};