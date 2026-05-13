#include "WaveManager.h"

#include"Application/Enemy/EnemyManager.h"
#include"Application/Enemy/EnemySpawner.h"
#include"Application/Effect/EffectManager.h"
#include"Application/Chara/Player.h"

bool WaveManager::Update(EnemyManager& enemy, EnemySpawner& spawner,EffectManager*effect,Player*player)
{
	if (m_bossStarted)
	{
		++m_wave;
		spawner.SpawnBoss(enemy,effect,player);
		m_bossStarted = false;
	}

	++m_waveTimer;

	bool isAllDead = enemy.GetEnemies().empty();
	bool midBossAlive = enemy.IsMidBossAlive();

	// BOSS 戦
	if (m_wave == kMaxWave + 1)
	{
		if (isAllDead)
		{
			m_waveAllClear = true;

			return false;
		}

		return false;
	}


	// 中ボス戦中は進行停止
	if (midBossAlive)
	{
		return false;
	}

	// 敵全滅もしくは時間経過で次ウェーブ
	if (isAllDead || m_waveTimer >= 600)
	{
		if (m_wave != kMaxWave)
		{
			++m_wave;
			spawner.StartWave(m_wave);
			m_waveTimer = 0;

			// 開始時,中ボス戦後は全滅ボーナスなし
			if (m_wave == 1 || m_wave == 6 || m_wave == 11)isAllDead = false;

			return isAllDead;
		}
		else
		{
			// ボス移行処理
			if (!m_bossWarning && !m_bossStarted && isAllDead)
			{
				m_bossWarning = true;
			}
		}
	}

	return false;
}
