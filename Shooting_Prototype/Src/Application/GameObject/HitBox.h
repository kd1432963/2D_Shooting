#pragma once

class HitBox
{
public:

	//**********************************
	// Šî–{•Ï”
	//**********************************
	Math::Vector2	pos		= {};
	float			radius	= 0.0f;

public:

	//**********************************
	// ‰~Œ`“–‚½‚è”»’è
	//**********************************
	bool IsHit(const HitBox& other) const noexcept
	{
		float dx = pos.x - other.pos.x;
		float dy = pos.y - other.pos.y;

		float distSq = dx * dx + dy * dy;
		float r = radius + other.radius;

		return distSq <= r * r;
	}
};