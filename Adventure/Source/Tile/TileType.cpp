#include "stdafx.h"
#include "Source\Tile\TileType.hpp"


const std::array<sf::Vector2u, static_cast<unsigned int>(TileType::NUM_OF_TILE_TYPES)> TileTypePositions::mPositionsArray =
{
	sf::Vector2u(0u, 0u), //Void
	sf::Vector2u(1u, 0u), //Gras
	sf::Vector2u(2u, 0u), //Dirt
	sf::Vector2u(3u, 0u), //Water
	sf::Vector2u(4u, 0u), //Brick
	sf::Vector2u(5u, 0u), //Ice
	sf::Vector2u(0u, 1u), //Gras Dirt Transition 1
	sf::Vector2u(1u, 1u), //Gras Dirt Transition 2
	sf::Vector2u(2u, 1u), //Gras Dirt Transition 3
	sf::Vector2u(3u, 1u), //Gras Dirt Transition 4
	sf::Vector2u(0u, 2u), //Gras Dirt Transition 5
	sf::Vector2u(1u, 2u), //Gras Dirt Transition 6
	sf::Vector2u(2u, 2u), //Gras Dirt Transition 7
	sf::Vector2u(3u, 2u), //Gras Dirt Transition 8
	sf::Vector2u(0u, 3u), //Gras Dirt Transition 9
	sf::Vector2u(1u, 3u), //Gras Dirt Transition 10
	sf::Vector2u(2u, 3u), //Gras Dirt Transition 11
	sf::Vector2u(3u, 3u) //Gras Dirt Transition 12
};


sf::Vector2u TileTypePositions::getPosition(TileType tileType)
{
	return mPositionsArray.at(static_cast<unsigned int>(tileType));
}

