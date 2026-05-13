#include "Boss.h"


#include"Application/GameObject/RectHitBox.h"
#include"Application/Bullet/BulletConfig.h"
#include"Application/Bullet/BulletManager.h"
#include"Application/Effect/EffectManager.h"
#include"Application/Effect/ExplosionEffect/ExplosionEffect.h"
#include"Application/Chara/Player.h"

#include"BossConfig.h"

using namespace BossConst;

Boss::Boss(const Math::Vector2& p, Player* player)
	:EnemyBase(EnemyType::Boss)
{
	std::unique_ptr<HitBoxBase>box = std::make_unique<RectHitBox>(100, 36);
	if (box)
	{
		box->offset.y = -62;
		m_hitboxes.push_back(std::move(box));

		box = std::make_unique<RectHitBox>(75, 51);
		box->offset = { 25,24 };
		m_hitboxes.push_back(std::move(box));

		box = std::make_unique<RectHitBox>(50, 12);
		box->offset = { 25,89 };
		m_hitboxes.push_back(std::move(box));
	}

	for (auto& h : m_hitboxes)
	{
		h->pos = p + h->offset;
	}

	mp_player = player;

	tex = ASSET.GetTexture("Boss");
	rect = ASSET.GetRectangle("Boss");

	pos = p;
	basePos = p;
	scale = { kScaleX, kScaleY };
	rotate = 0.0f;

	status.hp = kHp;
	status.maxHp = kHp;
	status.atk = kAtk;

	m_state = State::Enter;
	move = { 0.0f,0.0f };

	UpdateMatrix();
}

void Boss::Update()
{
	if (pos.x <= Screen::Right + -200 && m_state == State::Enter)
	{
		m_state = State::Battle;
		move.x = 0;
	}

	if (status.hp <= 0)
	{
		m_state = State::Dead;
	}

	UpdateAnim();
	UpdatePos();

	// Y座標の画面制御
	pos.y = Clamp(pos.y, -241.5f + 15.0f, 241.5f - 15.0f);
	for (auto& h : m_hitboxes)
	{
		h->pos = pos + h->offset;
	}

	UpdateMatrix();
}

void Boss::Action()
{
	switch (m_state)
	{
	case State::Enter:

		// 右から入場
		move.x = -3.0f;

		break;

	case State::Battle:

		BossAI();

		break;

	case State::Dead:

		m_deathAnimStart = true;
		++m_deathAnimTime;

		// 揺れる演出
		move = { RandomRangeF(-3.0f,3.0f),RandomRangeF(-3.0f,3.0f) };

		// 徐々に落ちていくのは確定
		move.y += -1;

		// 100Fで透明化
		m_alpha = 1.0f - (m_deathAnimTime / 300.0f);

		m_alpha = Clamp(m_alpha, 0.0f, 1.0f);

		if (effect)
		{
			// 爆発
			if (m_deathAnimTime % 6 == 0)
			{
				Math::Vector2 effectPos =
				{
					pos.x + RandomRangeF(-120,120),
					pos.y + RandomRangeF(-80,80)
				};

				auto e = std::make_unique<ExplosionEffect>(effectPos);
				effect->AddEffect(std::move(e));
			}
		}

		if (m_alpha <= 0.0f)
		{
			m_endDeathAnim = true;
		}

		break;
	}
}

void Boss::Draw2D()
{
	CalcDrawRect();
	SHADER.m_spriteShader.SetMatrix(mat);
	SHADER.m_spriteShader.DrawTex(tex, 0, 0, &rect, &Math::Color(1, 1, 1, m_alpha));

#if _DEBUG

	DebugDraw();

#endif

}

void Boss::DebugDraw()
{
	for (auto& h : m_hitboxes)
	{
		h->Draw();
	}
}

void Boss::BossAI()
{
	m_timer++;

	move.y = sinf(m_timer * 0.03f) * 2.0f;

	if (status.hp < 1000)
	{
		m_shotType = BossShotType::AimFiveWay;
	}

	if (status.hp < 500)
	{
		Math::Vector2 target = { 0,0 };

		Math::Vector2 dir =
			target - pos;

		float dist = dir.Length();

		float speed = std::max(dist * 0.0095f, 1.5f);

		dir.Normalize();

		move = dir * speed;

		if (dist < 5.0f)
		{
			pos = target;
			move = { 0,0 };

			m_shotType = BossShotType::Circle;
		}
	}

	int shotRecast = 0;

	switch (m_shotType)
	{
	case BossShotType::Circle:
		move.y = 0;
		shotRecast = 3;
		break;

	case BossShotType::FiveWay:
		shotRecast = 25;
		break;

	case BossShotType::AimFiveWay:
		shotRecast = 10;
		break;
	}

	if (m_timer % shotRecast == 0)
	{
		wantToShot = true;
	}
}

void Boss::Shot(BulletManager& b)
{
	if (!wantToShot)
	{
		return;
	}

	switch (m_shotType)
	{
	case BossShotType::Circle:

		ShotCircle(b);

		break;

	case BossShotType::FiveWay:

		ShotFiveWay(b);

		break;

	case BossShotType::AimFiveWay:

		ShotAimFiveWay(b, mp_player->GetPos());

		break;
	}

	wantToShot = false;
}

bool Boss::IsDead() const
{
	return m_endDeathAnim;
}


void Boss::ShotCircle(BulletManager& b)
{
	constexpr float PI = 3.1415926535f;
	constexpr float TwoPI = PI * 2.0f;

	constexpr int BulletNum = 4;

	for (int i = 0; i < BulletNum; i++)
	{
		float angle =
			TwoPI * i / BulletNum
			+ m_rotShotAngle;

		Math::Vector2 dir =
		{
			cosf(angle),
			sinf(angle)
		};

		dir.Normalize();

		BulletConfig cfg;

		cfg.texTag = "BossBullet1";
		cfg.pos = pos;
		cfg.move = dir * 3.0f;
		cfg.atk = status.atk;
		cfg.owner = BulletOwner::Enemy;

		b.Add(cfg, BulletType::Normal);
	}

	m_rotShotAngle += 0.035f;
}

void Boss::ShotFiveWay(BulletManager& b)
{
	constexpr float PI = 3.1415926535f;

	for (int i = -2; i <= 2; i++)
	{
		float angle = PI + i * 0.17f;

		Math::Vector2 dir =
		{
			cosf(angle),
			sinf(angle)
		};

		dir.Normalize();

		BulletConfig cfg;

		cfg.texTag = "BossBullet1";
		cfg.pos = pos;
		cfg.move = dir * 4.0f;
		cfg.atk = status.atk;
		cfg.owner = BulletOwner::Enemy;

		b.Add(cfg, BulletType::Normal);
	}
}

void Boss::ShotAimFiveWay
(
	BulletManager& b,
	const Math::Vector2& playerPos
)
{
	Math::Vector2 toPlayer =
		playerPos - pos;

	float baseAngle =
		atan2f(toPlayer.y, toPlayer.x);

	for (int i = -1; i <= 1; i++)
	{


		float angle = baseAngle + i * 0.05f;

		Math::Vector2 dir =
		{
			cosf(angle),
			sinf(angle)
		};

		dir.Normalize();

		BulletConfig cfg;

		cfg.texTag = "BossBullet1";
		cfg.pos = pos;
		cfg.move = dir * 5.0f;
		cfg.atk = status.atk;
		cfg.owner = BulletOwner::Enemy;

		b.Add(cfg, BulletType::Normal);
	}
}

