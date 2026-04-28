#include "RectHitBox.h"
#include "CircleHitBox.h"
#include "Application/Collision/Collision.h"

RectHitBox::RectHitBox(float w, float h)
    : HitBoxBase(Type::Rect)
{
    halfW = w;
    halfH = h;
}

bool RectHitBox::IsHit(const HitBoxBase& other) const noexcept
{
    switch (other.type)
    {
    case Type::Circle:
        return Collision::CircleRect(
            static_cast<const CircleHitBox&>(other),
            *this
        );

    case Type::Rect:
        return Collision::RectRect(
            *this,
            static_cast<const RectHitBox&>(other)
        );
    }

    return false;
}

void RectHitBox::Draw() const noexcept
{
    SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
    // 四隅の座標を計算
    float l = Left();
    float r = Right();
    float t = Top();
    float b = Bottom();

    // 上辺
    SHADER.m_spriteShader.DrawLine(l, t, r, t);
    // 下辺                                 
    SHADER.m_spriteShader.DrawLine(l, b, r, b);
    // 左辺                                  
    SHADER.m_spriteShader.DrawLine(l, t, l, b);
    // 右辺                                  
    SHADER.m_spriteShader.DrawLine(r, t, r, b);

    SHADER.m_spriteShader.End();
    SHADER.m_spriteShader.Begin();
}
