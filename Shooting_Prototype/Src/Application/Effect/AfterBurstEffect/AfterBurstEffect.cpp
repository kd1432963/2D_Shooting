#include "AfterBurstEffect.h"

AfterBurstEffect::AfterBurstEffect(const Math::Vector2& pos)
	:m_pos(pos)
{
	rect = ASSET.GetRectangle("AfterBurstEffect");
}

void AfterBurstEffect::Update()
{
	animFrame += 0.45f;

	const float animMax = 9;
	if (animFrame >= animMax)
	{
		isDead = true;
	}
}

void AfterBurstEffect::Draw2D()
{
	D3D.SetBlendState(BlendMode::Add);

	Math::Matrix S = Math::Matrix::CreateScale(1.5f, 1.5f, 1.0f);
	Math::Matrix T = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0.0f);

	SHADER.m_spriteShader.SetMatrix(S * T);

	Math::Rectangle animRect(
		rect.x + 32 * ToInt(animFrame),
		rect.y,
		32,
		rect.height
	);

	SHADER.m_spriteShader.DrawTex(ASSET.GetTexture("AfterBurstEffect"), animRect);

	D3D.SetBlendState(BlendMode::Alpha);
}
