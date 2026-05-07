#include "CharaBase.h"

void CharaBase::DrawChara()
{
	SHADER.m_spriteShader.SetMatrix(mat);
	SHADER.m_spriteShader.DrawTex(tex, rect);

	DebugDraw();
}

void CharaBase::UpdateAnim()
{
    // アニメーション更新
    animTimer++;
    if (animTimer > 10)
    {
        animTimer = 0;
        animFrame++;
        if (animFrame >= 5) // 5枚アニメ
        {
            animFrame = 0;
        }
    }
}

void CharaBase::CalcDrawRect()
{
    // rect の X をフレーム分ずらす
    Math::Rectangle animRect = rect;
    animRect.x = animRect.width * animFrame;
    rect = animRect;
}