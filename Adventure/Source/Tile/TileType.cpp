#include "stdafx.h"
#include "Source\Tile\TileType.hpp"


const std::array<sf::Vector2u, static_cast<unsigned int>(TileType::NUM_OF_TILE_TYPES)> TileTypeProperties::mPositionsArray =
{
	sf::Vector2u(0u, 0u), //Void
	sf::Vector2u(1u, 0u), //Grass
	sf::Vector2u(1u, 2u), //Dirt
	sf::Vector2u(1u, 5u), //Water
	sf::Vector2u(0u, 0u), //Empty1
	sf::Vector2u(0u, 0u), //Empty2

	sf::Vector2u(0u, 1u), //Grass Dirt Transition 1
	sf::Vector2u(1u, 1u), //Grass Dirt Transition 2
	sf::Vector2u(2u, 1u), //Grass Dirt Transition 3
	sf::Vector2u(2u, 2u), //Grass Dirt Transition 4
	sf::Vector2u(2u, 3u), //Grass Dirt Transition 5
	sf::Vector2u(1u, 3u), //Grass Dirt Transition 6
	sf::Vector2u(0u, 3u), //Grass Dirt Transition 7
	sf::Vector2u(0u, 2u), //Grass Dirt Transition 8
	sf::Vector2u(3u, 1u), //Grass Dirt Transition 9
	sf::Vector2u(4u, 1u), //Grass Dirt Transition 10
	sf::Vector2u(4u, 2u), //Grass Dirt Transition 11
	sf::Vector2u(3u, 2u), //Grass Dirt Transition 12
	sf::Vector2u(2u, 0u), //Grass Dirt Transition 13
	sf::Vector2u(3u, 0u), //Grass Dirt Transition 14
	sf::Vector2u(4u, 0u), //Grass Dirt Transition 15
	sf::Vector2u(5u, 0u), //Grass Dirt Transition 16
	sf::Vector2u(5u, 1u), //Grass Dirt Transition 17
	sf::Vector2u(5u, 2u), //Grass Dirt Transition 18
	sf::Vector2u(3u, 3u), //Grass Dirt Transition 19
	sf::Vector2u(4u, 3u), //Grass Dirt Transition 20
	sf::Vector2u(5u, 3u), //Grass Dirt Transition 21
	sf::Vector2u(6u, 3u), //Grass Dirt Transition 22
	sf::Vector2u(3u, 4u), //Grass Dirt Transition 23
	sf::Vector2u(4u, 4u), //Grass Dirt Transition 24
	sf::Vector2u(5u, 4u), //Grass Dirt Transition 25
	sf::Vector2u(6u, 4u), //Grass Dirt Transition 26
	sf::Vector2u(6u, 0u), //Grass Dirt Transition 27
	sf::Vector2u(6u, 1u), //Grass Dirt Transition 28

	sf::Vector2u(0u, 4u), //Water Grass Transition 1
	sf::Vector2u(1u, 4u), //Water Grass Transition 2
	sf::Vector2u(2u, 4u), //Water Grass Transition 3
	sf::Vector2u(2u, 5u), //Water Grass Transition 4
	sf::Vector2u(2u, 6u), //Water Grass Transition 5
	sf::Vector2u(1u, 6u), //Water Grass Transition 6
	sf::Vector2u(0u, 6u), //Water Grass Transition 7
	sf::Vector2u(0u, 5u), //Water Grass Transition 8
	sf::Vector2u(4u, 5u), //Water Grass Transition 9
	sf::Vector2u(5u, 5u), //Water Grass Transition 10
	sf::Vector2u(5u, 6u), //Water Grass Transition 11
	sf::Vector2u(4u, 6u), //Water Grass Transition 12
	sf::Vector2u(0u, 7u), //Water Grass Transition 13
	sf::Vector2u(1u, 7u), //Water Grass Transition 14
	sf::Vector2u(2u, 7u), //Water Grass Transition 15
	sf::Vector2u(3u, 5u), //Water Grass Transition 16
	sf::Vector2u(3u, 6u), //Water Grass Transition 17
	sf::Vector2u(3u, 7u), //Water Grass Transition 18

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

const std::array<TileTypeCategory, static_cast<unsigned int>(TileType::NUM_OF_TILE_TYPES)> TileTypeProperties::mCategoryArray = 
{
	TileTypeCategory::NONE, //Void
	TileTypeCategory::GRASS, //Grass
	TileTypeCategory::DIRT, //Dirt
	TileTypeCategory::WATER, //Water
	TileTypeCategory::NONE, //Empty1
	TileTypeCategory::NONE, //Empty2

	TileTypeCategory::DIRT, //Grass Dirt Transition 1
	TileTypeCategory::DIRT, //Grass Dirt Transition 2
	TileTypeCategory::DIRT, //Grass Dirt Transition 3
	TileTypeCategory::DIRT, //Grass Dirt Transition 4
	TileTypeCategory::DIRT, //Grass Dirt Transition 5
	TileTypeCategory::DIRT, //Grass Dirt Transition 6
	TileTypeCategory::DIRT, //Grass Dirt Transition 7
	TileTypeCategory::DIRT, //Grass Dirt Transition 8
	TileTypeCategory::DIRT, //Grass Dirt Transition 9
	TileTypeCategory::DIRT, //Grass Dirt Transition 10
	TileTypeCategory::DIRT, //Grass Dirt Transition 11
	TileTypeCategory::DIRT, //Grass Dirt Transition 12
	TileTypeCategory::DIRT, //Grass Dirt Transition 13
	TileTypeCategory::DIRT, //Grass Dirt Transition 14
	TileTypeCategory::DIRT, //Grass Dirt Transition 15
	TileTypeCategory::DIRT, //Grass Dirt Transition 16
	TileTypeCategory::DIRT, //Grass Dirt Transition 17
	TileTypeCategory::DIRT, //Grass Dirt Transition 18
	TileTypeCategory::DIRT, //Grass Dirt Transition 19
	TileTypeCategory::DIRT, //Grass Dirt Transition 20
	TileTypeCategory::DIRT, //Grass Dirt Transition 21
	TileTypeCategory::DIRT, //Grass Dirt Transition 22
	TileTypeCategory::DIRT, //Grass Dirt Transition 23
	TileTypeCategory::DIRT, //Grass Dirt Transition 24
	TileTypeCategory::DIRT, //Grass Dirt Transition 25
	TileTypeCategory::DIRT, //Grass Dirt Transition 26
	TileTypeCategory::DIRT, //Grass Dirt Transition 27
	TileTypeCategory::DIRT, //Grass Dirt Transition 28

	TileTypeCategory::WATER, //Water Grass Transition 1
	TileTypeCategory::WATER, //Water Grass Transition 2
	TileTypeCategory::WATER, //Water Grass Transition 3
	TileTypeCategory::WATER, //Water Grass Transition 4
	TileTypeCategory::WATER, //Water Grass Transition 5
	TileTypeCategory::WATER, //Water Grass Transition 6
	TileTypeCategory::WATER, //Water Grass Transition 7
	TileTypeCategory::WATER, //Water Grass Transition 8
	TileTypeCategory::WATER, //Water Grass Transition 9
	TileTypeCategory::WATER, //Water Grass Transition 10
	TileTypeCategory::WATER, //Water Grass Transition 11
	TileTypeCategory::WATER, //Water Grass Transition 12
	TileTypeCategory::WATER, //Water Grass Transition 13
	TileTypeCategory::WATER, //Water Grass Transition 14
	TileTypeCategory::WATER, //Water Grass Transition 15
	TileTypeCategory::WATER, //Water Grass Transition 16
	TileTypeCategory::WATER, //Water Grass Transition 17
	TileTypeCategory::WATER, //Water Grass Transition 18

	TileTypeCategory::BRICKED, //Bricked 1
	TileTypeCategory::BRICKED, //Bricked 2
	TileTypeCategory::BRICKED, //Bricked 3
	TileTypeCategory::BRICKED, //Bricked 4
	TileTypeCategory::BRICKED, //Bricked 5
	TileTypeCategory::BRICKED, //Bricked 6
	TileTypeCategory::BRICKED, //Bricked 7
	TileTypeCategory::BRICKED, //Bricked 8
	TileTypeCategory::BRICKED  //Bricked 9
};


sf::Vector2u TileTypeProperties::getPosition(TileType tileType)
{
	return mPositionsArray.at(static_cast<unsigned int>(tileType));
}

TileTypeCategory TileTypeProperties::getCategory(TileType tileType)
{
	return mCategoryArray.at(static_cast<unsigned int>(tileType));
}

