#include "StraightBullet.h"

#include"Application/Bullet/BulletConfig.h"

//+++++++++++++++++++++++++++++++++++++++++
// コンストラクタ
//+++++++++++++++++++++++++++++++++++++++++
StraightBullet::StraightBullet(const BulletConfig& cfg)
{
	// 当たり判定
	hitbox.pos = cfg.pos;
	hitbox.radius = 8.0f;
	radius = 8.0f;

	// テクスチャ取得
	tex = ASSET.GetTexture(cfg.texTag);
	m_rect = ASSET.GetRectangle(cfg.texTag);

	// 情報保存
	pos = cfg.pos;
	move = cfg.move;
	scale = { 1.0f, 1.0f };
	rotate = 0.0f;
	owner = cfg.owner;

	atk = cfg.atk;
}


//+++++++++++++++++++++++++++++++++++++++++
// 更新関数
//+++++++++++++++++++++++++++++++++++++++++
void StraightBullet::Update()
{
	// 座標確定
	UpdatePos();

	// 画面外にでていたら消す
	if (pos.x >= 640 + radius || pos.x <= -640 - radius)
	{
		isDead = true;
	}

	// 行列作成
	UpdateMatrix();
}

//+++++++++++++++++++++++++++++++++++++++++
// 描画関数
//+++++++++++++++++++++++++++++++++++++++++
void StraightBullet::Draw2D()
{
	// 弾描画
	SHADER.m_spriteShader.SetMatrix(mat);
	SHADER.m_spriteShader.DrawTex(tex, m_rect);
}
