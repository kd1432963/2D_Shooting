#include "BulletBase.h"

void BulletBase::UpdateAnim()
{
    animTimer++;

    if (animTimer >= animStep)
    {
        animTimer = 0;
        animFrame++;

        if (animFrame >= animMaxFrame)
        {
            animFrame = 0;
        }
    }
}
