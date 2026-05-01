#pragma once

#include "EnemyManager.h"

class Player;

class EnemySpawner
{
public:

	EnemySpawner();

	// Wave開始
	void StartWave(int wave);

	// 毎フレーム呼ぶ
	void Update(EnemyManager& manager, Player* player);

	

private:

	struct SpawnEvent
	{
		int wave;
		int time;
		int type;
		float x;
		float y;
	};

	std::vector<SpawnEvent>m_events;

	int m_currentWave = 0;
	int m_timer = 0;
	size_t m_index = 0;

	void RandomSpawn(EnemyManager& manager);

private:

	void LoadCSV(const std::string&path);
};