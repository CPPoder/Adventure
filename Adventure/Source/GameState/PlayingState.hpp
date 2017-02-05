#ifndef PLAYINGSTATE_HPP
#define PLAYINGSTATE_HPP

#include "Source\GameState\GameState.hpp"
#include "Source\Game\World.hpp"


namespace GameState
{

	class PlayingState final : public GameState
	{
	private:
		World* pWorld;

	public:
		PlayingState();
		~PlayingState();

		virtual void update(sf::Time const & frametime, sf::RenderWindow* renderWindow) override;
		virtual void render(sf::RenderWindow* renderWindow) override;
		virtual GameStateChange getGameStateChange() const;


	};

}



#endif //PLAYINGSTATE_HPP

