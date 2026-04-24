#include "EnemyManager.h"

#include"Application/Bullet/BulletManager.h"

//+++++++++++++++++++++++++++++++++++++++++
// 更新処理
//+++++++++++++++++++++++++++++++++++++++++
void EnemyManager::Update() 
{
    for (auto& e : m_enemies) 
    {
        e->Update();
    }
}

//+++++++++++++++++++++++++++++++++++++++++
// 行動決定
//+++++++++++++++++++++++++++++++++++++++++
void EnemyManager::Action()
{
    for (auto& e : m_enemies)
    {
        e->Action();
    }
}

//+++++++++++++++++++++++++++++++++++++++++
// 描画処理
//+++++++++++++++++++++++++++++++++++++++++
void EnemyManager::Draw2D() 
{
    for (auto& e : m_enemies) 
    {
        e->Draw2D();
    }
}

void EnemyManager::Shot(BulletManager& b)
{
    for (auto& e : m_enemies)
    {
        if (e->WantToShot())
        {
            e->Shot(b);
        }
    }
}


//+++++++++++++++++++++++++++++++++++++++++
// 死んでる要素を消す
//+++++++++++++++++++++++++++++++++++++++++
void EnemyManager::DeleteDead() 
{
    m_enemies.erase
    (
        //=== 条件の合う要素を後ろに押し出す ==========
        //=== 戻り値は条件に合わなかった要素の終端 ====
        std::remove_if
        (
            m_enemies.begin(),
            m_enemies.end(),
            [](const auto& e) { return e->IsDead(); }
        ),
        m_enemies.end()
    );
}