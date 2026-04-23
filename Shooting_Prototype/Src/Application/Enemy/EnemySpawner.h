#pragma once
#include "EnemyManager.h"

// 敵の種類をここで include（Spawner が唯一知っていればOK）
#include "Enemy1/Enemy1.h"

class EnemySpawner
{
public:

    void SpawnWave1(EnemyManager& manager);
    void SpawnWave2(EnemyManager& manager);

    // 必要ならスポーンポイントやランダム生成もここに追加
};
