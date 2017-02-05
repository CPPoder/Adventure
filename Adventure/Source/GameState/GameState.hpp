#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "SFML\Graphics.hpp"


namespace GameState
{

	enum class GameStateChange
	{
		NO_CHANGE,

		PUSH_MAIN_MENU_STATE,
		PUSH_PLAYING_STATE,
		PUSH_EDITOR_STATE,

		REPLACE_MAIN_MENU_STATE,
		REPLACE_PLAYING_STATE,
		REPLACE_EDITOR_STATE,

		POP,


		NUM_OF_GAME_STATE_CHANGES
	};



	class GameState
	{
	public:
		virtual void update(sf::Time const & frametime, sf::RenderWindow* renderWindow) = 0;
		virtual void render(sf::RenderWindow* renderWindow) = 0;
		virtual GameStateChange getGameStateChange() const = 0;

	};

}



#endif //GAMESTATE_HPP

