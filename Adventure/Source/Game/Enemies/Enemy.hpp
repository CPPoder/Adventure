#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "SFML\Graphics.hpp"

#include "Source\Tile\TileMap.hpp"
#include "Source\Game\BattleSystem\StatusValues.hpp"


namespace Enemy
{

	class Enemy
	{
	protected:
		StatusValues mStatusValues;

	public:
		Enemy() = delete;
		Enemy(StatusValues const & statusValues);
		Enemy(Enemy const &) = default;
		Enemy& operator=(Enemy const &) = default;
		
		virtual ~Enemy();

		virtual void update(sf::Time const & frametime, sf::RenderWindow const * renderWindow, TileMap const & tileMap) = 0;
		virtual void render(sf::RenderWindow* renderWindow) = 0;

		virtual void moveObjects(sf::Vector2f const & movement) = 0;
		virtual void tryToMove(sf::Vector2f const & movement, TileMap const & tileMap) = 0;



	}; //Class Enemy



} //Namespace Enemy


#endif //ENEMY_HPP
