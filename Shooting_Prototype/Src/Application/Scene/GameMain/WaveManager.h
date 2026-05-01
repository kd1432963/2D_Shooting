#pragma once

class EnemyManager;
class EnemySpawner;

class WaveManager
{
public:

	void Update(EnemyManager& enemy,EnemySpawner& spawner);

private:

	int m_wave = 0;
	int m_waveTimer = 0;

};