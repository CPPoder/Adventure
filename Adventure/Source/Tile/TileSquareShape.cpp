#include "stdafx.h"
#include "Source\Tile\TileSquareShape.hpp"


TileSquareShape::TileSquareShape(sf::Vector2f const & position, TileType tileType, float outlineThickness, sf::Color const & outlineColor)
	: mSquare(position, sf::Vector2f(TileMap::sSizeOfATile, TileMap::sSizeOfATile), sf::Color::White, false, outlineThickness, outlineColor)
{
	mSquare.pointer->setTexture(TextureManager::getTexture(TextureManager::TextureName::TILE_TEXTURE_ATLAS));
	this->setTileType(tileType);
}

void TileSquareShape::setTileType(TileType tileType)
{
	mSquare.pointer->setTextureRect(TileMap::getTextureRectForTileType(tileType));
}

void TileSquareShape::render(sf::RenderWindow* renderWindow)
{
	renderWindow->draw(*mSquare.pointer);
}

