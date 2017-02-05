#include "stdafx.h"
#include "Source\Tile\TileSquares.hpp"


TileSquares::TileSquares(TileMap const & tileMap)
{
	this->setTileMap(tileMap);
}


void TileSquares::setTileMap(TileMap const & tileMap)
{
	mMatrixOfTileSquares.clear();
	unsigned int ySizeOfTileMap = tileMap.getYSize();
	mMatrixOfTileSquares.reserve(ySizeOfTileMap);
	for (unsigned int y = 0; y < ySizeOfTileMap; ++y)
	{
		unsigned int xSize = tileMap.getXSizeAt(y);
		std::vector<TileSquare> vectorOfTileSquares;
		vectorOfTileSquares.reserve(xSize);
		for (unsigned int x = 0; x < xSize; ++x)
		{
			vectorOfTileSquares.push_back(TileSquare(static_cast<sf::Vector2f>(sf::Vector2u(x, y)) * static_cast<float>(TileSquare::sSizeOfATile), tileMap.at(x, y).tileType));
		}
		mMatrixOfTileSquares.push_back(vectorOfTileSquares);
	}
}


void TileSquares::render(sf::RenderWindow* renderWindow)
{
	for (auto vec : mMatrixOfTileSquares)
	{
		for (auto tileSquare : vec)
		{
			tileSquare.render(renderWindow);
		}
	}
}


