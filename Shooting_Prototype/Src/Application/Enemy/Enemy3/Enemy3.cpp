#include "Enemy3.h"
#include "Enemy3Config.h"

#include "Application/GameObject/RectHitBox.h"
#include "Application/Chara/Player.h"

using namespace Enemy3Const;

//+++++++++++++++++++++++++++++++++++++++++
// 初期化
//+++++++++++++++++++++++++++++++++++++++++
Enemy3::Enemy3(const Math::Vector2& p, Player* player)
{
    mp_player = player;

    hitbox = std::make_unique<RectHitBox>(15, 15);
    if (hitbox)
    {
        hitbox->pos = p;
    }

    tex = ASSET.GetTexture("Enemy3");
    rect = ASSET.GetRectangle("Enemy3");

    pos = { 640,p.y };
    scale = { kScaleX, kScaleY };
    rotate = 0.0f;

    velocity = { 0.0f, 0.0f };

    status.hp = kHp;
    status.maxHp = kHp;
    status.atk = kAtk;

    UpdateMatrix();
}

//+++++++++++++++++++++++++++++++++++++++++
// 更新
//+++++++++++++++++++++++++++++++++++++++++
void Enemy3::Update()
{
    UpdateAnim();
    UpdatePos();

    // Y座標の画面制御
    pos.y = Clamp(pos.y, -241.5f + 15.0f, 241.5f - 15.0f);
    hitbox->pos = pos;

    // X座標の画面制御
    if (pos.x < -640 - 15)
    {
        SystemKill();
    }

    UpdateMatrix();
}

//+++++++++++++++++++++++++++++++++++++++++
// 行動
//+++++++++++++++++++++++++++++++++++++++++
void Enemy3::Action()
{
    if (!isCharging)
    {
        waitTimer++;

        move.x = 0.0f;
        move.y = sinf(waitTimer * 0.1f) * 0.5f;

        if (waitTimer > 60 && mp_player)
        {
            Math::Vector2 dir = mp_player->GetPos() - pos;
            dir.Normalize();

            velocity = dir * kChargeSpeed;

            isCharging = true;
        }
    }
    else
    {
        move = velocity;
    }
}

//+++++++++++++++++++++++++++++++++++++++++
// 描画
//+++++++++++++++++++++++++++++++++++++++++
void Enemy3::Draw2D()
{
    CalcDrawRect();
    DrawChara();
}
