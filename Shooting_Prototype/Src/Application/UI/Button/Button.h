#pragma once

class Button
{
public:

	Button() {};
	Button(const std::string& texStr,
		const Math::Vector2& pos,
		const Math::Vector2& scale,
		const Math::Vector2& half);
	~Button() {};

	void Update();
	void Update(const Math::Vector2&p);

	void Draw();

	std::function<void()>onClick = nullptr;
	std::function<void()>onHover = nullptr;
	std::function<void()>offHover = nullptr;

	float GetScale()const { return m_scale.x; }
	Math::Color GetColor()const { return m_color; }

private:

	bool OnHover();

private:

	//=== 座標 ====================================

	Math::Vector2 m_pos = {};

	//=== 元の拡大率保存用 ========================

	Math::Vector2 m_scale = { 1.0f, 1.0f };
	Math::Vector2 m_baseScale = { 1.0f, 1.0f };

	//=== 半径 ==================================

	Math::Vector2 m_half = {};

	//=== 画像の情報 ==============================

	KdTexture* mp_tex;
	Math::Rectangle m_rect = {};
	Math::Color m_color = { 1,1,1,1 };

	//=== Mouse のフラグ =========================

	bool m_isHover = false;
	bool m_isPressed = false;
};