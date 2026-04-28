#include "Enemy1.h"

#include "Enemy1Config.h"
#include "Application/Bullet/BulletManager.h"
#include "Application/Bullet/BulletConfig.h"
#include "Application/Bullet/BulletType.h"
#include"Application/GameObject/CircleHitBox.h"

using namespace Enemy1Const;

//+++++++++++++++++++++++++++++++++++++++++
// èâä˙âª
//+++++++++++++++++++++++++++++++++++++++++
Enemy1::Enemy1()
{
	hitbox = std::make_unique<CircleHitBox>(kRadius);
	if (hitbox)
	{
		hitbox->pos = { kPosX, kPosY };
	}

	tex = ASSET.GetTexture("Enemy1");
	rect = ASSET.GetRectangle("Enemy1");

	pos = { kPosX, kPosY };
	scale = { kScaleX, kScaleY };
	rotate = 0.0f;
	move = { 0.0f, 0.0f };

	status.hp = kHp;
	status.maxHp = kHp;
	status.atk = kAtk;
	status.def = kDef;

	UpdateMatrix();
}

Enemy1::Enemy1(const Math::Vector2&p)
{
	hitbox = std::make_unique<CircleHitBox>(kRadius);
	if (hitbox)
	{
		hitbox->pos = { kPosX, kPosY };
	}

	tex = ASSET.GetTexture("Enemy1");
	rect = ASSET.GetRectangle("Enemy1");

	pos = p;
	scale = { kScaleX, kScaleY };
	rotate = 0.0f;
	move = { 0.0f, 0.0f };

	status.hp = kHp;
	status.maxHp = kHp;
	status.atk = kAtk;
	status.def = kDef;

	UpdateMatrix();
}

//+++++++++++++++++++++++++++++++++++++++++
// çXêV
//+++++++++++++++++++++++++++++++++++++++++
void Enemy1::Update()
{
	UpdatePos();
	UpdateMatrix();
}

//+++++++++++++++++++++++++++++++++++++++++
// çsìÆ
//+++++++++++++++++++++++++++++++++++++++++
void Enemy1::Action()
{
	move = { 0.0f, 0.0f };

	//move.x = RandomRangeF(-3.0f, 3.0f);
	//move.y = RandomRangeF(-3.0f, 3.0f);

	++t;

	move.x = -1.0f; // ÇŸÇ⁄å≈íË
	move.y = sinf(t * 0.1f) * 2.0f;

	if (t % 90 == 0)
	{
		m_wantToShot = true;
	}
}

//+++++++++++++++++++++++++++++++++++++++++
// ï`âÊ
//+++++++++++++++++++++++++++++++++++++++++
void Enemy1::Draw2D()
{
	DrawChara();
}

//+++++++++++++++++++++++++++++++++++++++++
// çUåÇ
//+++++++++++++++++++++++++++++++++++++++++
void Enemy1::Shot(BulletManager& b)
{
	BulletConfig cfg;
	cfg.texTag = "Straight";
	cfg.pos = pos;
	cfg.move = { -5, 0 };
	cfg.atk = 5;
	cfg.owner = BulletOwner::Enemy;

	b.Add(cfg, BulletType::Straight);

	m_wantToShot = false;
}