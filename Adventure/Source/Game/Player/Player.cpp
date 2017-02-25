#include "stdafx.h"
#include "Source\Game\Player\Player.hpp"



Player::Player(sf::Vector2f const & position)
	: mPlayerAnimation(TextureManager::TextureName::PLAYER_TEXTURE_ATLAS, mPlayerAnimTextRectPositions, mSizeOfPlayerTextRect, mAnimProgramOfStandingRight, mAnimProgramOfStandingRight.front(), sf::seconds(mPixelPerStep / mVelocity), position)
{
	mPlayerAnimationName = PlayerAnimationName::STANDING_RIGHT;
	float shadowRadius = 10.f;
	mPlayerShadow.setRadius(shadowRadius);
	mPlayerShadow.setFillColor(sf::Color(0, 0, 0, 100));
	mPlayerShadow.setOrigin(shadowRadius, shadowRadius);
	mPlayerShadow.setPosition(mPlayerAnimation.getPosition() + sf::Vector2f(0.f, 17.f));

}
Player::~Player()
{

}

void Player::update(sf::Time const & frametime, sf::RenderWindow const * renderWindow)
{
	this->handleMovement(frametime);

	mPlayerAnimation.update(frametime, renderWindow);
}
void Player::render(sf::RenderWindow* renderWindow)
{
	renderWindow->draw(mPlayerShadow);
	mPlayerAnimation.render(renderWindow);
}


void Player::move(sf::Vector2f const & direction)
{
	mPlayerAnimation.move(direction);
	mPlayerShadow.move(direction);
}


sf::Vector2f Player::getPosition() const
{
	return mPlayerAnimation.getPosition();
}



void Player::handleMovement(sf::Time const & frametime)
{
	//Handle UserInput
	bool keyRight = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right);
	bool keyUp = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up);
	bool keyLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left);
	bool keyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down);

	bool right = (keyRight && !keyUp && !keyLeft && !keyDown);
	bool rightUp = (keyRight && keyUp && !keyLeft && !keyDown);
	bool up = (!keyRight && keyUp && !keyLeft && !keyDown);
	bool upLeft = (!keyRight && keyUp && keyLeft && !keyDown);
	bool left = (!keyRight && !keyUp && keyLeft && !keyDown);
	bool leftDown = (!keyRight && !keyUp && keyLeft && keyDown);
	bool down = (!keyRight && !keyUp && !keyLeft && keyDown);
	bool downRight = (keyRight && !keyUp && !keyLeft && keyDown);

	bool newDirectionExists = false;
	PlayerDirection newDirection;

	do
	{
		if (right)
		{
			newDirection = PlayerDirection::RIGHT;
			newDirectionExists = true;
			break;
		}
		if (rightUp)
		{
			newDirection = PlayerDirection::RIGHT_UP;
			newDirectionExists = true;
			break;
		}
		if (up)
		{
			newDirection = PlayerDirection::UP;
			newDirectionExists = true;
			break;
		}
		if (upLeft)
		{
			newDirection = PlayerDirection::UP_LEFT;
			newDirectionExists = true;
			break;
		}
		if (left)
		{
			newDirection = PlayerDirection::LEFT;
			newDirectionExists = true;
			break;
		}
		if (leftDown)
		{
			newDirection = PlayerDirection::LEFT_DOWN;
			newDirectionExists = true;
			break;
		}
		if (down)
		{
			newDirection = PlayerDirection::DOWN;
			newDirectionExists = true;
			break;
		}
		if (downRight)
		{
			newDirection = PlayerDirection::DOWN_RIGHT;
			newDirectionExists = true;
			break;
		}
	} while (false);
	
	if (mPlayerState == PlayerState::STANDING)
	{
		if (newDirectionExists)
		{
			this->setPlayerStateAndDirection(PlayerState::WALKING, newDirection);
		}
	}
	else // mPlayerState == PlayerState::WALKING
	{
		if (newDirectionExists)
		{
			this->setPlayerStateAndDirection(PlayerState::WALKING, newDirection);
		}
		else
		{
			this->setPlayerStateAndDirection(PlayerState::STANDING, mPlayerDirection);
		}
	}


	//Move Animation
	if (mPlayerState == PlayerState::WALKING)
	{
		this->move(this->getUnitVectorInDirection(mPlayerDirection) * mVelocity * frametime.asSeconds());
	}



}




void Player::setPlayerStateAndDirection(PlayerState playerState, PlayerDirection playerDirection)
{
	mPlayerState = playerState;
	mPlayerDirection = playerDirection;
	PlayerAnimationName newAnim = this->getPlayerAnimationName(mPlayerState, mPlayerDirection);
	if (newAnim != mPlayerAnimationName)
	{
		mPlayerAnimationName = newAnim;
		this->changeAnimation();
	}
}



