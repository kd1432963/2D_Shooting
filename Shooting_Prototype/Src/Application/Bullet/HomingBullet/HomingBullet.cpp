#include "HomingBullet.h"

#include"Application/Bullet/BulletConfig.h"

#include"Application/Chara/CharaBase.h"

#include"Application/Enemy/EnemyManager.h"

HomingBullet::HomingBullet(const BulletConfig& cfg)
{
	// “–‚½‚è”»’è
	hitbox.pos = cfg.pos;
	hitbox.radius = 8.0f;
	radius = 8.0f;

	// ƒeƒNƒXƒ`ƒƒŽæ“¾
	tex = ASSET.GetTexture(cfg.texTag);
	m_rect = ASSET.GetRectangle(cfg.texTag);

	// î•ñ•Û‘¶
	pos = cfg.pos;
	move = cfg.move;
	scale = { 1.0f, 1.0f };
	rotate = 0.0f;
	owner = cfg.owner;

	atk = cfg.atk;

	m_dir = move;
	m_dir.Normalize();
}

void HomingBullet::Update()
{
	if (!m_target || m_target->IsDead())
	{
		m_target = FindTarget();
	}

	if (m_target)
	{
		Math::Vector2 toTarget = m_target->GetPos() - pos;
		toTarget.Normalize();

		float homingPower = 0.1f;

		m_dir = m_dir * (1.0f - homingPower) + toTarget * homingPower;
		m_dir.Normalize();
	}

	move = m_dir * speed;

	UpdatePos();

	if (pos.x >= 640 + radius || pos.x <= -640 - radius)
	{
		isDead = true;
	}

	UpdateMatrix();
}

void HomingBullet::Draw2D()
{
	// ’e•`‰æ
	SHADER.m_spriteShader.SetMatrix(mat);
	SHADER.m_spriteShader.DrawTex(tex, m_rect);
}

CharaBase* HomingBullet::FindTarget()
{
	if (!m_enemyManager) return nullptr;

	auto& enemies = m_enemyManager->GetEnemies();

	CharaBase* nearest = nullptr;
	float minDist = FLT_MAX;

	for (auto& e : enemies)
	{
		if (e->IsDead()) continue;

		float d = (e->GetPos() - pos).Length();

		if (d < minDist)
		{
			minDist = d;
			nearest = e.get();
		}
	}

	return nearest;
}