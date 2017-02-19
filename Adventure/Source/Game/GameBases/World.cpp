#include "stdafx.h"
#include "Source\Game\GameBases\World.hpp"

World::World()
	: mTileMap("./Data/TileMaps/test.tm"),
	  mTileVertexArray(mTileMap),
	  mPlayer()
{
}

World::~World()
{
}

void World::update(sf::Time const & frametime, sf::RenderWindow* renderWindow)
{
	mPlayer.update(frametime, renderWindow);
}

void World::render(sf::RenderWindow* renderWindow)
{
	mTileVertexArray.render(renderWindow);
	mPlayer.render(renderWindow);
}

