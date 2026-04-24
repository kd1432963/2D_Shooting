#include "HomingBullet.h"

#include "Application/Bullet/BulletConfig.h"
#include "Application/Chara/CharaBase.h"
#include"Application/Chara/Player.h"
#include "Application/Enemy/EnemyManager.h"

HomingBullet::HomingBullet(const BulletConfig& cfg)
{
	hitbox.pos = cfg.pos;
	hitbox.radius = 8.0f;
	radius = 8.0f;

	tex = ASSET.GetTexture(cfg.texTag);
	m_rect = ASSET.GetRectangle(cfg.texTag);

	pos = cfg.pos;
	move = cfg.move;
	scale = { 1.0f, 1.0f };
	rotate = 0.0f;
	owner = cfg.owner;

	atk = cfg.atk;

	m_dir = move;
	if (m_dir.LengthSquared() > 0.0f)
	{
		m_dir.Normalize();
	}
}

//+++++++++++++++++++++++++++++++++++++++++
// 更新
//+++++++++++++++++++++++++++++++++++++++++
void HomingBullet::Update()
{
	if (!m_target || m_target->IsDead())
	{
		m_target = FindTarget();
	}

	if (m_target)
	{
		Math::Vector2 toTarget = m_target->GetPos() - pos;

		if (toTarget.LengthSquared() > 0.0f)
		{
			toTarget.Normalize();

			const float homingPower = 0.1f;

			m_dir = m_dir * (1.0f - homingPower) + toTarget * homingPower;
			m_dir.Normalize();
		}
	}

	move = m_dir * m_speed;

	UpdatePos();

	// 画面外で消す（上下も入れた）
	if (pos.x >= 640 + radius || pos.x <= -640 - radius ||
		pos.y >= 360 + radius || pos.y <= -360 - radius)
	{
		isDead = true;
	}

	UpdateMatrix();
}

//+++++++++++++++++++++++++++++++++++++++++
// 描画
//+++++++++++++++++++++++++++++++++++++++++
void HomingBullet::Draw2D()
{
	SHADER.m_spriteShader.SetMatrix(mat);
	SHADER.m_spriteShader.DrawTex(tex, m_rect);
}

//+++++++++++++++++++++++++++++++++++++++++
// ターゲット検索
//+++++++++++++++++++++++++++++++++++++++++
CharaBase* HomingBullet::FindTarget()
{
	if (owner == BulletOwner::Player)
	{
		if (!mp_enemyManager) return nullptr;

		const auto& enemies = mp_enemyManager->GetEnemies();

		CharaBase* nearest = nullptr;
		float minDist = FLT_MAX;

		for (const auto& e : enemies)
		{
			if (e->IsDead()) continue;

			float distSq = (e->GetPos() - pos).LengthSquared();

			if (distSq < minDist)
			{
				minDist = distSq;
				nearest = e.get();
			}
		}

		return nearest;
	}
	else
	{
		// 敵弾 → プレイヤー
		return mp_player;
	}
}