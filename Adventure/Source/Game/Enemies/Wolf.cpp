#include "stdafx.h"
#include "Source\Game\Enemies\Wolf.hpp"


namespace Enemy
{

	Wolf::Wolf(sf::Vector2f const & position)
		: Enemy::Enemy(StatusValues(20, 0, 0, 0, 0, 0, 0, 40)),
		  mWolfAnimation(TextureManager::TextureName::WOLF_TEXTURE_ATLAS, sWolfAnimTextRectPositions, sSizeOfWolfTextRect, sAnimProgramOfStandingDown, sAnimProgramOfStandingDown.front(), sf::seconds(sPixelPerJumpStep / StatusValues::convertSpeedIntoPixelPerSecond(mStatusValues.speed)), position),
		  mWolfBrain(WolfMovementBehaviour::STATIC)
	{
		mWolfAnimationName = WolfAnimationName::STANDING_DOWN;
		mWolfCollisionArea.addShape(mySFML::Class::RectShape(position + sf::Vector2f(0.f, 15.f), sf::Vector2f(15.f, 15.f), sf::Color::Green, true).pointer);
	}

	void Wolf::update(sf::Time const & frametime, sf::RenderWindow const * renderWindow, TileMap const & tileMap)
	{
		this->handleMovement(frametime, tileMap);
		mWolfAnimation.update(frametime, renderWindow);
	}
	void Wolf::render(sf::RenderWindow* renderWindow)
	{
		mWolfAnimation.render(renderWindow);
		//mWolfCollisionArea.render(renderWindow);
	}

	void Wolf::moveObjects(sf::Vector2f const & movement)
	{
		mWolfAnimation.move(movement);
		mWolfCollisionArea.move(movement);
	}
	void Wolf::tryToMove(sf::Vector2f const & movement, TileMap const & tileMap)
	{
		this->moveObjects(movement);
		if (this->checkIfCollisionOccured(tileMap))
		{
			this->undoLastMovement(movement);
		}
	}


	sf::Vector2f Wolf::getPosition() const
	{
		return mWolfAnimation.getPosition();
	}


	void Wolf::handleMovement(sf::Time const & frametime, TileMap const & tileMap)
	{
		//Somehow get next WolfMovement
		WolfMovement newWolfMovement = mWolfBrain.getNextWolfMovement(WolfMovementInput());
		WolfState newWolfState = newWolfMovement.wolfState;
		WolfDirection newWolfDirection = newWolfMovement.wolfDirection;

		//Set WolfState and Animation
		this->setWolfStateAndDirection(newWolfState, newWolfDirection);

		//Move Animation
		if (mWolfState == WolfState::WALKING)
		{
			float velocity = StatusValues::convertSpeedIntoPixelPerSecond(mStatusValues.speed);
			this->tryToMove(this->getUnitVectorInDirection(mWolfDirection) * velocity * frametime.asSeconds(), tileMap);
		}
	}

	void Wolf::setWolfStateAndDirection(WolfState wolfState, WolfDirection wolfDirection)
	{
		mWolfState = wolfState;
		mWolfDirection = wolfDirection;
		WolfAnimationName newAnim = this->getWolfAnimationName(mWolfState, mWolfDirection);
		if (newAnim != mWolfAnimationName)
		{
			mWolfAnimationName = newAnim;
			this->changeAnimation();
		}
	}

	void Wolf::changeAnimation()
	{
		switch (mWolfAnimationName)
		{
		case WolfAnimationName::STANDING_RIGHT:
			mWolfAnimation.useAnimationProgram(sAnimProgramOfStandingRight, sAnimProgramOfStandingRight.front());
			break;
		case WolfAnimationName::STANDING_UP:
			mWolfAnimation.useAnimationProgram(sAnimProgramOfStandingUp, sAnimProgramOfStandingUp.front());
			break;
		case WolfAnimationName::STANDING_LEFT:
			mWolfAnimation.useAnimationProgram(sAnimProgramOfStandingLeft, sAnimProgramOfStandingLeft.front());
			break;
		case WolfAnimationName::STANDING_DOWN:
			mWolfAnimation.useAnimationProgram(sAnimProgramOfStandingDown, sAnimProgramOfStandingDown.front());
			break;
		case WolfAnimationName::WALKING_RIGHT:
			mWolfAnimation.useAnimationProgram(sAnimProgramOfWalkingRight, sAnimProgramOfWalkingRight.front());
			break;
		case WolfAnimationName::WALKING_UP:
			mWolfAnimation.useAnimationProgram(sAnimProgramOfWalkingUp, sAnimProgramOfWalkingUp.front());
			break;
		case WolfAnimationName::WALKING_LEFT:
			mWolfAnimation.useAnimationProgram(sAnimProgramOfWalkingLeft, sAnimProgramOfWalkingLeft.front());
			break;
		case WolfAnimationName::WALKING_DOWN:
			mWolfAnimation.useAnimationProgram(sAnimProgramOfWalkingDown, sAnimProgramOfWalkingDown.front());
			break;
		}
	}

	bool Wolf::checkIfCollisionOccured(TileMap const & tileMap) const
	{
		auto listOfBorders = tileMap.getListOfBorders();
		for (auto& border : listOfBorders)
		{
			if (mWolfCollisionArea.checkCollisionWith(Line(static_cast<sf::Vector2f>(border.point1) * static_cast<float>(TileMap::sSizeOfATile), static_cast<sf::Vector2f>(border.point2) * static_cast<float>(TileMap::sSizeOfATile))))
			{
				return true;
			}
		}
		return false;
	}

