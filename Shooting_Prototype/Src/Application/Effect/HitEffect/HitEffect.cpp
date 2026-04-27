#include "HitEffect.h"

HitEffect::HitEffect(const Math::Vector2& pos)
	:m_pos(pos)
{
	rect = ASSET.GetRectangle("HitEffect");
}

void HitEffect::Update()
{
	animFrame += 1.0f;

	const float animMax = 12;
	if (animFrame >= animMax)
	{
		isDead = true;
	}
}

void HitEffect::Draw2D()
{
	Math::Matrix S = Math::Matrix::CreateScale(2.0f, 2.0f, 1.0f);
	Math::Matrix T = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0.0f);

	SHADER.m_spriteShader.SetMatrix(S * T);

	Math::Rectangle animRect(
		rect.x + 32 * animFrame,
		rect.y,
		32,
		rect.height
	);

	SHADER.m_spriteShader.DrawTex(ASSET.GetTexture("HitEffect"),animRect);
}
