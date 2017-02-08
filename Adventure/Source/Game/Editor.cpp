#include "stdafx.h"
#include "Source\Game\Editor.hpp"



Editor::Editor()
	: mTileMap("./Data/TileMaps/test.tm"),
	  mTileSquares(mTileMap)
{
	mTileMap.saveToFile("./Data/TileMaps/out.tm");
}


void Editor::update(sf::Time const & frametime, sf::RenderWindow* renderWindow)
{

}

void Editor::render(sf::RenderWindow* renderWindow)
{
	mTileSquares.render(renderWindow);
}

