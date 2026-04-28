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
