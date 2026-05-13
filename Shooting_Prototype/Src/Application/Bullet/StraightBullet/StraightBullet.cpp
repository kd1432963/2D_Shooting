#include "StraightBullet.h"

#include "Application/Bullet/BulletConfig.h"

#include"Application/GameObject/RectHitBox.h"

//+++++++++++++++++++++++++++++++++++++++++
// コンストラクタ
//+++++++++++++++++++++++++++++++++++++++++
StraightBullet::StraightBullet(const BulletConfig& cfg)
{
	hitbox = std::make_unique<RectHitBox>(8,3);
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

//+++++++++++++++++++++++++++++++++++++++++
// 更新
//+++++++++++++++++++++++++++++++++++++++++
void StraightBullet::Update()
{
	UpdatePos();

	if (pos.x >= Screen::Right + radius+100 || pos.x <= Screen::Left - radius-100 ||
		pos.y >= Screen::Top + radius || pos.y <= Screen::Bottom - radius)
	{
		isDead = true;
	}

	UpdateAnim();

	UpdateMatrix();
}

//+++++++++++++++++++++++++++++++++++++++++
// 描画
//+++++++++++++++++++++++++++++++++++++++++
void StraightBullet::Draw2D()
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