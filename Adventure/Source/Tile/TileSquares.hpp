#ifndef TILESQUARES_HPP
#define TILESQUARES_HPP

#include "SFML\Graphics.hpp"

#include "Source\Tile\TileMap.hpp"
#include "Source\Tile\TileSquare.hpp"

#include <vector>

#include "mySFMLVectorFunctions.hpp"


class TileSquares
{
private:
	std::vector<std::vector<TileSquare>> mMatrixOfTileSquares;

public:
	TileSquares(TileMap const & tileMap);

	void setTileMap(TileMap const & tileMap);

	void render(sf::RenderWindow* renderWindow);


};



#endif //TILESQUARES_HPP

