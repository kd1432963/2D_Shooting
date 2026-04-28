#pragma once

class CircleHitBox;
class RectHitBox;

namespace Collision
{
    bool CircleCircle(const CircleHitBox& a, const CircleHitBox& b);
    bool CircleRect(const CircleHitBox& c, const RectHitBox& r);
    bool RectRect(const RectHitBox& a, const RectHitBox& b);
}
