#pragma once

class EffectBase
{
public:
	virtual ~EffectBase() = default;

	virtual void Update() = 0;
	virtual void Draw2D() = 0;

	bool IsDead() const { return isDead; }

protected:
	bool isDead = false;
	float animFrame = 0;
	Math::Rectangle rect = {};
};
