#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include "SFML\Graphics.hpp"

#include "Source\ControlElements\Button.hpp"

#include "mySFMLVectorFunctions.hpp"

class MainMenu
{
private:
	mySFML::Class::Fonts mFonts;

	mySFML::Class::Text mHeaderText;
	Button mPlayButton;
	Button mEditorButton;
	Button mExitButton;

public:
	MainMenu();

	void render(sf::RenderWindow* renderWindow);
	void update(sf::Time const & frametime, sf::RenderWindow* renderWindow);

	enum class OutgoingEvent
	{
		NO_EVENT,
		START_GAME,
		START_EDITOR,
		EXIT
	} mOutgoingEvent;

};



#endif //MAINMENU_HPP

