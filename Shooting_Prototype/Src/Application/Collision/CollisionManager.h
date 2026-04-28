#pragma once

class Player;
class EnemyManager;
class BulletManager;
class EffectManager;

class CollisionManager
{
public:
    static void CheckAll(
        Player& player,
        EnemyManager& enemyMgr,
        BulletManager& bulletMgr,
        EffectManager& effectMgr,
        int& score
    );
};
