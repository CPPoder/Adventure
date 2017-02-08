#include "stdafx.h"
#include "Source\Game\World.hpp"

World::World()
	: mTileMap("./Data/TileMaps/test.tm"),
	  mTileSquares(mTileMap)
{
}

World::~World()
{
}

void World::update(sf::Time const & frametime, sf::RenderWindow* renderWindow)
{

}

void World::render(sf::RenderWindow* renderWindow)
{
	mTileSquares.render(renderWindow);
}

