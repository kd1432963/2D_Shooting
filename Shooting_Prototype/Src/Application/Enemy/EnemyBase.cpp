#include"EnemyBase.h"

#include"Application/Bullet/BulletManager.h"
#include"Application/Bullet/BulletConfig.h"
#include"Application/Bullet/StraightBullet/StraightBullet.h"

void EnemyBase::Shot(BulletManager& bulletManager)
{
    BulletConfig config;
    config.pos = pos;
    config.atk = 1;

    auto bullet = std::make_unique<StraightBullet>(config);

    bulletManager.Add(std::move(bullet));
}