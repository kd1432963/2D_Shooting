#include"Eneny2.h"
#include "Enemy2Config.h"

#include"Application/GameObject/CircleHitBox.h"
#include"Application/Chara/Player.h"

using namespace Enemy2Const;

//+++++++++++++++++++++++++++++++++++++++++
// èâä˙âª
//+++++++++++++++++++++++++++++++++++++++++
Enemy2::Enemy2(const Math::Vector2& p, Player* player)
{
	mp_player = player;

	hitbox = std::make_unique<CircleHitBox>(kRadius);
	if (hitbox)
	{
		hitbox->pos = p;
	}

	tex = ASSET.GetTexture("Enemy2");
	rect = ASSET.GetRectangle("Enemy2");

	pos = p;
	scale = { kScaleX, kScaleY };
	rotate = 0.0f;
	move = { 0.0f, 0.0f };

	status.hp = kHp;
	status.maxHp = kHp;
	status.atk = kAtk;

	UpdateMatrix();
}

//+++++++++++++++++++++++++++++++++++++++++
// çXêV
//+++++++++++++++++++++++++++++++++++++++++
void Enemy2::Update()
{
	UpdatePos();
	UpdateMatrix();
}

//+++++++++++++++++++++++++++++++++++++++++
// çsìÆ
//+++++++++++++++++++++++++++++++++++++++++
void Enemy2::Action()
{
	move = { 0.0f, 0.0f };

	if (mp_player)
	{
		Math::Vector2 desired = mp_player->GetPos() - pos;
		desired.Normalize();
		desired *= kMovePow;

		velocity += (desired - velocity) * 0.075f;

		move = velocity;
	}
}

//+++++++++++++++++++++++++++++++++++++++++
// ï`âÊ
//+++++++++++++++++++++++++++++++++++++++++
void Enemy2::Draw2D()
{
	DrawChara();
}