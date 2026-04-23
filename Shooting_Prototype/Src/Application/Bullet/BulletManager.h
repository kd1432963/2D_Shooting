#pragma once

class BulletBase;

class BulletManager
{
public:

    //+++++++++++++++++++++++++++++++++++++++++
    // 追加関数
    //+++++++++++++++++++++++++++++++++++++++++
    void Add(std::unique_ptr<BulletBase> bullet);
    
    //+++++++++++++++++++++++++++++++++++++++++
    // 基本ライフサイクル
    //+++++++++++++++++++++++++++++++++++++++++
    void Update();
    void Draw2D();

    //+++++++++++++++++++++++++++++++++++++++++
    // 弾リストの参照を返す
    //+++++++++++++++++++++++++++++++++++++++++
    const std::vector<std::unique_ptr<BulletBase>>& GetBullets() const;

private:

    //+++++++++++++++++++++++++++++++++++++++++
    // 弾リスト
    //+++++++++++++++++++++++++++++++++++++++++
    std::vector<std::unique_ptr<BulletBase>> m_bullets;
};