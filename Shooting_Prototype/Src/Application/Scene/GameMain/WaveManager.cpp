#include "WaveManager.h"

#include"Application/Enemy/EnemyManager.h"
#include"Application/Enemy/EnemySpawner.h"

void WaveManager::Update(EnemyManager& enemy,EnemySpawner& spawner)
{
	++m_waveTimer;

	bool isAllDead = enemy.GetEnemies().empty();

	// 敵全滅もしくは時間経過で次ウェーブ
	if (isAllDead || m_waveTimer >= 600)
	{
		++m_wave;
		spawner.StartWave(m_wave);
		m_waveTimer = 0;
	}
}
