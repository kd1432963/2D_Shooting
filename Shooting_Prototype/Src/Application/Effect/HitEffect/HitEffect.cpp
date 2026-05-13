#include "HitEffect.h"

HitEffect::HitEffect(const Math::Vector2& pos)
	:m_pos(pos)
{
	rect = ASSET.GetRectangle("HitEffect");
}

void HitEffect::Update()
{
	animFrame += 0.7f;

	const float animMax = 12;
	if (animFrame >= animMax)
	{
		isDead = true;
	}
}

void HitEffect::Draw2D()
{
	Math::Matrix S = Math::Matrix::CreateScale(2.5f, 2.5f, 1.0f);
	Math::Matrix T = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0.0f);

	SHADER.m_spriteShader.SetMatrix(S * T);

	Math::Rectangle animRect(
		rect.x + 32 * ToInt(animFrame),
		rect.y,
		32,
		rect.height
	);

	SHADER.m_spriteShader.DrawTex(ASSET.GetTexture("HitEffect"),animRect);
}
