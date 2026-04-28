#include "RectHitBox.h"
#include "CircleHitBox.h"
#include "Application/Collision/Collision.h"

CircleHitBox::CircleHitBox(float r)
    : HitBoxBase(Type::Circle)
{
    radius = r;
}

bool CircleHitBox::IsHit(const HitBoxBase& other) const noexcept
{
    switch (other.type)
    {
    case Type::Circle:
        return Collision::CircleCircle(
            *this,
            static_cast<const CircleHitBox&>(other)
        );

    case Type::Rect:
        return Collision::CircleRect(
            *this,
            static_cast<const RectHitBox&>(other)
        );
    }

    return false;
}

void CircleHitBox::Draw() const noexcept
{
    SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
    SHADER.m_spriteShader.DrawCircle(pos.x, pos.y, radius,&Math::Color(0,0,0,1),false);
    SHADER.m_spriteShader.End();
    SHADER.m_spriteShader.Begin();
}
