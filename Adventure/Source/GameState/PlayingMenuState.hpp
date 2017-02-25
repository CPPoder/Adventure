#ifndef PLAYINGMENUSTATE_HPP
#define PLAYINGMENUSTATE_HPP

#include "Source\GameState\GameState.hpp"
#include "Source\Game\GameBases\PlayingMenu.hpp"


namespace GameState
{

	class PlayingMenuState final : public GameState
	{
	private:
		PlayingMenu mPlayingMenu;

		bool mClosePlayingMenu = false;

	public:
		virtual ~PlayingMenuState() override;

		virtual void update(sf::Time const & frametime, sf::RenderWindow* renderWindow) override;
		virtual void render(sf::RenderWindow* renderWindow) override;
		virtual GameStateChange pollGameStateChange() override;
		virtual void reactOnESC() override;


	};



} //Namespace GameState



#endif //PLAYINGMENUSTATE_HPP

