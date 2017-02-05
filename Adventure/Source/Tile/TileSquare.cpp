#include "stdafx.h"
#include "Source\Tile\TileSquare.hpp"


TileSquare::TileSquare(sf::Vector2f const & position, TileType tileType)
	: mSquare(position, sf::Vector2f(sSizeOfATile, sSizeOfATile), sf::Color::White, false)
{
	if (!sInitialized)
	{
		initialize();
	}
	mSquare.pointer->setTexture(sTextureAtlasOfTiles);
	mSquare.pointer->setTextureRect(getTextureRectForTileType(tileType));
}

void TileSquare::setTileType(TileType tileType)
{
	mSquare.pointer->setTextureRect(getTextureRectForTileType(tileType));
}

void TileSquare::render(sf::RenderWindow* renderWindow)
{
	renderWindow->draw(*mSquare.pointer);
}



sf::IntRect TileSquare::getTextureRectForTileType(TileType tileType)
{
	return sf::IntRect(static_cast<int>(tileType) * sSizeOfATile, 0, sSizeOfATile, sSizeOfATile);
}



bool TileSquare::sInitialized = false;
sf::Texture* TileSquare::sTextureAtlasOfTiles = nullptr;

void TileSquare::initialize()
{
	sInitialized = false;
	sTextureAtlasOfTiles = new sf::Texture;
	sTextureAtlasOfTiles->loadFromFile("./Data/Textures/TextureAtlas_Tile.png");
}

