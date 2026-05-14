#include "Player.h"

#include "PlayerConfig.h"
#include "Application/Bullet/BulletManager.h"
#include "Application/Bullet/BulletConfig.h"

#include"Application/GameObject/RectHitBox.h"

#include"Application/Item/ItemStockManager.h"

using namespace PlayerConst;

//+++++++++++++++++++++++++++++++++++++++++
// 初期化
//+++++++++++++++++++++++++++++++++++++++++
Player::Player()
{
	hitbox = std::make_unique<RectHitBox>(10, 5);
	if (hitbox)
	{
		hitbox->pos = { kPosX, kPosY };
	}

	m_itemManager = new ItemStockManager();

	tex = ASSET.GetTexture("Player");
	rect = ASSET.GetRectangle("Player");

	pos = { kPosX, kPosY };
	scale = { kScaleX, kScaleY };
	rotate = 90.0f;
	move = { 0.0f, 0.0f };

	status.atk = kAtk;
	status.hp = kHp;
	status.maxHp = kHp;

	UpdateMatrix();
}

Player::~Player()
{
	if (m_itemManager)
	{
		delete m_itemManager;
		m_itemManager = nullptr;
	}
}

//+++++++++++++++++++++++++++++++++++++++++
// 更新
//+++++++++++++++++++++++++++++++++++++++++
void Player::Update()
{
	UpdatePos();

	// アイテム使用リキャスト減少
	if (m_itemRecast > 0.0f)
	{
		m_itemRecast -= 1.0f / 60.0f;
		if (m_itemRecast <= 0.0f)
		{
			m_itemRecast = 0.0f;
		}
	}

	// ホーミング時間減少
	if (m_homingTime > 0.0f)
	{
		m_homingTime -= 1.0f / 60.0f;
		if (m_homingTime <= 0.0f)
		{
			m_shotMode = BulletType::Straight;
			m_homingTime = 0.0f;
		}
	}

	// 貫通時間減少
	if (m_piercingTime > 0.0f)
	{
		m_piercingTime -= 1.0f / 60.0f;
		if (m_piercingTime <= 0.0f)
		{
			m_shotMode = BulletType::Straight;
			m_piercingTime = 0.0f;
		}
	}

	// 無敵時間減少
	if (m_isInvincible)
	{
		m_invincibleTimer -= 1.0f / 60.0f;

		if (m_invincibleTimer <= 0.0f)
		{
			m_isInvincible = false;
			m_invincibleTimer = 0.0f;
		}

		m_blinkTimer += 1.0f / 60.0f;
	}

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

	//=============================
	// 右クリックで先頭アイテム使用
	//=============================
	if (MOUSE.IsTriggerRight())
	{
		if (m_itemRecast <= 0.0f && m_itemManager && m_itemManager->HasItem())
		{
			ItemType type = m_itemManager->Get(0);
			m_itemManager->UseItem();
			UseItemEffect(type);
			m_itemRecast = 5.0f;
		}
	}
	/*else if (KEY.IsTrigger(VK_SHIFT))
	{
		if (m_itemRecast <= 0.0f && m_itemManager && m_itemManager->HasItem())
		{
			ItemType type = m_itemManager->Get(0);
			m_itemManager->UseItem();
			UseItemEffect(type);
			m_itemRecast = 5.0f;
		}
	}*/
	ShotInput();
}

//+++++++++++++++++++++++++++++++++++++++++
// 入力：移動
//+++++++++++++++++++++++++++++++++++++++++
void Player::MoveInput()
{
	move = { 0.0f, 0.0f };

	if (KEY.IsPress('W')) move.y += 1.0f;
	if (KEY.IsPress('A')) move.x -= 1.0f;
	if (KEY.IsPress('S')) move.y -= 1.0f;
	if (KEY.IsPress('D')) move.x += 1.0f;

	//if (KEY.IsPress(VK_UP)) move.y += 1.0f;
	//if (KEY.IsPress(VK_LEFT)) move.x -= 1.0f;
	//if (KEY.IsPress(VK_DOWN)) move.y -= 1.0f;
	//if (KEY.IsPress(VK_RIGHT)) move.x += 1.0f;

	// 正規化
	move.Normalize();

	move *= kWalkPow;

	float fPosX = pos.x + move.x;
	float fPosY = pos.y + move.y;

	// 画面内制御
	if (fPosX + kRadius >= Screen::Right || fPosX - kRadius <= Screen::Left)
	{
		move.x = 0.0f;
	}

	if (fPosY + kRadius >= GameArea::Top || fPosY - kRadius <= GameArea::Bottom)
	{
		move.y = 0.0f;
	}

}

//+++++++++++++++++++++++++++++++++++++++++
// 入力：発射判定
//+++++++++++++++++++++++++++++++++++++++++
void Player::ShotInput()
{
	if (MOUSE.IsPressLeft() && m_shotRecast <= 0.0f)
	{
		wantToShot = true;
		m_shotRecast = kShotRecastTime;
	}
	/*else if (KEY.IsPress(VK_SPACE) && m_shotRecast <= 0.0f)
	{
		wantToShot = true;
		m_shotRecast = kShotRecastTime;
	}*/
}

//+++++++++++++++++++++++++++++++++++++++++
// アイテム使用効果
//+++++++++++++++++++++++++++++++++++++++++
void Player::UseItemEffect(ItemType type)
{
	switch (type)
	{
	case ItemType::Homing:
		m_shotMode = BulletType::Homing;
		m_homingTime = kHomingRecast;
		break;

	case ItemType::Piercing:
		m_shotMode = BulletType::Piercing;
		m_piercingTime = kPiercingRecast;
	default:
		break;
	}
}

//+++++++++++++++++++++++++++++++++++++++++
// 描画
//+++++++++++++++++++++++++++++++++++++++++
void Player::Draw2D()
{
	if(!IsDead())
	{
		if (m_isInvincible)
		{
			if (sin(m_blinkTimer * 30.0f) > 0)
			{
				DrawChara();
			}
		}
		else
		{
			DrawChara();
		}
	}
}

//+++++++++++++++++++++++++++++++++++++++++
// 弾発射
//+++++++++++++++++++++++++++++++++++++++++
void Player::Shot(BulletManager& b)
{
	Math::Vector2 muzzuleOffset = { 8.0f,0.0f };

	BulletConfig cfg =
	{
		"Straight",
		pos + muzzuleOffset,
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

	case BulletType::Piercing:
		cfg.texTag = "Piercing";
		break;
	}

	b.Add(cfg, m_shotMode);

	SOUND.PlaySE("ShotSE");

	wantToShot = false;
}

void Player::TakeDamage(int damage)
{
	if (m_isInvincible) return;

	status.hp -= damage;

	if (status.hp <= 0)status.hp = 0;

	m_isInvincible = true;
	m_invincibleTimer = kInvincibleDuration;

	m_blinkTimer = 0.0f;
}

void Player::GetItem(ItemType type)
{
	if (type == ItemType::Heal)
	{
		if (status.hp < 5)++status.hp;
	}
	else
	{
		m_itemManager->AddItem(type);
	}
}

bool Player::CanUseItem() const
{
	return m_itemManager->HasItem() && m_itemRecast <= 0.0f;
}
