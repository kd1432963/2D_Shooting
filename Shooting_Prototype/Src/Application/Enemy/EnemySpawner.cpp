#include "EnemySpawner.h"

#include "Enemy1/Enemy1.h"
#include "Enemy2/Eneny2.h"

EnemySpawner::EnemySpawner()
{
	LoadCSV("_Data/EnemyData/EnemySpawnData.csv");
}

//======================================
// Wave開始
//======================================
void EnemySpawner::StartWave(int wave)
{
	m_currentWave = wave;
	m_timer = 0;

	// そのwaveの開始位置までindexを進める
	m_index = 0;

	while (m_index < m_events.size())
	{
		if (m_events[m_index].wave >= m_currentWave)
			break;

		m_index++;
	}
}

//======================================
// 毎フレーム
//======================================
void EnemySpawner::Update(EnemyManager& manager, Player* player)
{
	m_timer++;

	while (m_index < m_events.size())
	{
		const auto& e = m_events[m_index];

		if (e.wave != m_currentWave) break;

		if (e.time > m_timer) break;

		// 出現
		switch (e.type)
		{
		case 0:
			manager.AddEnemy<Enemy1>(Math::Vector2{ e.x, e.y });
			break;

			// 将来ここにEnemy2とか追加
		case 1:
			manager.AddEnemy<Enemy2>(Math::Vector2{ e.x,e.y }, player);
			break;
		}

		m_index++;
	}
}

//+++++++++++++++++++++++++++++++++++++++++
// ランダム生成
//+++++++++++++++++++++++++++++++++++++++++
void EnemySpawner::RandomSpawn(EnemyManager& manager)
{
	manager.AddEnemy<Enemy1>(
		Math::Vector2{
			RandomRangeF(100.0f, 600.0f),
			RandomRangeF(-200.0f, 200.0f)
		}
	);
}

void EnemySpawner::LoadCSV(const std::string& path)
{
	std::ifstream file(path);
	std::string line;

	std::getline(file, line);

	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string item;

		SpawnEvent e;

		std::getline(ss, item, ','); e.wave = std::stoi(item);
		std::getline(ss, item, ','); e.time = std::stoi(item);
		std::getline(ss, item, ','); e.type = std::stoi(item);
		std::getline(ss, item, ','); e.x = std::stof(item);
		std::getline(ss, item, ','); e.y = std::stof(item);

		m_events.push_back(e);
	}
}