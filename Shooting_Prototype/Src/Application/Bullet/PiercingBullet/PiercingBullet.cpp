#include "PiercingBullet.h"

#include "Application/Bullet/BulletConfig.h"

#include"Application/GameObject/RectHitBox.h"

PiercingBullet::PiercingBullet(const BulletConfig& cfg)
{
	hitbox = std::make_unique<RectHitBox>(11, 11);
	if (hitbox)
	{
		hitbox->pos = cfg.pos;
	}

	tex = ASSET.GetTexture(cfg.texTag);
	m_rect = ASSET.GetRectangle(cfg.texTag);

	pos = cfg.pos;
	move = cfg.move;
	scale = { 1.0f, 1.0f };
	rotate = 0.0f;
	owner = cfg.owner;

	atk = cfg.atk;

	animMaxFrame = 8;
	animStep = 5;
}

void PiercingBullet::Update()
{
	UpdatePos();

	// 画面外で消す（上下も対応）
	if (pos.x >= 640 + radius || pos.x <= -640 - radius ||
		pos.y >= 360 + radius || pos.y <= -360 - radius)
	{
		isDead = true;
	}

	UpdateAnim();

	UpdateMatrix();
}

void PiercingBullet::Draw2D()
{
	SHADER.m_spriteShader.SetMatrix(mat);

	// 現在のフレームの矩形
	Math::Rectangle animRect(
		m_rect.x + 24 * animFrame,
		m_rect.y,
		24,
		m_rect.height
	);

	SHADER.m_spriteShader.DrawTex(tex, animRect);

	DebugDraw();
}

void PiercingBullet::SetDead()
{
	if (m_pierceCount < MAX_PIERCE)
	{
		++m_pierceCount;
	}
	else
	{
		isDead = true;
	}
}
