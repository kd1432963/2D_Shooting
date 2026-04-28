#pragma once

#include"HitBoxBase.h"

class RectHitBox : public HitBoxBase
{
public:
    float halfW;
    float halfH;

    RectHitBox(float w,float h);

    float Left()   const { return pos.x - halfW; }
    float Right()  const { return pos.x + halfW; }
    float Top()    const { return pos.y - halfH; }
    float Bottom() const { return pos.y + halfH; }

    bool IsHit(const HitBoxBase& other) const noexcept override;

    void Draw() const noexcept override;
};
