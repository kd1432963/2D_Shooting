#include "StraightBullet.h"

//+++++++++++++++++++++++++++++++++++++++++
// コンストラクタ
//+++++++++++++++++++++++++++++++++++++++++
StraightBullet::StraightBullet(const std::string& texTag, const Math::Vector2& p, const Math::Vector2& m)
{
	// 当たり判定
	hitbox.pos = p;
	hitbox.radius = 8.0f;

	// テクスチャ取得
	tex = ASSET.GetTexture(texTag);
	m_rect = ASSET.GetRectangle(texTag);

	// 情報保存
	pos = p;
	move = m;
	scale = { 1.0f, 1.0f };
	rotate = 0.0f;

	atk = 10;
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
