#ifndef TILETYPE_HPP
#define TILETYPE_HPP

#include <array>

#include "SFML\Graphics.hpp"


enum class TileType
{
	VOID,
	GRAS,
	DIRT,
	WATER,
	BRICK,
	ICE,

	GRAS_DIRT_TRANSITION_1,
	GRAS_DIRT_TRANSITION_2,
	GRAS_DIRT_TRANSITION_3,
	GRAS_DIRT_TRANSITION_4,
	GRAS_DIRT_TRANSITION_5,
	GRAS_DIRT_TRANSITION_6,
	GRAS_DIRT_TRANSITION_7,
	GRAS_DIRT_TRANSITION_8,
	GRAS_DIRT_TRANSITION_9,
	GRAS_DIRT_TRANSITION_10,
	GRAS_DIRT_TRANSITION_11,
	GRAS_DIRT_TRANSITION_12,

	NUM_OF_TILE_TYPES
};

class TileTypePositions
{
private:
	static const std::array<sf::Vector2u, static_cast<unsigned int>(TileType::NUM_OF_TILE_TYPES)> mPositionsArray;

public:
	static sf::Vector2u getPosition(TileType tileType);

};



#endif //TILETYPE_HPP

