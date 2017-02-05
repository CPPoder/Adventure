#include "stdafx.h"
#include "Source\GameState\EditorState.hpp"

namespace GameState
{

	EditorState::EditorState()
	{

	}

	EditorState::~EditorState()
	{

	}

	void EditorState::update(sf::Time const & frametime, sf::RenderWindow* renderWindow)
	{

	}

	void EditorState::render(sf::RenderWindow* renderWindow)
	{

	}

	GameStateChange EditorState::getGameStateChange() const
	{
		return GameStateChange::NO_CHANGE;
	}
}

