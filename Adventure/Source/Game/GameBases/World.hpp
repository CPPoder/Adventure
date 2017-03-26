#ifndef WORLD_HPP
#define WORLD_HPP

#include "SFML\Graphics.hpp"

#include "Source\Tile\TileMap.hpp"
#include "Source\Tile\TileVertexArray.hpp"
#include "Source\Game\Player\Player.hpp"
#include "Source\Game\Magic\FireBall.hpp"

#include "Source\Game\Enemies\Wolf.hpp"

#include "Source\Framework\SoundManager.hpp"

#include "mySFMLVectorFunctions.hpp"



class World
{
private:
	TileMap mTileMap;
	TileVertexArray mTileVertexArray;
	sf::Sprite mSpriteOfWaterWaves;
	
	Player mPlayer;
	Enemy::Wolf mWolf;

	sf::View mActualView;
	sf::View mWantedView;

	std::list<Magic::FireBall*> mListOfFireBalls;

	sf::Color mColorOfAmbientLayer = sf::Color(10, 0, 25, 0);


public:
	World();
	~World();

	void update(sf::Time const & frametime, sf::RenderWindow* renderWindow);
	void render(sf::RenderWindow* renderWindow);


private:
	sf::IntRect calculateWaterWavesTextureRect() const;

};






#endif //WORLD_HPP

