#include "UIManager.h"
#include <Pch.cpp>

void UIManager::Init()
{
}

void UIManager::Update()
{
}


void UIManager::Draw2D(int score)
{
	// BOX ‰¼•\Ž¦
	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
	SHADER.m_spriteShader.DrawBox(0, 300, 640, 60, &Math::Color(0, 0, 0, 1));
	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
	SHADER.m_spriteShader.DrawBox(0, -300, 640, 60, &Math::Color(0, 0, 0, 1));

	// Score‰¼•\Ž¦
	SHADER.m_spriteShader.DrawBox(0, 300, 250, 50, &Math::Color(1, 1, 1, 1), false);

	std::string padScore = std::to_string(score);
	while (padScore.size() < 6) 
	{
		padScore = "0" + padScore;
	}

	std::string scoreStr = "SCOREF" + padScore;

	SHADER.m_spriteShader.DrawString(-245, 342.5f, scoreStr.c_str(), Math::Vector4(1, 1, 1, 1), 1.3f);

	SHADER.m_spriteShader.End();
	SHADER.m_spriteShader.Begin();
}
