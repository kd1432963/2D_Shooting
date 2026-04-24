#include "CharaBase.h"

void CharaBase::DrawChara()
{
	SHADER.m_spriteShader.SetMatrix(mat);
	SHADER.m_spriteShader.DrawTex(tex, rect);
}