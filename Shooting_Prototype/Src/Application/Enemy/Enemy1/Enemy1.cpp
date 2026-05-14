#include "Enemy1.h"

#include "Enemy1Config.h"
#include "Application/Bullet/BulletManager.h"
#include "Application/Bullet/BulletConfig.h"
#include "Application/Bullet/BulletType.h"
#include"Application/GameObject/RectHitBox.h"

using namespace Enemy1Const;

//+++++++++++++++++++++++++++++++++++++++++
// 初期化
//+++++++++++++++++++++++++++++++++++++++++
Enemy1::Enemy1(const Math::Vector2& p)
	:EnemyBase(EnemyType::Enemy1)
{
	hitbox = std::make_unique<RectHitBox>(15, 15);
	if (hitbox)
	{
		hitbox->pos = p;
	}

	tex = ASSET.GetTexture("Enemy1");
	rect = ASSET.GetRectangle("Enemy1");

	pos = p;
	basePos = p;
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
void Enemy1::Update()
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
void Enemy1::Action()
{
	// 初期フレームでは動かさない
	if (m_aliveTime == 0)
	{
		move = { 0, 0 };
		++m_aliveTime;
		return;
	}

	move = { 0.0f, 0.0f };

	++m_shotWait;
	++m_aliveTime;

	move.x = -1.0f; // ほぼ固定

	// 波の速さ
	float speed = 0.1f;
	// 振れ幅
	float amplitude = 25.0f;

	// 目標座標は 25 ~ -25
	float targetY = basePos.y + sinf(m_aliveTime * speed) * amplitude;

	move.y = targetY - pos.y;

	if (m_shotWait > 120)
	{
		wantToShot = true;
		m_shotWait = 0;
	}
}

//+++++++++++++++++++++++++++++++++++++++++
// 描画
//+++++++++++++++++++++++++++++++++++++++++
void Enemy1::Draw2D()
{
	CalcDrawRect();

	DrawChara();
}

//+++++++++++++++++++++++++++++++++++++++++
// 攻撃
//+++++++++++++++++++++++++++++++++++++++++
void Enemy1::Shot(BulletManager& b)
{
	BulletConfig cfg;
	cfg.texTag = "Enemy1Bullet";
	cfg.pos = pos;
	cfg.move = { -4, 0 };
	cfg.atk = status.atk;
	cfg.owner = BulletOwner::Enemy;

	b.Add(cfg, BulletType::Straight);

	SOUND.PlaySE("EnemyShotSE");

	wantToShot = false;
}