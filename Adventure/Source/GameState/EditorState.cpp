#include "stdafx.h"
#include "Source\GameState\EditorState.hpp"
#include "Source\Framework\Framework.hpp"

namespace GameState
{

	EditorState::EditorState()
		: mExitButton(sf::Vector2f(Framework::getRenderWindow()->getSize().x - mButtonSize.x, 0.f), mButtonSize, "X", mySFML::Class::FontName::ARIAL, -2.f, 12u)
	{

	}

	EditorState::~EditorState()
	{

	}

	void EditorState::update(sf::Time const & frametime, sf::RenderWindow* renderWindow)
	{
		mExitButton.updateState(renderWindow);
		if (mExitButton.getMouseReleasedEventOccured())
		{
			mCloseEditor = true;
		}

		if (!mCloseEditor)
		{
			mEditor.update(frametime, renderWindow);
		}
		
	}

	void EditorState::render(sf::RenderWindow* renderWindow)
	{
		mEditor.render(renderWindow);
		mExitButton.render(renderWindow);
	}

	GameStateChange EditorState::pollGameStateChange()
	{
		if (mCloseEditor)
		{
			return GameStateChange::REPLACE_MAIN_MENU_STATE;
		}
		else
		{
			return GameStateChange::NO_CHANGE;
		}
	}

	void EditorState::reactOnESC()
	{
		mCloseEditor = true;
	}


} //Namespace GameState

