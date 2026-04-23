#pragma once

#include"Application/Bullet/BulletBase.h"

class StraightBullet :public BulletBase
{
public:

	//+++++++++++++++++++++++++++++++++++++++++
	// コンストラクタ
	//+++++++++++++++++++++++++++++++++++++++++
	StraightBullet(const std::string& texTug, const Math::Vector2& p, const Math::Vector2& m);

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