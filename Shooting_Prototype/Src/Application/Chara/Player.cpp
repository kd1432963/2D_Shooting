#include "Player.h"

#include"PlayerConfig.h"

#include"Application/Bullet/BulletManager.h"
#include"Application/Bullet/BulletConfig.h"

using namespace PlayerConst;

//+++++++++++++++++++++++++++++++++++++++++
// 初期化処理
//+++++++++++++++++++++++++++++++++++++++++
Player::Player()
{
	//=== 判定情報 ========================

	hitbox.radius = kRadius;
	hitbox.pos = { kPosX,kPosY };

	//=== 画像情報取得 ====================

	tex = ASSET.GetTexture("Player");
	rect = ASSET.GetRectangle("Player");

	//=== 情報初期化 ======================

	pos = { kPosX,kPosY };
	scale = { kScaleX,kScaleY };
	rotate = 90.0f;
	move = { 0.0f,0.0f };

	//=== ステータス初期化 ================

	status.atk = kAtk;
	status.def = kDef;
	status.hp = kHp;
	status.maxHp = kHp;

	//=== 初期化した情報で行列更新 ========

	UpdateMatrix();
}

//+++++++++++++++++++++++++++++++++++++++++
// 更新処理
//+++++++++++++++++++++++++++++++++++++++++
void Player::Update()
{
	// 座標確定
	UpdatePos();

	// 行列更新
	UpdateMatrix();
}

//+++++++++++++++++++++++++++++++++++++++++
// 行動確定
//+++++++++++++++++++++++++++++++++++++++++
void Player::Action()
{
	// リキャストを減らす
	if (m_shotRecast >= 0.0f)--m_shotRecast;

	// 毎フレーム初期化
	move = { 0.0f,0.0f };

	// 入力されてるキーによって移動量決定
	if (KEY.IsPress('W'))move.y += kWalkPow;
	else if (KEY.IsPress('A'))move.x -= kWalkPow;
	else if (KEY.IsPress('S'))move.y -= kWalkPow;
	else if (KEY.IsPress('D'))move.x += kWalkPow;

	if (KEY.IsTrigger('Q'))
	{
		m_shotMode = BulletType::Homing;
	}

	else if (KEY.IsTrigger('E'))
	{
		m_shotMode = BulletType::Straight;
	}

	// 玉発射
	if (KEY.IsPress(VK_RETURN) && m_shotRecast <= 0.0f)
	{
		m_wantToShot = true;
		m_shotRecast = kShotRecastTime;
	}
}

//+++++++++++++++++++++++++++++++++++++++++
// 描画処理
//+++++++++++++++++++++++++++++++++++++++++
void Player::Draw2D()
{
	// 自機描画
	DrawChara();
}

void Player::Shot(BulletManager& b)
{
	BulletConfig cfg =
	{
		"Bullet",
		pos,
		{8,0.0f},
		status.atk,
		BulletOwner::Player
	};

	b.Add(cfg, m_shotMode);

	m_wantToShot = false;
}
