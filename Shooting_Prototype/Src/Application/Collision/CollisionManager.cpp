#include "CollisionManager.h"
#include "Application/Chara/Player.h"
#include "Application/Enemy/EnemyManager.h"
#include "Application/Bullet/BulletManager.h"
#include "Application/Effect/EffectManager.h"
#include "Application/Collision/Collision.h"
#include"Application/Item/ItemDropManager.h"


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
            if (b->GetHitBox()->IsHit(*e->GetHitBox()))
            {
                e->TakeDamage(b->GetAtk());
                b->SetDead();
                effectMgr.SpawnHitEffect(b->GetPos());
                score += 10;
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
            player.TakeDamage(b->GetAtk());
            b->SetDead();
        }
    }

    // --- プレイヤー vs アイテムー ---
    for (auto& item : items)
    {
        if (item->GetHitBox()->IsHit(*player.GetHitBox()))
        {
            //player.GetItem(item->GetItemType());
            item->SetDead();
        }
    }

}
