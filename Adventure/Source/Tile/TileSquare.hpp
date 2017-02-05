#ifndef TILESQUARE_HPP
#define TILESQUARE_HPP

#include "SFML\Graphics.hpp"

#include "Source\Tile\TileMap.hpp"

#include "mySFMLVectorFunctions.hpp"


class TileSquare
{
private:
	mySFML::Class::RectShape mSquare;


public:
	TileSquare(sf::Vector2f const & position, TileType tileType);
	void setTileType(TileType tileType);
	void render(sf::RenderWindow* renderWindow);


private:
	static sf::IntRect getTextureRectForTileType(TileType tileType);


public:
	static constexpr unsigned int sSizeOfATile = 32;


private:
	static bool sInitialized;
	static sf::Texture* sTextureAtlasOfTiles;
	static void initialize();


};



#endif //TILESQUARE_HPP

