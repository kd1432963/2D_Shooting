#include "TransitionController.h"

//+++++++++++++++++++++++++++++++++++++++++
// フェード開始（FadeOut）
//+++++++++++++++++++++++++++++++++++++++++
void TransitionController::Start(float time)
{
	m_time = time;
	m_timer = 0.0f;
	m_state = State::FadeOut;
}

//+++++++++++++++++++++++++++++++++++++++++
// 更新
//+++++++++++++++++++++++++++++++++++++++++
void TransitionController::Update(float deltaTime)
{
	if (m_state == State::None) return;

	m_timer += deltaTime;

	switch (m_state)
	{
	case State::FadeOut:
		if (m_timer >= m_time)
		{
			m_timer = m_time;
			m_state = State::Switch;
		}
		break;

	case State::FadeIn:
		if (m_timer >= m_time)
		{
			m_timer = m_time;
			m_state = State::None;
		}
		break;

	default:
		break;
	}
}

//+++++++++++++++++++++++++++++++++++++++++
// 描画
//+++++++++++++++++++++++++++++++++++++++++
void TransitionController::Draw() const
{
	if (m_state == State::None) return;

	float alpha = 0.0f;

	if (m_state == State::FadeOut)
	{
		alpha = m_timer / m_time;
	}
	else if (m_state == State::FadeIn)
	{
		alpha = 1.0f - (m_timer / m_time);
	}
	else if (m_state == State::Switch)
	{
		alpha = 1.0f;
	}

	// ボックス表示
	SHADER.m_spriteShader.End();
	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
	SHADER.m_spriteShader.DrawBox(0, 0, 640, 360, &Math::Color{ 0,0,0,alpha });
}

//+++++++++++++++++++++++++++++++++++++++++
// 切り替えタイミング
//+++++++++++++++++++++++++++++++++++++++++
bool TransitionController::IsSwitchTiming() const
{
	return m_state == State::Switch;
}

//+++++++++++++++++++++++++++++++++++++++++
// フェードイン開始
//+++++++++++++++++++++++++++++++++++++++++
void TransitionController::StartFadeIn()
{
	m_timer = 0.0f;
	m_state = State::FadeIn;
}

//+++++++++++++++++++++++++++++++++++++++++
// フェード中かどうか
//+++++++++++++++++++++++++++++++++++++++++
bool TransitionController::IsActive() const
{
	return m_state != State::None;
}