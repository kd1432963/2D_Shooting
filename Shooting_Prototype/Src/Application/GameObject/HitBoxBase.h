#pragma once

class HitBoxBase
{
public:

    enum class Type
    {
        Circle,
        Rect,
    };

    Type type;
    Math::Vector2 pos;

    HitBoxBase(Type t) : type(t) {}
    virtual ~HitBoxBase() = default;

    virtual bool IsHit(const HitBoxBase& other) const noexcept = 0;

    // デバッグ描画用
    virtual void Draw() const noexcept = 0;
};