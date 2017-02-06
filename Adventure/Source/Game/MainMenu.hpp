#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include "SFML\Graphics.hpp"

#include "Source\ControlElements\Button.hpp"

#include "mySFMLVectorFunctions.hpp"


class MainMenu
{
private:
	Button mButton;

public:
	MainMenu();

	void render(sf::RenderWindow* renderWindow);
	void update(sf::Time const & frametime, sf::RenderWindow* renderWindow);


};



#endif //MAINMENU_HPP

