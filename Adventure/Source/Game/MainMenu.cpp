#include "stdafx.h"
#include "Source\Game\MainMenu.hpp"



MainMenu::MainMenu()
	: mButton(sf::Vector2f(200.f, 200.f), sf::Vector2f(150.f, 50.f), "Test Text!", mySFML::Class::FontName::INFORMAL_ROMAN, 2.f, 36u)
{

}

void MainMenu::render(sf::RenderWindow* renderWindow)
{
	mButton.render(renderWindow);
}
void MainMenu::update(sf::Time const & frametime, sf::RenderWindow* renderWindow)
{
	static unsigned int i = 0;
	mButton.updateState(renderWindow);
	if (mButton.getMouseReleasedEventOccured())
	{

		std::cout << "Yeah!" << i++ << std::endl;
	}
}

