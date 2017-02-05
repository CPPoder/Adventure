#include "stdafx.h"
#include "Source\GameState\PlayingState.hpp"

namespace GameState
{
	
	PlayingState::PlayingState()
		: pWorld(new World)
	{

	}

	PlayingState::~PlayingState()
	{
		delete pWorld;
		pWorld = nullptr;
	}

	void PlayingState::update(sf::Time const & frametime, sf::RenderWindow* renderWindow)
	{
		pWorld->update(frametime, renderWindow);
	}

	void PlayingState::render(sf::RenderWindow* renderWindow)
	{
		pWorld->render(renderWindow);
	}

	GameStateChange PlayingState::getGameStateChange() const
	{
		return GameStateChange::NO_CHANGE;
	}
}

