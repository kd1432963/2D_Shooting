#include "ItemBase.h"

ItemBase::ItemBase(ItemType t)
	:type(t)
{
}

void ItemBase::Update()
{
	UpdatePos();

	move.x = -3;

	UpdateMatrix();
}

void ItemBase::Draw2D()
{
	SHADER.m_spriteShader.SetMatrix(mat);
	SHADER.m_spriteShader.DrawTex(tex, rect);

	DebugDraw();
}
