#include "ExplosionEffect.h"

ExplosionEffect::ExplosionEffect(const Math::Vector2& pos)
	:m_pos(pos)
{
	SOUND.PlaySE("ExplosionSE");

	rect = ASSET.GetRectangle("ExplosionEffect");
}

ExplosionEffect::ExplosionEffect(const Math::Vector2& pos, bool isPlayer)
	:m_pos(pos)
{
	SOUND.PlaySE("ExplosionSE");
	rect = ASSET.GetRectangle("ExplosionEffect");
	m_isPlayer = isPlayer;
}

void ExplosionEffect::Update()
{
	if (!m_isPlayer)
	{
		animFrame += 0.8f;
	}
	else
	{
		animFrame += 0.25f;
	}

	const float animMax = 12;
	if (animFrame >= animMax)
	{
		isDead = true;
	}
}

void ExplosionEffect::Draw2D()
{
	if(m_isPlayer)
	D3D.SetBlendState(BlendMode::Add);

	Math::Matrix S = Math::Matrix::CreateScale(5.0f, 5.0f, 1.0f);
	Math::Matrix T = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0.0f);

	SHADER.m_spriteShader.SetMatrix(S * T);

	Math::Rectangle animRect(
		rect.x + 32 * ToInt(animFrame),
		rect.y,
		32,
		rect.height
	);

	SHADER.m_spriteShader.DrawTex(ASSET.GetTexture("ExplosionEffect"), animRect);

	if (m_isPlayer)
	D3D.SetBlendState(BlendMode::Alpha);
}
