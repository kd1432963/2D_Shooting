#include "Player.h"

#include "PlayerConfig.h"
#include "Application/Bullet/BulletManager.h"
#include "Application/Bullet/BulletConfig.h"

using namespace PlayerConst;

//+++++++++++++++++++++++++++++++++++++++++
// 初期化
//+++++++++++++++++++++++++++++++++++++++++
Player::Player()
{
	hitbox.radius = kRadius;
	hitbox.pos = { kPosX, kPosY };

	tex = ASSET.GetTexture("Player");
	rect = ASSET.GetRectangle("Player");

	pos = { kPosX, kPosY };
	scale = { kScaleX, kScaleY };
	rotate = 90.0f;
	move = { 0.0f, 0.0f };

	status.atk = kAtk;
	status.def = kDef;
	status.hp = kHp;
	status.maxHp = kHp;

	UpdateMatrix();
}

//+++++++++++++++++++++++++++++++++++++++++
// 更新
//+++++++++++++++++++++++++++++++++++++++++
void Player::Update()
{
	UpdatePos();
	UpdateMatrix();
}

//+++++++++++++++++++++++++++++++++++++++++
// 行動
//+++++++++++++++++++++++++++++++++++++++++
void Player::Action()
{
	if (m_shotRecast > 0.0f)
		--m_shotRecast;

	MoveInput();
	ChangeShotMode();
	ShotInput();
}

//+++++++++++++++++++++++++++++++++++++++++
// 入力：移動
//+++++++++++++++++++++++++++++++++++++++++
void Player::MoveInput()
{
	move = { 0.0f, 0.0f };

	if (KEY.IsPress('W')) move.y += kWalkPow;
	else if (KEY.IsPress('A')) move.x -= kWalkPow;
	else if (KEY.IsPress('S')) move.y -= kWalkPow;
	else if (KEY.IsPress('D')) move.x += kWalkPow;

	float fPosX = pos.x + move.x;
	float fPosY = pos.y + move.y;

	if (fPosX + kRadius >= 640 || fPosX - kRadius <= -640)
	{
		move.x = 0.0f;
	}

	if (fPosY + kRadius >= 241.5f || fPosY - kRadius <= -241.5f)
	{
		move.y = 0.0f;
	}

}

//+++++++++++++++++++++++++++++++++++++++++
// 入力：ショットモード変更
//+++++++++++++++++++++++++++++++++++++++++
void Player::ChangeShotMode()
{
	if (KEY.IsTrigger('Q'))
		m_shotMode = BulletType::Homing;
	else if (KEY.IsTrigger('E'))
		m_shotMode = BulletType::Straight;
}

//+++++++++++++++++++++++++++++++++++++++++
// 入力：発射判定
//+++++++++++++++++++++++++++++++++++++++++
void Player::ShotInput()
{
	if (KEY.IsPress(VK_RETURN) && m_shotRecast <= 0.0f)
	{
		m_wantToShot = true;
		m_shotRecast = kShotRecastTime;
	}
}

//+++++++++++++++++++++++++++++++++++++++++
// 描画
//+++++++++++++++++++++++++++++++++++++++++
void Player::Draw2D()
{
	DrawChara();
}

//+++++++++++++++++++++++++++++++++++++++++
// 弾発射
//+++++++++++++++++++++++++++++++++++++++++
void Player::Shot(BulletManager& b)
{
	BulletConfig cfg =
	{
		"Straight",
		pos,
		{kShotPow, 0.0f},
		status.atk,
		BulletOwner::Player
	};

	switch (m_shotMode)
	{
	case BulletType::Straight:
		cfg.texTag = "Straight";
			break;

	case BulletType::Homing:
		cfg.texTag = "Homing";
		break;
	}

	b.Add(cfg, m_shotMode);

	m_wantToShot = false;
}