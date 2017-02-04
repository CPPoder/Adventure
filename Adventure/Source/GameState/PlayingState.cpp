#include "stdafx.h"
#include "Source\GameState\PlayingState.hpp"

namespace GameState
{

	void PlayingState::update(sf::Time const & frametime, sf::RenderWindow* renderWindow)
	{

	}

	void PlayingState::render(sf::RenderWindow* renderWindow)
	{

	}

	GameStateChange PlayingState::getGameStateChange() const
	{
		return GameStateChange::NO_CHANGE;
	}
}

