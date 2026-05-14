#include "Button.h"

Button::Button(const std::string& texStr,
	const Math::Vector2& pos,
	const Math::Vector2& scale,
	const Math::Vector2& half)
	:m_pos(pos), m_scale(scale), m_half(half)
{
	mp_tex = ASSET.GetTexture(texStr);
	m_rect = ASSET.GetRectangle(texStr);

	m_baseScale = scale;
}

void Button::Update()
{
	//=== マウスが重なっているか ==================================

	m_isHover = OnHover();

	//=== ホバーした瞬間だけ音を鳴らす ==============================
	if (m_isHover && !m_prevHover)
	{
		SOUND.PlaySE("HoverSE");
	}

	//=== 重なっていれば呼び出す ==================================

	if (m_isHover)
	{
		if (onHover)
		{
			onHover();
		}
	}

	//=== 重なっていなければ呼び出す ==============================

	else
	{
		if (offHover)
		{
			offHover();
		}
	}

	//=== ホバー中にクリックすれば押下中 ==================================

	if (m_isHover && MOUSE.IsPressLeft())
	{
		m_isPressed = true;
	}

	//=== 離されたらクリック成立 ===========================================

	if (m_isPressed && MOUSE.IsReleaseLeft())
	{
		if (m_isHover && onClick)onClick();
		m_isPressed = false;
	}

	//=== 外に出たらクリックキャンセル ======================================

	if (m_isPressed && !m_isHover && MOUSE.IsPressLeft())m_isPressed = false;

	//=== 押下中は色を変える ================================================

	m_color = m_isPressed ?
		Math::Color(0.9f, 0.9f, 0.9f, 1.0f) :
		Math::Color(1.0f, 1.0f, 1.0f, 1.0f);

	//=== ボタンらしく大きさを変える ============================

	constexpr float kDiff = 0.02f;
	constexpr float kLerp = 0.15f;

	// 目標拡大率
	float targetScale = m_baseScale.x;

	if (m_isPressed)
	{
		targetScale -= kDiff;
	}
	else if (m_isHover)
	{
		targetScale += kDiff;
	}

	// 補間
	m_scale.x += (targetScale - m_scale.x) * kLerp;

	m_scale.y = m_scale.x;

	m_prevHover = m_isHover;
}

void Button::Update(const Math::Vector2& p)
{

	m_pos = p;

	//=== マウスが重なっているか ==================================

	m_isHover = OnHover();

	//=== ホバーした瞬間だけ音を鳴らす ==============================
	if (m_isHover && !m_prevHover)
	{
		SOUND.PlaySE("HoverSE");
	}

	//=== 重なっていれば呼び出す ==================================

	if (m_isHover)
	{
		if (onHover)
		{
			onHover();
		}
	}

	//=== 重なっていなければ呼び出す ==============================

	else
	{
		if (offHover)
		{
			offHover();
		}
	}

	//=== ホバー中にクリックすれば押下中 ==================================

	if (m_isHover && MOUSE.IsPressLeft())
	{
		m_isPressed = true;
	}

	//=== 離されたらクリック成立 ===========================================

	if (m_isPressed && MOUSE.IsReleaseLeft())
	{
		if (m_isHover && onClick)onClick();
		m_isPressed = false;
	}

	//=== 外に出たらクリックキャンセル ======================================

	if (m_isPressed && !m_isHover && MOUSE.IsPressLeft())m_isPressed = false;

	//=== 押下中は色を変える ================================================

	m_color = m_isPressed ?
		Math::Color(0.9f, 0.9f, 0.9f, 1.0f) :
		Math::Color(1.0f, 1.0f, 1.0f, 1.0f);

	//=== ボタンらしく大きさを変える ============================

	constexpr float kDiff = 0.02f;
	constexpr float kLerp = 0.15f;

	// 目標拡大率
	float targetScale = m_baseScale.x;

	if (m_isPressed)
	{
		targetScale -= kDiff;
	}
	else if (m_isHover)
	{
		targetScale += kDiff;
	}

	// 補間
	m_scale.x += (targetScale - m_scale.x) * kLerp;

	m_scale.y = m_scale.x;

	m_prevHover = m_isHover;
}

void Button::Draw()
{
	Math::Matrix S = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 1.0f);
	Math::Matrix T = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0.0f);

	SHADER.m_spriteShader.SetMatrix(S * T);
	SHADER.m_spriteShader.DrawTex(mp_tex, 0, 0, &m_rect, &m_color);

#if _DEBUG

	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
	// 四隅の座標を計算
	float l = m_pos.x - m_half.x;
	float r = m_pos.x + m_half.x;
	float t = m_pos.y + m_half.y;
	float b = m_pos.y - m_half.y;

	// 上辺
	SHADER.m_spriteShader.DrawLine(l, t, r, t);
	// 下辺                                 
	SHADER.m_spriteShader.DrawLine(l, b, r, b);
	// 左辺                                  
	SHADER.m_spriteShader.DrawLine(l, t, l, b);
	// 右辺                                  
	SHADER.m_spriteShader.DrawLine(r, t, r, b);

	SHADER.m_spriteShader.End();
	SHADER.m_spriteShader.Begin();
#endif
}

bool Button::OnHover()
{
	int mX = MOUSE.GetPos().x;
	int mY = MOUSE.GetPos().y;

	return (mX >= m_pos.x - m_half.x &&
		mX <= m_pos.x + m_half.x &&
		mY >= m_pos.y - m_half.y &&
		mY <= m_pos.y + m_half.y);
}
