#include "EnemySpawner.h"

#include "Enemy1/Enemy1.h"

//+++++++++++++++++++++++++++++++++++++++++
// Wave1
//+++++++++++++++++++++++++++++++++++++++++
void EnemySpawner::SpawnWave1(EnemyManager& manager)
{
	RandomSpawn(manager);
	RandomSpawn(manager);
	RandomSpawn(manager);
}

//+++++++++++++++++++++++++++++++++++++++++
// Wave2
//+++++++++++++++++++++++++++++++++++++++++
void EnemySpawner::SpawnWave2(EnemyManager& manager)
{
	manager.AddEnemy<Enemy1>();
	manager.AddEnemy<Enemy1>();
	manager.AddEnemy<Enemy1>();
	manager.AddEnemy<Enemy1>();
}

//+++++++++++++++++++++++++++++++++++++++++
// ƒ‰ƒ“ƒ_ƒ€¶¬
//+++++++++++++++++++++++++++++++++++++++++
void EnemySpawner::RandomSpawn(EnemyManager& manager)
{
	manager.AddEnemy<Enemy1>(
		Math::Vector2{
			RandomRangeF(100.0f, 600.0f),
			RandomRangeF(-300.0f, 300.0f)
		}
	);
}