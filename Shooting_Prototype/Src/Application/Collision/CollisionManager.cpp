#include "CollisionManager.h"
#include "Application/Chara/Player.h"
#include "Application/Enemy/EnemyManager.h"
#include "Application/Bullet/BulletManager.h"
#include "Application/Effect/EffectManager.h"
#include "Application/Collision/Collision.h"
#include"Application/Item/ItemDropManager.h"
#include"Application/Enemy/Boss/Boss.h"


void CollisionManager::CheckAll(
	Player& player,
	EnemyManager& enemyMgr,
	BulletManager& bulletMgr,
	EffectManager& effectMgr,
	ItemDropManager& itemDropMgr,
	int& score
)
{
	auto& bullets = bulletMgr.GetBullets();
	auto& enemies = enemyMgr.GetEnemies();
	auto& items = itemDropMgr.GetItems();

	// --- 弾 vs 敵 ---
	for (auto& b : bullets)
	{
		if (b->GetOwner() != BulletOwner::Player)
			continue;

		for (auto& e : enemies)
		{
			// ★ ボスなら複数 HitBox をチェック
			if (auto boss = dynamic_cast<Boss*>(e.get()))
			{
				if (!boss->IsDeathAnim())
				{
					for (auto& hb : boss->GetHitBoxes())
					{
						if (b->GetHitBox()->IsHit(*hb))
						{
							boss->TakeDamage(b->GetAtk());
							b->SetDead();
							effectMgr.SpawnHitEffect(b->GetPos());

							effectMgr.SpawnScoreEffect(boss->GetPos(), 100);
							score += 100;

							if (RandomChance(0.05f))
							{
								itemDropMgr.DropItemRandom(boss->GetPos());
							}

							if (RandomChance(0.2f))
							SOUND.PlaySE("HitSE");

							goto NEXT_ENEMY;
						}
					}
				}
			}
			else
			{
				// ★ 通常敵（今まで通り）
				if (b->GetHitBox()->IsHit(*e->GetHitBox()))
				{
					e->TakeDamage(b->GetAtk());
					b->SetDead();
					effectMgr.SpawnHitEffect(b->GetPos());

					EnemyType type = e->GetType();
					int addScore = 0;

					switch (type)
					{
					case EnemyType::Enemy1: addScore = 10; break;
					case EnemyType::Enemy2: addScore = 30; break;
					case EnemyType::Enemy3: addScore = 30; break;
					case EnemyType::Enemy4: addScore = 20; break;
					}

					effectMgr.SpawnScoreEffect(e->GetPos(), addScore);
					score += addScore;

					if(RandomChance(0.3f))
					SOUND.PlaySE("HitSE");
				}
			}

		NEXT_ENEMY:;
		}
	}

	if (!player.IsInvincible())
	{
		// --- 敵 vs プレイヤー ---
		for (auto& e : enemies)
		{
			if (auto boss = dynamic_cast<Boss*>(e.get()))
			{
				for (auto& hb : boss->GetHitBoxes())
				{
					if (player.GetHitBox()->IsHit(*hb))
					{
						player.TakeDamage(e->GetAtk());
						break;
					}
				}
			}
			else
			{
				if (e->GetHitBox()->IsHit(*player.GetHitBox()))
				{
					player.TakeDamage(e->GetAtk());
					break;
				}
			}
		}
	}

	// --- 敵弾 vs プレイヤー ---
	for (auto& b : bullets)
	{
		if (b->GetOwner() != BulletOwner::Enemy)
			continue;

		if (b->GetHitBox()->IsHit(*player.GetHitBox()))
		{
			if (!player.IsInvincible())
			{
				player.TakeDamage(b->GetAtk());
			}
			b->SetDead();
			break;
		}
	}

	// --- プレイヤー vs アイテムー ---
	for (auto& item : items)
	{
		if (item->GetHitBox()->IsHit(*player.GetHitBox()))
		{
			player.GetItem(item->GetItemType());
			item->SetDead();
		}
	}

}
