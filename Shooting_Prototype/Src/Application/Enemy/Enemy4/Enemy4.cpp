#include "Enemy4.h"
#include "Enemy4Config.h"

#include "Application/GameObject/RectHitBox.h"
#include "Application/Bullet/BulletManager.h"
#include "Application/Bullet/BulletConfig.h"
#include "Application/Bullet/BulletType.h"

using namespace Enemy4Const;

//+++++++++++++++++++++++++++++++++++++++++
// 初期化
//+++++++++++++++++++++++++++++++++++++++++
Enemy4::Enemy4(const Math::Vector2& p)
{
	hitbox = std::make_unique<RectHitBox>(15, 15);
	if (hitbox)
	{
		hitbox->pos = p;
	}

	tex = ASSET.GetTexture("Enemy4");
	rect = ASSET.GetRectangle("Enemy4");

	pos = p;
	basePos = p;
	scale = { kScaleX, kScaleY };
	rotate = 0.0f;

	status.hp = kHp;
	status.maxHp = kHp;
	status.atk = kAtk;

	UpdateMatrix();
}

//+++++++++++++++++++++++++++++++++++++++++
// 更新
//+++++++++++++++++++++++++++++++++++++++++
void Enemy4::Update()
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
void Enemy4::Action()
{
	m_aliveTime++;
	m_shotWait++;

	// 左へゆっくり移動
	move.x = -1.5f;

	// 波の速さ
	float speed = 0.05f;
	// 振れ幅
	float amplitude = 100.0f;

	// 目標座標は 100 ~ -100
	float targetY = basePos.y + sinf(m_aliveTime * speed) * amplitude;

	move.y = targetY - pos.y;

	// 弾を撃つ
	if (m_shotWait > 90)
	{
		wantToShot = true;
		m_shotWait = 0;
	}
}

//+++++++++++++++++++++++++++++++++++++++++
// 描画
//+++++++++++++++++++++++++++++++++++++++++
void Enemy4::Draw2D()
{
	CalcDrawRect();
	DrawChara();
}

//+++++++++++++++++++++++++++++++++++++++++
// 攻撃
//+++++++++++++++++++++++++++++++++++++++++
void Enemy4::Shot(BulletManager& b)
{
	BulletConfig cfg;
	cfg.texTag = "Enemy4Bullet";
	cfg.pos = pos;
	cfg.move = { -3.0f, 0.0f }; // Enemy1 より遅い
	cfg.atk = status.atk;
	cfg.owner = BulletOwner::Enemy;

	b.Add(cfg, BulletType::Straight);

	wantToShot = false;
}
