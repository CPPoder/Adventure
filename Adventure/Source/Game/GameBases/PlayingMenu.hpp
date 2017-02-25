#ifndef PLAYINGMENU_HPP
#define PLAYINGMENU_HPP


#include "mySFMLVectorFunctions.hpp"

#include "Source\ControlElements\Button.hpp"


class PlayingMenu
{
private:
	mySFML::Class::Fonts mFonts;

	mySFML::Class::Text mHeaderText;
	Button mContinueButton;
	Button mExitButton;

public:
	PlayingMenu();

	void render(sf::RenderWindow* renderWindow);
	void update(sf::Time const & frametime, sf::RenderWindow* renderWindow);

	enum class OutgoingEvent
	{
		NO_EVENT,
		CLOSE_PLAYING_MENU,
		EXIT_PLAYING_MODE
	} mOutgoingEvent = OutgoingEvent::NO_EVENT;

};



#endif //PLAYINGMENU_HPP

