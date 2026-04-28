#pragma once

#include"HitBoxBase.h"

class CircleHitBox : public HitBoxBase
{
public:
    float radius;

    CircleHitBox(float r);

    bool IsHit(const HitBoxBase& other) const noexcept override;

    void Draw() const noexcept override;
};
