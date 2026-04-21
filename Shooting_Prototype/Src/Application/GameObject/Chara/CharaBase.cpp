#include "CharaBase.h"

void CharaBase::DrawChara()
{
	// •`‰æ
	SHADER.m_spriteShader.SetMatrix(mat);
	SHADER.m_spriteShader.DrawTex(tex, rect);
}
