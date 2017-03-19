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

	mPlayerCollisionArea.addShape(mySFML::Class::RectShape(position + sf::Vector2f(0.f, 15.f), sf::Vector2f(15.f, 15.f), sf::Color::Green, true).pointer);
}
Player::~Player()
{

}

void Player::update(sf::Time const & frametime, sf::RenderWindow const * renderWindow, TileMap const & tileMap)
{
	this->handleMovement(frametime, tileMap);
	this->handleFireBallCreation();
	mPlayerAnimation.update(frametime, renderWindow);


}
void Player::render(sf::RenderWindow* renderWindow)
{
	renderWindow->draw(mPlayerShadow);
	mPlayerAnimation.render(renderWindow);
	//mPlayerCollisionArea.render(renderWindow);
}


void Player::moveObjects(sf::Vector2f const & movement)
{
	mPlayerAnimation.move(movement);
	mPlayerShadow.move(movement);
	mPlayerCollisionArea.move(movement);
}

void Player::tryToMove(sf::Vector2f const & movement, TileMap const & tileMap)
{
	this->moveObjects(movement);
	if (this->checkIfCollisionOccured(tileMap))
	{
		if (mHitBorderSoundClock.getElapsedTime() > mHitBorderSoundTime)
		{
			mHitBorderSoundClock.restart();
			SoundManager::playOnce(SoundName::HIT_BORDER, 10.f, sf::Vector3f(), true);
		}
		this->undoLastMovement(movement);
	}
}


sf::Vector2f Player::getPosition() const
{
	return mPlayerAnimation.getPosition();
}


std::list<Magic::FireBall*>& Player::getAccessToListOfFireBalls()
{
	return mListOfFireBalls;
}



void Player::handleMovement(sf::Time const & frametime, TileMap const & tileMap)
{
	//Handle UserInput
	bool keyRight = Settings::ControlSettings::checkIfSomeKeyOfActionIsPressed(Settings::ControlSettings::Action::WALK_RIGHT);
	bool keyUp = Settings::ControlSettings::checkIfSomeKeyOfActionIsPressed(Settings::ControlSettings::Action::WALK_UP);
	bool keyLeft = Settings::ControlSettings::checkIfSomeKeyOfActionIsPressed(Settings::ControlSettings::Action::WALK_LEFT);
	bool keyDown = Settings::ControlSettings::checkIfSomeKeyOfActionIsPressed(Settings::ControlSettings::Action::WALK_DOWN);

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
	else if (mPlayerState == PlayerState::WALKING) // mPlayerState == PlayerState::WALKING
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
		this->tryToMove(this->getUnitVectorInDirection(mPlayerDirection) * mVelocity * frametime.asSeconds(), tileMap);
	}

}


void Player::handleFireBallCreation()
{
	if (mPlayerState != PlayerState::SHOOT_FIRE_BALL)
	{
		if (Settings::ControlSettings::checkIfSomeKeyOfActionIsPressed(Settings::ControlSettings::Action::ATTACK) && mFireBallCoolDownClock.getElapsedTime() > mFireBallCoolDown)
		{
			//Go into ShootFireBall State
			this->setPlayerStateAndDirection(PlayerState::SHOOT_FIRE_BALL, mPlayerDirection);
		}
	}
	else
	{
		if (mActualStateClock.getElapsedTime() > mTimeToShootFireBall)
		{
			//Return to Standing State and Create FireBall
			this->setPlayerStateAndDirection(PlayerState::STANDING, mPlayerDirection);
			mListOfFireBalls.push_back(new Magic::FireBall(this->calculateFireBallPosition(), this->calculateFireBallVelocity(), this->calculateFireBallDamage()));
			mFireBallCoolDownClock.restart();
		}
	}

}


void Player::setPlayerStateAndDirection(PlayerState playerState, PlayerDirection playerDirection)
{
	mPlayerState = playerState;
	mPlayerDirection = playerDirection;
	mActualStateClock.restart();
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
	case PlayerAnimationName::SHOOT_FIRE_BALL_RIGHT:
		mPlayerAnimation.useAnimationProgram(mAnimProgramOfShootingFireBallRight, mAnimProgramOfShootingFireBallRight.front());
		break;
	case PlayerAnimationName::SHOOT_FIRE_BALL_UP:
		mPlayerAnimation.useAnimationProgram(mAnimProgramOfShootingFireBallUp, mAnimProgramOfShootingFireBallUp.front());
		break;
	case PlayerAnimationName::SHOOT_FIRE_BALL_LEFT:
		mPlayerAnimation.useAnimationProgram(mAnimProgramOfShootingFireBallLeft, mAnimProgramOfShootingFireBallLeft.front());
		break;
	case PlayerAnimationName::SHOOT_FIRE_BALL_DOWN:
		mPlayerAnimation.useAnimationProgram(mAnimProgramOfShootingFireBallDown, mAnimProgramOfShootingFireBallDown.front());
		break;
	}
}


bool Player::checkIfCollisionOccured(TileMap const & tileMap) const
{
	auto listOfBorders = tileMap.getListOfBorders();
	for (auto& border : listOfBorders)
	{
		if (mPlayerCollisionArea.checkCollisionWith(Line(static_cast<sf::Vector2f>(border.point1) * static_cast<float>(TileMap::sSizeOfATile), static_cast<sf::Vector2f>(border.point2) * static_cast<float>(TileMap::sSizeOfATile))))
		{
			return true;
		}
	}
	return false;
}

void Player::undoLastMovement(sf::Vector2f const & lastMovement)
{
	this->moveObjects(-lastMovement);
	this->setPlayerStateAndDirection(PlayerState::STANDING, mPlayerDirection);
}



sf::Vector2f Player::calculateFireBallPosition() const
{
	sf::Vector2f const correctionDueToHandPos = sf::Vector2f(8.f, 4.f);
	return mPlayerAnimation.getPosition() + correctionDueToHandPos;
}
sf::Vector2f Player::calculateFireBallVelocity() const
{
	return this->getUnitVectorInDirection(mPlayerDirection) * 200.f;
}
float Player::calculateFireBallDamage() const
{
	return 1.f;
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
	case PlayerState::SHOOT_FIRE_BALL:
	{
		switch (playerDirection)
		{
		case PlayerDirection::RIGHT:
		{
			return PlayerAnimationName::SHOOT_FIRE_BALL_RIGHT;
			break;
		}
		case PlayerDirection::RIGHT_UP:
		{
			return PlayerAnimationName::SHOOT_FIRE_BALL_RIGHT;
			break;
		}
		case PlayerDirection::UP:
		{
			return PlayerAnimationName::SHOOT_FIRE_BALL_UP;
			break;
		}
		case PlayerDirection::UP_LEFT:
		{
			return PlayerAnimationName::SHOOT_FIRE_BALL_LEFT;
			break;
		}
		case PlayerDirection::LEFT:
		{
			return PlayerAnimationName::SHOOT_FIRE_BALL_LEFT;
			break;
		}
		case PlayerDirection::LEFT_DOWN:
		{
			return PlayerAnimationName::SHOOT_FIRE_BALL_LEFT;
			break;
		}
		case PlayerDirection::DOWN:
		{
			return PlayerAnimationName::SHOOT_FIRE_BALL_DOWN;
			break;
		}
		case PlayerDirection::DOWN_RIGHT:
		{
			return PlayerAnimationName::SHOOT_FIRE_BALL_RIGHT;
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


