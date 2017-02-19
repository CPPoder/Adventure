#include "stdafx.h"
#include "Source\Game\GameBases\MainMenu.hpp"



MainMenu::MainMenu()
	: mHeaderText(*mFonts.getFont(mySFML::Class::FontName::INFORMAL_ROMAN), sf::Vector2f(300.f, 100.f), "Adventure Game", 50, sf::Color::White),
	  mPlayButton(sf::Vector2f(300.f, 200.f), sf::Vector2f(150.f, 50.f), "Play", mySFML::Class::FontName::INFORMAL_ROMAN, 2.f, 36u),
	  mEditorButton(sf::Vector2f(300.f, 300.f), sf::Vector2f(150.f, 50.f), "Editor", mySFML::Class::FontName::INFORMAL_ROMAN, 2.f, 36u),
	  mExitButton(sf::Vector2f(300.f, 400.f), sf::Vector2f(150.f, 50.f), "Exit", mySFML::Class::FontName::INFORMAL_ROMAN, 2.f, 36u),
	  mOutgoingEvent(OutgoingEvent::NO_EVENT)
{
}

void MainMenu::render(sf::RenderWindow* renderWindow)
{
	renderWindow->draw(*mHeaderText.pointer);
	mPlayButton.render(renderWindow);
	mEditorButton.render(renderWindow);
	mExitButton.render(renderWindow);
}
void MainMenu::update(sf::Time const & frametime, sf::RenderWindow* renderWindow)
{
	mPlayButton.updateState(renderWindow);
	mEditorButton.updateState(renderWindow);
	mExitButton.updateState(renderWindow);
	
	if (mPlayButton.getMouseReleasedEventOccured())
	{
		mOutgoingEvent = OutgoingEvent::START_GAME;
	}
	if (mEditorButton.getMouseReleasedEventOccured())
	{
		mOutgoingEvent = OutgoingEvent::START_EDITOR;
	}
	if (mExitButton.getMouseReleasedEventOccured())
	{
		mOutgoingEvent = OutgoingEvent::EXIT;
	}
}

