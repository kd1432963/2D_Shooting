#include "Enemy1.h"

#include"Enemy1Config.h"

using namespace Enemy1Const;

void Enemy1::Init()
{
	//=== 画像情報取得 ====================

	tex = ASSET.GetTexture("Enemy1");
	rect = ASSET.GetRectangle("Enemy1");

	//=== 情報初期化 ======================

	pos = { kPosX,kPosY };
	scale = { kScaleX,kScaleY };
	rotate = 0.0f;
	move = { 0.0f,0.0f };
	hitbox.radius = 16.0f;

	//=== 初期化した情報で行列更新 ========

	UpdateMatrix();
}

void Enemy1::Update()
{
	// 座標確定
	UpdatePos();




	// 行列更新
	UpdateMatrix();
}

void Enemy1::Action()
{

	move = { 0.0f,0.0f };

	move.x = RandomRangeF(-3.0f, 3.0f);
	move.y = RandomRangeF(-3.0f, 3.0f);
}

void Enemy1::Draw2D()
{
	// 敵描画
	DrawChara();
}
