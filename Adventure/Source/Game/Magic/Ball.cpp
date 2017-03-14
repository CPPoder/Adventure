#include "stdafx.h"
#include "Source\Game\Magic\Ball.hpp"

namespace Magic
{

	Ball::Ball(sf::Vector2f const & velocity, float damage, Type type)
		: mVelocity(velocity),
		  mDamage(damage),
		  mType(type)
	{

	}

	Ball::~Ball()
	{

	}

	Type Ball::getType() const
	{
		return mType;
	}
	sf::Vector2f Ball::getVelocity() const
	{
		return mVelocity;
	}
	float Ball::getDamage() const
	{
		return mDamage;
	}

} //Namespace Magic

