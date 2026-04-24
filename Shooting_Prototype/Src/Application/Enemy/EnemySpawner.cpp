#include "EnemySpawner.h"

void EnemySpawner::SpawnWave1(EnemyManager& manager)
{
    manager.AddEnemy<Enemy1>();
    manager.AddEnemy<Enemy1>();
    RandomSpawn(manager);
}

void EnemySpawner::SpawnWave2(EnemyManager& manager)
{
    manager.AddEnemy<Enemy1>();
    manager.AddEnemy<Enemy1>(); 
    manager.AddEnemy<Enemy1>();
    manager.AddEnemy<Enemy1>();
}

void EnemySpawner::RandomSpawn(EnemyManager& manager)
{
    manager.AddEnemy<Enemy1>(Math::Vector2{ RandomRangeF(100.0f, 600.0f),RandomRangeF(-300.0f, 300.0f) });
}
