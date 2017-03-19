#include "stdafx.h"
#include "Source\Tile\TileType.hpp"


const std::array<sf::Vector2u, TileTypeProperties::sNumberOfTileTypes> TileTypeProperties::mPositionsArray =
{
	sf::Vector2u(0u, 0u), //Void

	sf::Vector2u(1u, 0u), //Grass

	sf::Vector2u(1u, 2u), //Dirt
	sf::Vector2u(0u, 1u), //Grass Dirt Transition 1
	sf::Vector2u(1u, 1u), //Grass Dirt Transition 2
	sf::Vector2u(2u, 1u), //Grass Dirt Transition 3
	sf::Vector2u(2u, 2u), //Grass Dirt Transition 4
	sf::Vector2u(2u, 3u), //Grass Dirt Transition 5
	sf::Vector2u(1u, 3u), //Grass Dirt Transition 6
	sf::Vector2u(0u, 3u), //Grass Dirt Transition 7
	sf::Vector2u(0u, 2u), //Grass Dirt Transition 8
	sf::Vector2u(3u, 1u), //Grass Dirt Transition 9
	sf::Vector2u(5u, 1u), //Grass Dirt Transition 10
	sf::Vector2u(5u, 3u), //Grass Dirt Transition 11
	sf::Vector2u(3u, 3u), //Grass Dirt Transition 12

	sf::Vector2u(1u, 5u), //Water
	sf::Vector2u(0u, 4u), //Water Grass Transition 1
	sf::Vector2u(1u, 4u), //Water Grass Transition 2
	sf::Vector2u(2u, 4u), //Water Grass Transition 3
	sf::Vector2u(2u, 5u), //Water Grass Transition 4
	sf::Vector2u(2u, 6u), //Water Grass Transition 5
	sf::Vector2u(1u, 6u), //Water Grass Transition 6
	sf::Vector2u(0u, 6u), //Water Grass Transition 7
	sf::Vector2u(0u, 5u), //Water Grass Transition 8
	sf::Vector2u(3u, 4u), //Water Grass Transition 9
	sf::Vector2u(5u, 4u), //Water Grass Transition 10
	sf::Vector2u(5u, 6u), //Water Grass Transition 11
	sf::Vector2u(3u, 6u), //Water Grass Transition 12

	sf::Vector2u(1u, 8u), //Bricked 1
	sf::Vector2u(0u, 7u), //Bricked 2
	sf::Vector2u(1u, 7u), //Bricked 3
	sf::Vector2u(2u, 7u), //Bricked 4
	sf::Vector2u(2u, 8u), //Bricked 5
	sf::Vector2u(2u, 9u), //Bricked 6
	sf::Vector2u(1u, 9u), //Bricked 7
	sf::Vector2u(0u, 9u), //Bricked 8
	sf::Vector2u(0u, 8u)  //Bricked 9
	
};

const std::array<TileTypeCategory, TileTypeProperties::sNumberOfTileTypes> TileTypeProperties::mCategoryArray =
{
	//Void
	TileTypeCategory::NONE,

	//Grass
	TileTypeCategory::GRASS,

	//Dirt
	TileTypeCategory::DIRT,
	TileTypeCategory::DIRT,
	TileTypeCategory::DIRT,
	TileTypeCategory::DIRT,
	TileTypeCategory::DIRT,
	TileTypeCategory::DIRT,
	TileTypeCategory::DIRT,
	TileTypeCategory::DIRT,
	TileTypeCategory::DIRT,
	TileTypeCategory::DIRT,
	TileTypeCategory::DIRT,
	TileTypeCategory::DIRT,
	TileTypeCategory::DIRT,

	//Water
	TileTypeCategory::WATER,
	TileTypeCategory::WATER,
	TileTypeCategory::WATER,
	TileTypeCategory::WATER,
	TileTypeCategory::WATER,
	TileTypeCategory::WATER,
	TileTypeCategory::WATER,
	TileTypeCategory::WATER,
	TileTypeCategory::WATER,
	TileTypeCategory::WATER,
	TileTypeCategory::WATER,
	TileTypeCategory::WATER,
	TileTypeCategory::WATER,

	//Bricked
	TileTypeCategory::BRICKED,
	TileTypeCategory::BRICKED,
	TileTypeCategory::BRICKED,
	TileTypeCategory::BRICKED,
	TileTypeCategory::BRICKED,
	TileTypeCategory::BRICKED,
	TileTypeCategory::BRICKED,
	TileTypeCategory::BRICKED,
	TileTypeCategory::BRICKED,
};


sf::Vector2u TileTypeProperties::getPosition(TileType tileType)
{
	return mPositionsArray.at(tileType);
}

TileTypeCategory TileTypeProperties::getCategory(TileType tileType)
{
	return mCategoryArray.at(tileType);
}

