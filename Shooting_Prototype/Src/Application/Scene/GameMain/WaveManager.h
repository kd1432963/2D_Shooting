#pragma once

class EnemyManager;
class EffectManager;
class EnemySpawner;
class Player;

class WaveManager
{
public:

	bool Update(EnemyManager& enemy, EnemySpawner& spawner, EffectManager* effect,Player*player);

	int GetWave()const { return m_wave; }

	bool IsBossWarning() const { return m_bossWarning; }
	bool IsBossStarted() const { return m_bossStarted; }

	bool IsWaveAllClear() const{ return m_waveAllClear; }

	void SetBossStarted() { m_bossStarted = true; }

private:

	static const int kMaxWave = 1;

	int m_wave = 0;
	int m_waveTimer = 0;

	bool m_bossWarning = false;
	bool m_bossStarted = false;

	bool m_waveAllClear = false;

};