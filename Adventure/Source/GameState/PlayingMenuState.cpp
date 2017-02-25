#include "stdafx.h"
#include "Source\GameState\PlayingMenuState.hpp"

namespace GameState
{

	PlayingMenuState::~PlayingMenuState()
	{

	}

	void PlayingMenuState::update(sf::Time const & frametime, sf::RenderWindow* renderWindow)
	{
		mPlayingMenu.update(frametime, renderWindow);
	}

	void PlayingMenuState::render(sf::RenderWindow* renderWindow)
	{
		mPlayingMenu.render(renderWindow);
	}

	GameStateChange PlayingMenuState::pollGameStateChange()
	{
		if (!mClosePlayingMenu)
		{
			switch (mPlayingMenu.mOutgoingEvent)
			{
			case PlayingMenu::OutgoingEvent::NO_EVENT:
				return GameStateChange::NO_CHANGE;
				break;
			case PlayingMenu::OutgoingEvent::CLOSE_PLAYING_MENU:
				return GameStateChange::POP;
				break;
			case PlayingMenu::OutgoingEvent::EXIT_PLAYING_MODE:
				return GameStateChange::POP_TWICE_AND_PUSH_MAIN_MENU_STATE;
				break;
			}
		}
		else
		{
			return GameStateChange::POP;
		}
	}

	void PlayingMenuState::reactOnESC()
	{
		mClosePlayingMenu = true;
	}


} //Namespace GameState

