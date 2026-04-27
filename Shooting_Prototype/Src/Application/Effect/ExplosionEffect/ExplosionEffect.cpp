#include "ExplosionEffect.h"

ExplosionEffect::ExplosionEffect(const Math::Vector2& pos)
	:m_pos(pos)
{
	rect = ASSET.GetRectangle("ExplosionEffect");
}

void ExplosionEffect::Update()
{
	animFrame += 1;

	const float animMax = 12;
	if (animFrame >= animMax)
	{
		isDead = true;
	}
}

void ExplosionEffect::Draw2D()
{
	Math::Matrix S = Math::Matrix::CreateScale(5.0f, 5.0f, 1.0f);
	Math::Matrix T = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0.0f);

	SHADER.m_spriteShader.SetMatrix(S * T);

	Math::Rectangle animRect(
		rect.x + 32 * animFrame,
		rect.y,
		32,
		rect.height
	);

	SHADER.m_spriteShader.DrawTex(ASSET.GetTexture("ExplosionEffect"), animRect);
}
