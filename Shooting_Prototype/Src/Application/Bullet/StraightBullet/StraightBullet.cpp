#include "StraightBullet.h"

#include "Application/Bullet/BulletConfig.h"

//+++++++++++++++++++++++++++++++++++++++++
// コンストラクタ
//+++++++++++++++++++++++++++++++++++++++++
StraightBullet::StraightBullet(const BulletConfig& cfg)
{
	hitbox.pos = cfg.pos;
	hitbox.radius = 8.0f;
	radius = 8.0f;

	tex = ASSET.GetTexture(cfg.texTag);
	m_rect = ASSET.GetRectangle(cfg.texTag);

	pos = cfg.pos;
	move = cfg.move;
	scale = { 1.0f, 1.0f };
	rotate = 0.0f;
	owner = cfg.owner;

	atk = cfg.atk;
}

//+++++++++++++++++++++++++++++++++++++++++
// 更新
//+++++++++++++++++++++++++++++++++++++++++
void StraightBullet::Update()
{
	UpdatePos();

	// 画面外で消す（上下も対応）
	if (pos.x >= 640 + radius || pos.x <= -640 - radius ||
		pos.y >= 360 + radius || pos.y <= -360 - radius)
	{
		isDead = true;
	}

	UpdateMatrix();
}

//+++++++++++++++++++++++++++++++++++++++++
// 描画
//+++++++++++++++++++++++++++++++++++++++++
void StraightBullet::Draw2D()
{
	SHADER.m_spriteShader.SetMatrix(mat);
	SHADER.m_spriteShader.DrawTex(tex, m_rect);
}