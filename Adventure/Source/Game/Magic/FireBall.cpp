#include "stdafx.h"
#include "Source\Game\Magic\FireBall.hpp"

namespace Magic
{

	FireBall::FireBall(sf::Vector2f const & position, sf::Vector2f const & velocity, float damage)
		: Ball(velocity, damage, Type::FIRE),
		  mAnimation(TextureManager::TextureName::PLAYER_TEXTURE_ATLAS, mFireBallAnimTextRectPositions, mSizeOfFireBallTextRect, mAnimProgramOfFlyingFireBall, mAnimProgramOfFlyingFireBall.front(), mAnimationTime, position, true)
	{

	}
	FireBall::~FireBall()
	{

	}

	void FireBall::render(sf::RenderWindow* renderWindow)
	{
		mAnimation.render(renderWindow);
	}
	void FireBall::update(sf::Time const & frametime, sf::RenderWindow const * renderWindow)
	{
		mAnimation.update(frametime, renderWindow);
		mAnimation.move(this->getVelocity() * frametime.asSeconds());
		mTimeSinceCreation += frametime;
	}

	bool FireBall::getDurationExceeded() const
	{
		return (mTimeSinceCreation > mDuration);
	}



} //Namespace Magic

