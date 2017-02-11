#ifndef WORLD_HPP
#define WORLD_HPP

#include "SFML\Graphics.hpp"

#include "Source\Tile\TileMap.hpp"
#include "Source\Tile\TileVertexArray.hpp"

#include "mySFMLVectorFunctions.hpp"



class World
{
private:
	TileMap mTileMap;
	TileVertexArray mTileVertexArray;


public:
	World();
	~World();

	void update(sf::Time const & frametime, sf::RenderWindow* renderWindow);
	void render(sf::RenderWindow* renderWindow);


};






#endif //WORLD_HPP

