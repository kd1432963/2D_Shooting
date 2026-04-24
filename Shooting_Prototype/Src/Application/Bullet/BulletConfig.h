#pragma once

#include "BulletOwner.h"

struct BulletConfig
{
	std::string		texTag	= {};
	Math::Vector2	pos		= {};
	Math::Vector2	move	= {};
	int				atk		= 0;
	BulletOwner owner = BulletOwner::Player;
};