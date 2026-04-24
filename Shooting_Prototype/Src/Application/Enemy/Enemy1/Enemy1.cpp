#include "Enemy1.h"

#include"Enemy1Config.h"

#include"Application/Bullet/BulletManager.h"
#include"Application/Bullet/BulletConfig.h"
#include"Application/Bullet/BulletType.h"

using namespace Enemy1Const;

Enemy1::Enemy1()
{//=== 画像情報取得 ====================

	tex = ASSET.GetTexture("Enemy1");
	rect = ASSET.GetRectangle("Enemy1");

	//=== 情報初期化 ======================

	pos = {kPosX,kPosY};
	scale = { kScaleX,kScaleY };
	rotate = 0.0f;
	move = { 0.0f,0.0f };
	hitbox.radius = 16.0f;
	status.hp = kHp;

	//=== 初期化した情報で行列更新 ========

	UpdateMatrix();
}

Enemy1::Enemy1(const Math::Vector2 p)
{
	//=== 画像情報取得 ====================

	tex = ASSET.GetTexture("Enemy1");
	rect = ASSET.GetRectangle("Enemy1");

	//=== 情報初期化 ======================

	pos =  p ;
	scale = { kScaleX,kScaleY };
	rotate = 0.0f;
	move = { 0.0f,0.0f };
	hitbox.radius = 16.0f;
	status.hp = kHp;

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



	++t;
	if (t %20  == 0)
	{
		m_wantToShot = true;
	}
}

void Enemy1::Draw2D()
{
	// 敵描画
	DrawChara();
}

void Enemy1::Shot(BulletManager& b)
{
	BulletConfig cfg;
	cfg.texTag = "Bullet";
	cfg.pos = pos;
	cfg.move = { -5, 0 };
	cfg.atk = 5;
	cfg.owner = BulletOwner::Enemy;

	b.Add(cfg, BulletType::Straight);

	m_wantToShot = false;
}

