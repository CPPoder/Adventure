#include "stdafx.h"
#include "Source/Game/Enemies/WolfBrain.hpp"
#include "SFML\Graphics.hpp"

namespace Enemy
{


	WolfBrain::WolfBrain(WolfMovementBehaviour movementBehaviour)
		: mMovementBehaviour(movementBehaviour)
	{

	}

	WolfMovementBehaviour WolfBrain::getMovementBehaviour() const
	{
		return mMovementBehaviour;
	}

	void WolfBrain::setMovementBehaviour(WolfMovementBehaviour movementBehaviour)
	{
		mMovementBehaviour = movementBehaviour;
	}

	WolfMovement WolfBrain::getNextWolfMovement(WolfMovementInput const & wolfMovementInput) const
	{
		static sf::Clock clock;
		static int dir(0);
		if (clock.getElapsedTime() > sf::seconds(1.f))
		{
			clock.restart();
			dir = dir + 1;
			if (dir > 7)
			{
				dir = 0;
			}
		}
		switch (mMovementBehaviour)
		{
		case WolfMovementBehaviour::STATIC:
			switch (dir)
			{
			case 0:
				return WolfMovement(WolfState::WALKING, WolfDirection::RIGHT);
				break;
			case 1:
				return WolfMovement(WolfState::STANDING, WolfDirection::RIGHT);
				break;
			case 2:
				return WolfMovement(WolfState::WALKING, WolfDirection::RIGHT);
				break;
			case 3:
				return WolfMovement(WolfState::WALKING, WolfDirection::DOWN);
				break;
			case 4:
				return WolfMovement(WolfState::WALKING, WolfDirection::LEFT);
				break;
			case 5:
				return WolfMovement(WolfState::STANDING, WolfDirection::LEFT);
				break;
			case 6:
				return WolfMovement(WolfState::WALKING, WolfDirection::LEFT);
				break;
			case 7:
				return WolfMovement(WolfState::WALKING, WolfDirection::UP);
				break;
			}
			

		}
	}



} //Namespace Enemy
