#pragma once

#include"BulletOwner.h"

struct BulletConfig
{
    std::string texTag;     // ‚Ç‚Ì‰æ‘œ‚ğg‚¤‚©
    Math::Vector2 pos;      // ‰ŠúˆÊ’u
    Math::Vector2 move;     // ‰ŠúˆÚ“®—Ê
    int atk = 1;
    BulletOwner owner = BulletOwner::Player;
};