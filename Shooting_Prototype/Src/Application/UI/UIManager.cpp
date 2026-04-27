#include "UIManager.h"

void UIManager::Init()
{
}

void UIManager::Update()
{
}


void UIManager::Draw2D()
{
	// BOX âºï\é¶
	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
	SHADER.m_spriteShader.DrawBox(0, 300, 640, 60, &Math::Color(0, 0, 0, 1));
	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
	SHADER.m_spriteShader.DrawBox(0, -300, 640, 60, &Math::Color(0, 0, 0, 1));

	// Scoreâºï\é¶
	SHADER.m_spriteShader.DrawBox(0, 300, 250, 50, &Math::Color(1, 1, 1, 1), false);
	SHADER.m_spriteShader.DrawString(-245, 342.5f, "SCOREÅF000000", Math::Vector4(1, 1, 1, 1), 1.3f);

	SHADER.m_spriteShader.End();
	SHADER.m_spriteShader.Begin();
}