void Player::changeAnimation()
{
	switch (mPlayerAnimationName)
	{
	case PlayerAnimationName::STANDING_RIGHT:
		mPlayerAnimation.useAnimationProgram(mAnimProgramOfStandingRight, mAnimProgramOfStandingRight.front());
		break;
	case PlayerAnimationName::STANDING_UP:
		mPlayerAnimation.useAnimationProgram(mAnimProgramOfStandingUp, mAnimProgramOfStandingUp.front());
		break;
	case PlayerAnimationName::STANDING_LEFT:
		mPlayerAnimation.useAnimationProgram(mAnimProgramOfStandingLeft, mAnimProgramOfStandingLeft.front());
		break;
	case PlayerAnimationName::STANDING_DOWN:
		mPlayerAnimation.useAnimationProgram(mAnimProgramOfStandingDown, mAnimProgramOfStandingDown.front());
		break;
	case PlayerAnimationName::WALKING_RIGHT:
		mPlayerAnimation.useAnimationProgram(mAnimProgramOfWalkingRight, mAnimProgramOfWalkingRight.front());
		break;
	case PlayerAnimationName::WALKING_UP:
		mPlayerAnimation.useAnimationProgram(mAnimProgramOfWalkingUp, mAnimProgramOfWalkingUp.front());
		break;
	case PlayerAnimationName::WALKING_LEFT:
		mPlayerAnimation.useAnimationProgram(mAnimProgramOfWalkingLeft, mAnimProgramOfWalkingLeft.front());
		break;
	case PlayerAnimationName::WALKING_DOWN:
		mPlayerAnimation.useAnimationProgram(mAnimProgramOfWalkingDown, mAnimProgramOfWalkingDown.front());
		break;
	}
}






PlayerAnimationName Player::getPlayerAnimationName(PlayerState playerState, PlayerDirection playerDirection)
{
	switch (playerState)
	{
	case PlayerState::STANDING:
	{
		switch (playerDirection)
		{
		case PlayerDirection::RIGHT:
		{
			return PlayerAnimationName::STANDING_RIGHT;
			break;
		}
		case PlayerDirection::RIGHT_UP:
		{
			return PlayerAnimationName::STANDING_RIGHT;
			break;
		}
		case PlayerDirection::UP:
		{
			return PlayerAnimationName::STANDING_UP;
			break;
		}
		case PlayerDirection::UP_LEFT:
		{
			return PlayerAnimationName::STANDING_LEFT;
			break;
		}
		case PlayerDirection::LEFT:
		{
			return PlayerAnimationName::STANDING_LEFT;
			break;
		}
		case PlayerDirection::LEFT_DOWN:
		{
			return PlayerAnimationName::STANDING_LEFT;
			break;
		}
		case PlayerDirection::DOWN:
		{
			return PlayerAnimationName::STANDING_DOWN;
			break;
		}
		case PlayerDirection::DOWN_RIGHT:
		{
			return PlayerAnimationName::STANDING_RIGHT;
			break;
		}
		}
		break;
	}
	case PlayerState::WALKING:
	{
		switch (playerDirection)
		{
		case PlayerDirection::RIGHT:
		{
			return PlayerAnimationName::WALKING_RIGHT;
			break;
		}
		case PlayerDirection::RIGHT_UP:
		{
			return PlayerAnimationName::WALKING_RIGHT;
			break;
		}
		case PlayerDirection::UP:
		{
			return PlayerAnimationName::WALKING_UP;
			break;
		}
		case PlayerDirection::UP_LEFT:
		{
			return PlayerAnimationName::WALKING_LEFT;
			break;
		}
		case PlayerDirection::LEFT:
		{
			return PlayerAnimationName::WALKING_LEFT;
			break;
		}
		case PlayerDirection::LEFT_DOWN:
		{
			return PlayerAnimationName::WALKING_LEFT;
			break;
		}
		case PlayerDirection::DOWN:
		{
			return PlayerAnimationName::WALKING_DOWN;
			break;
		}
		case PlayerDirection::DOWN_RIGHT:
		{
			return PlayerAnimationName::WALKING_RIGHT;
			break;
		}
		}
		break;
	}
	}
}


sf::Vector2f Player::getUnitVectorInDirection(PlayerDirection direction)
{
	switch (direction)
	{
	case PlayerDirection::RIGHT:
		return sf::Vector2f(1.f, 0.f);
	case PlayerDirection::RIGHT_UP:
		return sf::Vector2f(1.f, -1.f) / myMath::Const::SQRT2f;
	case PlayerDirection::UP:
		return sf::Vector2f(0.f, -1.f);
		case PlayerDirection::UP_LEFT:
		return sf::Vector2f(-1.f, -1.f) / myMath::Const::SQRT2f;
	case PlayerDirection::LEFT:
		return sf::Vector2f(-1.f, 0.f);
	case PlayerDirection::LEFT_DOWN:
		return sf::Vector2f(-1.f, 1.f) / myMath::Const::SQRT2f;
	case PlayerDirection::DOWN:
		return sf::Vector2f(0.f, 1.f);
	case PlayerDirection::DOWN_RIGHT:
		return sf::Vector2f(1.f, 1.f) / myMath::Const::SQRT2f;
	}
}


