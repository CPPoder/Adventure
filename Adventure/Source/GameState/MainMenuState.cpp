#include "stdafx.h"
#include "Source\GameState\MainMenuState.hpp"

namespace GameState
{

	void MainMenuState::update(sf::Time const & frametime, sf::RenderWindow* renderWindow)
	{
		mMainMenu.update(frametime, renderWindow);
	}

	void MainMenuState::render(sf::RenderWindow* renderWindow)
	{
		mMainMenu.render(renderWindow);
	}

	GameStateChange MainMenuState::getGameStateChange() const
	{
		//return GameStateChange::PUSH_PLAYING_STATE;
		return GameStateChange::NO_CHANGE;
	}

}

