#pragma once

#include"EnemyBase.h"

class EnemyManager
{
public:

    //+++++++++++++++++++++++++++++++++++++++++
    // 敵追加関数
    //+++++++++++++++++++++++++++++++++++++++++
    template <class T, class... Args>
    T* AddEnemy(Args&&... args) 
    {
        // T が EnemyBase を継承しているかチェック
        static_assert(std::is_base_of_v<EnemyBase, T>, "T must inherit EnemyBase");

        // T を new する(引数は各コンストラクタに合わせて)
        auto enemy = std::make_unique<T>(std::forward<Args>(args)...);
        T* raw = enemy.get();

        // 初期化処理を通す
        enemy->Init();

        // vector に保存
        m_enemies.emplace_back(std::move(enemy));
        
        // 所有権は渡さず呼び出し元へ返す
        return raw;
    }

    //+++++++++++++++++++++++++++++++++++++++++
    // 基本ライフサイクル
    //+++++++++++++++++++++++++++++++++++++++++
    void Update();
    void Action();
    void Draw2D();
    void DeleteDead();

    //+++++++++++++++++++++++++++++++++++++++++
    // 敵リストの参照を返す
    //+++++++++++++++++++++++++++++++++++++++++
    const std::vector<std::unique_ptr<EnemyBase>>& GetEnemies() const { return m_enemies; }

private:
    //+++++++++++++++++++++++++++++++++++++++++
    // 敵リスト
    //+++++++++++++++++++++++++++++++++++++++++
    std::vector<std::unique_ptr<EnemyBase>> m_enemies;
};