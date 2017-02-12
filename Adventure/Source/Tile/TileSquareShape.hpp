#ifndef TILESQUARE_HPP
#define TILESQUARE_HPP

#include "SFML\Graphics.hpp"

#include "Source\Tile\TileMap.hpp"
#include "Source\Framework\TextureManager.hpp"

#include "mySFMLVectorFunctions.hpp"


class TileSquareShape
{
private:
	mySFML::Class::RectShape mSquare;


public:
	TileSquareShape(sf::Vector2f const & position, TileType tileType, float outlineThickness = 0.f, sf::Color const & outlineColor = sf::Color::Black, float scaleFactor = 1.f);
	void setTileType(TileType tileType);
	void render(sf::RenderWindow* renderWindow);

};



#endif //TILESQUARE_HPP

