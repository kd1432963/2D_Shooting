#include "Collision.h"
#include "Application/GameObject/CIrcleHitBox.h"
#include "Application/GameObject/RectHitBox.h"

bool Collision::CircleCircle(const CircleHitBox& a, const CircleHitBox& b)
{
    float dx = a.pos.x - b.pos.x;
    float dy = a.pos.y - b.pos.y;
    float distSq = dx * dx + dy * dy;
    float r = a.radius + b.radius;
    return distSq <= r * r;
}

bool Collision::CircleRect(const CircleHitBox& c, const RectHitBox& r)
{
    float nearestX = Clamp(c.pos.x, r.Left(), r.Right());
    float nearestY = Clamp(c.pos.y, r.Top(), r.Bottom());

    float dx = c.pos.x - nearestX;
    float dy = c.pos.y - nearestY;

    return (dx * dx + dy * dy) <= (c.radius * c.radius);
}

bool Collision::RectRect(const RectHitBox& a, const RectHitBox& b)
{
    return !(a.Right() < b.Left() ||
        a.Left()  > b.Right() ||
        a.Bottom() < b.Top() ||
        a.Top() > b.Bottom());
}