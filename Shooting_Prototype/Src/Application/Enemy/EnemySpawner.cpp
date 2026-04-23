#include "EnemySpawner.h"

void EnemySpawner::SpawnWave1(EnemyManager& manager)
{
    manager.AddEnemy<Enemy1>();
    manager.AddEnemy<Enemy1>();
}

void EnemySpawner::SpawnWave2(EnemyManager& manager)
{
    manager.AddEnemy<Enemy1>();
    manager.AddEnemy<Enemy1>(); 
    manager.AddEnemy<Enemy1>();
    manager.AddEnemy<Enemy1>();
}
