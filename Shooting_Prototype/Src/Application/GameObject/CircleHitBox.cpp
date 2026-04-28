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