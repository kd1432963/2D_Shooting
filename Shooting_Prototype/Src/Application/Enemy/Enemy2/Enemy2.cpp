#include"Eneny2.h"
#include "Enemy2Config.h"

#include"Application/GameObject/RectHitBox.h"
#include"Application/Chara/Player.h"

using namespace Enemy2Const;

//+++++++++++++++++++++++++++++++++++++++++
// 初期化
//+++++++++++++++++++++++++++++++++++++++++
Enemy2::Enemy2(const Math::Vector2& p, Player* player)
	:EnemyBase(EnemyType::Enemy2)
{
	mp_player = player;
	hitbox = std::make_unique<RectHitBox>(32, 32);
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
// 更新
//+++++++++++++++++++++++++++++++++++++++++
void Enemy2::Update()
{
	UpdateAnim();
	UpdatePos();

	// Y座標の画面制御
	pos.y = Clamp(pos.y, -241.5f + 15.0f, 241.5f - 15.0f);
	hitbox->pos = pos;

	// X座標の画面制御
	if (pos.x < -640 - 15)
	{
		SystemKill();
	}

	UpdateMatrix();
}

//+++++++++++++++++++++++++++++++++++++++++
// 行動
//+++++++++++++++++++++++++++++++++++++++++
void Enemy2::Action()
{
	move = { 0.0f, 0.0f };

	if (mp_player)
	{
		float Bonus = mp_player->GetPos().x > pos.x ? 2.5f : 1.0f;

		Math::Vector2 desired = mp_player->GetPos() - pos;
		desired.Normalize();
		desired *= kMovePow*Bonus;

		velocity += (desired - velocity) * 0.035f;

		move = velocity;
	}
}

//+++++++++++++++++++++++++++++++++++++++++
// 描画
//+++++++++++++++++++++++++++++++++++++++++
void Enemy2::Draw2D()
{
	CalcDrawRect();

	SHADER.m_spriteShader.SetMatrix(mat);
	Math::Color color = {};

	float t = ToFloat(status.hp) / status.maxHp;

	color = { 1,1,1,1};
	SHADER.m_spriteShader.DrawTex(tex,0,0, &rect,&color);

	DebugDraw();
}