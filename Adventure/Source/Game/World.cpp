#include "stdafx.h"
#include "Source\Game\World.hpp"

World::World()
{
	mTileMap.loadFromFile("./Data/TileMaps/test.tm");
	pTileSquares = new TileSquares(mTileMap);
}

World::~World()
{
	delete pTileSquares;
	pTileSquares = nullptr;
}

void World::update(sf::Time const & frametime, sf::RenderWindow* renderWindow)
{

}

void World::render(sf::RenderWindow* renderWindow)
{
	pTileSquares->render(renderWindow);
}

