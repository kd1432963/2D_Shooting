#include "Enemy3.h"
#include "Enemy3Config.h"

#include "Application/GameObject/RectHitBox.h"
#include "Application/Chara/Player.h"

using namespace Enemy3Const;

//+++++++++++++++++++++++++++++++++++++++++
// 初期化
//+++++++++++++++++++++++++++++++++++++++++
Enemy3::Enemy3(const Math::Vector2& p, Player* player)
    :EnemyBase(EnemyType::Enemy3)
{
    mp_player = player;

    hitbox = std::make_unique<RectHitBox>(15, 15);
    if (hitbox)
    {
        hitbox->pos = p;
    }

    tex = ASSET.GetTexture("Enemy3");
    rect = ASSET.GetRectangle("Enemy3");

    pos = p;
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

    const float left = -640.0f + 15.0f;
    const float right = 640.0f - 15.0f;
    const float top = -241.5f + 15.0f;
    const float bottom = 241.5f - 15.0f;

    //========================
    // X反射
    //========================
    if (pos.x < left)
    {
        pos.x = left;
        velocity.x *= -0.5f;
    }
    else if (pos.x > right)
    {
        pos.x = right;
        velocity.x *= -0.5f;
    }

    //========================
    // Y反射
    //========================
    if (pos.y < top)
    {
        pos.y = top;
        velocity.y *= -0.5f;
    }
    else if (pos.y > bottom)
    {
        pos.y = bottom;
        velocity.y *= -0.5f;
    }

    hitbox->pos = pos;

    UpdateMatrix();
}

//+++++++++++++++++++++++++++++++++++++++++
// 行動
//+++++++++++++++++++++++++++++++++++++++++
void Enemy3::Action()
{
    //========================
   // 待機状態
   //========================
    if (!isCharging)
    {
        waitTimer++;

        move.x = 0.0f;
        move.y = sinf(waitTimer * 0.1f) * 0.5f;

        // 1秒後に突進開始
        if (waitTimer > 60 && mp_player)
        {
            Math::Vector2 dir = mp_player->GetPos() - pos;
            dir.Normalize();

            velocity = dir * kChargeSpeed;

            isCharging = true;

            chargeTimer = 0;
            waitTimer = 0;
        }
    }

    //========================
    // 突進状態
    //========================
    else
    {
        chargeTimer++;

        move = velocity;

        if (chargeTimer > 180)
        {
            isCharging = false;

            chargeTimer = 0;

            move = { 0.0f, 0.0f };
            velocity = { 0.0f, 0.0f };
        }
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
