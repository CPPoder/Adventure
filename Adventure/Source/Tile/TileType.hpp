#ifndef TILETYPE_HPP
#define TILETYPE_HPP

#include <array>

#include "SFML\Graphics.hpp"


typedef unsigned int TileType;

enum class TileTypeCategory
{
	NONE,

	GRASS,
	DIRT,
	WATER,
	BRICKED,


	NUM_OF_CATEGORIES
};

class TileTypeProperties
{
public:
	static constexpr unsigned int sNumberOfTileTypes = 37u;

private:
	static const std::array<sf::Vector2u, sNumberOfTileTypes> mPositionsArray;
	static const std::array<TileTypeCategory, sNumberOfTileTypes> mCategoryArray;

public:
	static sf::Vector2u getPosition(TileType tileType);
	static TileTypeCategory getCategory(TileType tileType);

};



#endif //TILETYPE_HPP

