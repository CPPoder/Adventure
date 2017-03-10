#include "stdafx.h"
#include "Source\Tile\TileType.hpp"


const std::array<sf::Vector2u, static_cast<unsigned int>(TileType::NUM_OF_TILE_TYPES)> TileTypePositions::mPositionsArray =
{
	sf::Vector2u(0u, 0u), //Void
	sf::Vector2u(1u, 0u), //Gras
	sf::Vector2u(1u, 2u), //Dirt
	sf::Vector2u(1u, 5u), //Water
	sf::Vector2u(0u, 0u), //Empty1
	sf::Vector2u(0u, 0u), //Empty2

	sf::Vector2u(0u, 1u), //Gras Dirt Transition 1
	sf::Vector2u(1u, 1u), //Gras Dirt Transition 2
	sf::Vector2u(2u, 1u), //Gras Dirt Transition 3
	sf::Vector2u(2u, 2u), //Gras Dirt Transition 4
	sf::Vector2u(2u, 3u), //Gras Dirt Transition 5
	sf::Vector2u(1u, 3u), //Gras Dirt Transition 6
	sf::Vector2u(0u, 3u), //Gras Dirt Transition 7
	sf::Vector2u(0u, 2u), //Gras Dirt Transition 8
	sf::Vector2u(3u, 1u), //Gras Dirt Transition 9
	sf::Vector2u(4u, 1u), //Gras Dirt Transition 10
	sf::Vector2u(4u, 2u), //Gras Dirt Transition 11
	sf::Vector2u(3u, 2u), //Gras Dirt Transition 12
	sf::Vector2u(2u, 0u), //Gras Dirt Transition 13
	sf::Vector2u(3u, 0u), //Gras Dirt Transition 14
	sf::Vector2u(4u, 0u), //Gras Dirt Transition 15
	sf::Vector2u(5u, 0u), //Gras Dirt Transition 16
	sf::Vector2u(5u, 1u), //Gras Dirt Transition 17
	sf::Vector2u(5u, 2u), //Gras Dirt Transition 18
	sf::Vector2u(3u, 3u), //Gras Dirt Transition 19
	sf::Vector2u(4u, 3u), //Gras Dirt Transition 20
	sf::Vector2u(5u, 3u), //Gras Dirt Transition 21
	sf::Vector2u(6u, 3u), //Gras Dirt Transition 22
	sf::Vector2u(3u, 4u), //Gras Dirt Transition 23
	sf::Vector2u(4u, 4u), //Gras Dirt Transition 24
	sf::Vector2u(5u, 4u), //Gras Dirt Transition 25
	sf::Vector2u(6u, 4u), //Gras Dirt Transition 26
	sf::Vector2u(6u, 0u), //Gras Dirt Transition 27
	sf::Vector2u(6u, 1u), //Gras Dirt Transition 28

	sf::Vector2u(0u, 4u), //Water Gras Transition 1
	sf::Vector2u(1u, 4u), //Water Gras Transition 2
	sf::Vector2u(2u, 4u), //Water Gras Transition 3
	sf::Vector2u(2u, 5u), //Water Gras Transition 4
	sf::Vector2u(2u, 6u), //Water Gras Transition 5
	sf::Vector2u(1u, 6u), //Water Gras Transition 6
	sf::Vector2u(0u, 6u), //Water Gras Transition 7
	sf::Vector2u(0u, 5u), //Water Gras Transition 8
	sf::Vector2u(4u, 5u), //Water Gras Transition 9
	sf::Vector2u(5u, 5u), //Water Gras Transition 10
	sf::Vector2u(5u, 6u), //Water Gras Transition 11
	sf::Vector2u(4u, 6u), //Water Gras Transition 12
	sf::Vector2u(0u, 7u), //Water Gras Transition 13
	sf::Vector2u(1u, 7u), //Water Gras Transition 14
	sf::Vector2u(2u, 7u), //Water Gras Transition 15
	sf::Vector2u(3u, 5u), //Water Gras Transition 16
	sf::Vector2u(3u, 6u), //Water Gras Transition 17
	sf::Vector2u(3u, 7u),  //Water Gras Transition 18

	sf::Vector2u(1u, 9u), //Bricked 1
	sf::Vector2u(0u, 8u), //Bricked 2
	sf::Vector2u(1u, 8u), //Bricked 3
	sf::Vector2u(2u, 8u), //Bricked 4
	sf::Vector2u(2u, 9u), //Bricked 5
	sf::Vector2u(2u, 10u), //Bricked 6
	sf::Vector2u(1u, 10u), //Bricked 7
	sf::Vector2u(0u, 10u), //Bricked 8
	sf::Vector2u(0u, 9u)  //Bricked 9
	
};


sf::Vector2u TileTypePositions::getPosition(TileType tileType)
{
	return mPositionsArray.at(static_cast<unsigned int>(tileType));
}

