#pragma once

#include "EnemyManager.h"

class EnemySpawner
{
public:

	void SpawnWave1(EnemyManager& manager);
	void SpawnWave2(EnemyManager& manager);

	void RandomSpawn(EnemyManager& manager);
};