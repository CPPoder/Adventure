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

	GameStateChange PlayingState::pollGameStateChange()
	{
		if (mOpenPlayingMenu)
		{
			mOpenPlayingMenu = false;
			return GameStateChange::PUSH_PLAYING_MENU_STATE;
		}
		else
		{
			return GameStateChange::NO_CHANGE;
		}
	}

	void PlayingState::reactOnESC()
	{
		mOpenPlayingMenu = true;
	}


} //Namespace PlayingState