	void Wolf::undoLastMovement(sf::Vector2f const & lastMovement)
	{
		this->moveObjects(-lastMovement);
		this->setWolfStateAndDirection(WolfState::STANDING, mWolfDirection);
	}



	WolfAnimationName Wolf::getWolfAnimationName(WolfState wolfState, WolfDirection wolfDirection)
	{
		switch (wolfState)
		{
		case WolfState::STANDING:
		{
			switch (wolfDirection)
			{
			case WolfDirection::RIGHT:
			{
				return WolfAnimationName::STANDING_RIGHT;
				break;
			}
			case WolfDirection::RIGHT_UP:
			{
				return WolfAnimationName::STANDING_RIGHT;
				break;
			}
			case WolfDirection::UP:
			{
				return WolfAnimationName::STANDING_UP;
				break;
			}
			case WolfDirection::UP_LEFT:
			{
				return WolfAnimationName::STANDING_LEFT;
				break;
			}
			case WolfDirection::LEFT:
			{
				return WolfAnimationName::STANDING_LEFT;
				break;
			}
			case WolfDirection::LEFT_DOWN:
			{
				return WolfAnimationName::STANDING_LEFT;
				break;
			}
			case WolfDirection::DOWN:
			{
				return WolfAnimationName::STANDING_DOWN;
				break;
			}
			case WolfDirection::DOWN_RIGHT:
			{
				return WolfAnimationName::STANDING_RIGHT;
				break;
			}
			}
			break;
		}
		case WolfState::WALKING:
		{
			switch (wolfDirection)
			{
			case WolfDirection::RIGHT:
			{
				return WolfAnimationName::WALKING_RIGHT;
				break;
			}
			case WolfDirection::RIGHT_UP:
			{
				return WolfAnimationName::WALKING_RIGHT;
				break;
			}
			case WolfDirection::UP:
			{
				return WolfAnimationName::WALKING_UP;
				break;
			}
			case WolfDirection::UP_LEFT:
			{
				return WolfAnimationName::WALKING_LEFT;
				break;
			}
			case WolfDirection::LEFT:
			{
				return WolfAnimationName::WALKING_LEFT;
				break;
			}
			case WolfDirection::LEFT_DOWN:
			{
				return WolfAnimationName::WALKING_LEFT;
				break;
			}
			case WolfDirection::DOWN:
			{
				return WolfAnimationName::WALKING_DOWN;
				break;
			}
			case WolfDirection::DOWN_RIGHT:
			{
				return WolfAnimationName::WALKING_RIGHT;
				break;
			}
			}
			break;
		}
		}
	}

	sf::Vector2f Wolf::getUnitVectorInDirection(WolfDirection direction)
	{
		switch (direction)
		{
		case WolfDirection::RIGHT:
			return sf::Vector2f(1.f, 0.f);
		case WolfDirection::RIGHT_UP:
			return sf::Vector2f(1.f, -1.f) / myMath::Const::SQRT2f;
		case WolfDirection::UP:
			return sf::Vector2f(0.f, -1.f);
		case WolfDirection::UP_LEFT:
			return sf::Vector2f(-1.f, -1.f) / myMath::Const::SQRT2f;
		case WolfDirection::LEFT:
			return sf::Vector2f(-1.f, 0.f);
		case WolfDirection::LEFT_DOWN:
			return sf::Vector2f(-1.f, 1.f) / myMath::Const::SQRT2f;
		case WolfDirection::DOWN:
			return sf::Vector2f(0.f, 1.f);
		case WolfDirection::DOWN_RIGHT:
			return sf::Vector2f(1.f, 1.f) / myMath::Const::SQRT2f;
		}
	}








	//Static Variables
	const float Wolf::sPixelPerJumpStep = 20.f;

	const sf::Vector2f Wolf::sSizeOfWolfTextRect = sf::Vector2f(64.f, 64.f);
	const Animation::TextRectPositions Wolf::sWolfAnimTextRectPositions = {
		{ 0.f, 0.f },{ 32.f, 0.f },{ 64.f, 0.f },			//Right
		{ 0.f, 64.f },{ 32.f, 64.f },{ 64.f, 64.f },		//Up
		{ 0.f, 128.f },{ 32.f, 128.f },{ 64.f, 128.f },		//Left
		{ 0.f, 0.f },{ 64.f, 0.f },{ 128.f, 0.f }			//Down
	};
	const Animation::AnimProgram Wolf::sAnimProgramOfStandingRight = { 0u };
	const Animation::AnimProgram Wolf::sAnimProgramOfStandingUp = { 3u };
	const Animation::AnimProgram Wolf::sAnimProgramOfStandingLeft = { 6u };
	const Animation::AnimProgram Wolf::sAnimProgramOfStandingDown = { 9u };
	const Animation::AnimProgram Wolf::sAnimProgramOfWalkingRight = { 1u, 2u };
	const Animation::AnimProgram Wolf::sAnimProgramOfWalkingUp = { 4u, 5u };
	const Animation::AnimProgram Wolf::sAnimProgramOfWalkingLeft = { 7u, 8u };
	const Animation::AnimProgram Wolf::sAnimProgramOfWalkingDown = { 10u, 11u };





} //Namespace Enemy

