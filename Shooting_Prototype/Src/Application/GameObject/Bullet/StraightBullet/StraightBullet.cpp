#include "StraightBullet.h"

//+++++++++++++++++++++++++++++++++++++++++
// コンストラクタ
//+++++++++++++++++++++++++++++++++++++++++
StraightBullet::StraightBullet(const std::string& texTag, const Math::Vector2& p, const Math::Vector2& m)
{
	//=== 画像タグ保存 ====================

	tag = texTag;

	//=== 情報保存 ========================

	pos = p;
	move = m;
}

void StraightBullet::Init()
{
	//=== 画像情報取得 ====================

	tex = ASSET.GetTexture(tag);
	m_rect = ASSET.GetRectangle(tag);

	//===  情報初期化 =====================

	scale = { 1.0f,1.0f };
	rotate = 0.0f;
	radius = 8.0f * scale.x;
}

//+++++++++++++++++++++++++++++++++++++++++
// 更新関数
//+++++++++++++++++++++++++++++++++++++++++
void StraightBullet::Update()
{
	// 座標確定
	pos += move;

	// 画面外にでていたら消す
	if (pos.x >= 640 + radius || pos.x <= -640 - radius)
	{
		isDead = true;
	}

	// 行列作成
	UpdateMatrix();
}

void StraightBullet::Action()
{

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
