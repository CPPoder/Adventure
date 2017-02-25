#include "stdafx.h"
#include "Source\Game\GameBases\PlayingMenu.hpp"


PlayingMenu::PlayingMenu()
	: mHeaderText(*mFonts.getFont(mySFML::Class::FontName::INFORMAL_ROMAN), sf::Vector2f(300.f, 100.f), "Menu", 50, sf::Color::White),
	  mContinueButton(sf::Vector2f(300.f, 200.f), sf::Vector2f(150.f, 50.f), "Continue", mySFML::Class::FontName::INFORMAL_ROMAN, 2.f, 36u),
	  mExitButton(sf::Vector2f(300.f, 300.f), sf::Vector2f(150.f, 50.f), "Exit", mySFML::Class::FontName::INFORMAL_ROMAN, 2.f, 36u)
{
}

void PlayingMenu::render(sf::RenderWindow* renderWindow)
{
	renderWindow->draw(*mHeaderText.pointer);
	mContinueButton.render(renderWindow);
	mExitButton.render(renderWindow);
}
void PlayingMenu::update(sf::Time const & frametime, sf::RenderWindow* renderWindow)
{
	mContinueButton.updateState(renderWindow);
	mExitButton.updateState(renderWindow);

	if (mContinueButton.getMouseReleasedEventOccured())
	{
		mOutgoingEvent = OutgoingEvent::CLOSE_PLAYING_MENU;
	}
	if (mExitButton.getMouseReleasedEventOccured())
	{
		mOutgoingEvent = OutgoingEvent::EXIT_PLAYING_MODE;
	}
}

