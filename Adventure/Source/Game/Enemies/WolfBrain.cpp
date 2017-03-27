#include "stdafx.h"
#include "Source/Game/Enemies/WolfBrain.hpp"

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
		switch (mMovementBehaviour)
		{
		case WolfMovementBehaviour::STATIC:
			return WolfMovement(WolfState::WALKING, WolfDirection::DOWN);

		}
	}



} //Namespace Enemy
