#pragma once

class HitBox
{
public:

    //**********************************
    // 基本変数
    //**********************************
    Math::Vector2 pos = { 0.0f,0.0f };
    float radius = 0.0f;

public:

    //**********************************
    // 円形判定
    //**********************************
    bool IsHit(const HitBox& other) const noexcept
    {
        float dx = pos.x - other.pos.x;
        float dy = pos.y - other.pos.y;

        // 距離の二乗
        float distSq = dx * dx + dy * dy;

        // 半径の合計
        float r = radius + other.radius;

        // 衝突しているか（距離の二乗 <= 半径の合計の二乗）
        return distSq <= r * r;
    }
};