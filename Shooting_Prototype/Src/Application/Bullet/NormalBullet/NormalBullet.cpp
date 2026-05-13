#include "NormalBullet.h"

#include "Application/Bullet/BulletConfig.h"

#include"Application/GameObject/CircleHitBox.h"

NormalBullet::NormalBullet(const BulletConfig& cfg)
{
	hitbox = std::make_unique<CircleHitBox>(8);
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

void NormalBullet::Update()
{
	UpdatePos();

	if (pos.x >= Screen::Right + radius + 100 || pos.x <= Screen::Left - radius - 100 ||
		pos.y >= Screen::Top + radius || pos.y <= Screen::Bottom - radius)
	{
		isDead = true;
	}

	UpdateAnim();

	UpdateMatrix();
}

void NormalBullet::Draw2D()
{
	SHADER.m_spriteShader.SetMatrix(mat);

	// Œ»Ý‚ÌƒtƒŒ[ƒ€‚Ì‹éŒ`
	Math::Rectangle animRect(
		m_rect.x + 24 * animFrame,
		m_rect.y,
		24,
		m_rect.height
	);

	SHADER.m_spriteShader.DrawTex(tex, animRect);

	DebugDraw();
}
