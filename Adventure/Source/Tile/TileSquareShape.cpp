#include "stdafx.h"
#include "Source\Tile\TileSquareShape.hpp"


TileSquareShape::TileSquareShape(sf::Vector2f const & position, TileType tileType, float outlineThickness, sf::Color const & outlineColor, float scaleFactor)
	: mSquare(position, sf::Vector2f(static_cast<float>(TileMap::sSizeOfATile), static_cast<float>(TileMap::sSizeOfATile)), sf::Color::White, false, outlineThickness, outlineColor)
{
	mSquare.pointer->setTexture(TextureManager::getTexture(TextureManager::TextureName::TILE_TEXTURE_ATLAS));
	mSquare.pointer->setScale(scaleFactor, scaleFactor);
	this->setTileType(tileType);
}

void TileSquareShape::setTileType(TileType tileType)
{
	mSquare.pointer->setTextureRect(TileMap::getTextureRectForTileType(tileType));
}

sf::FloatRect TileSquareShape::getGlobalBounds() const
{
	return mSquare.pointer->getGlobalBounds();
}

void TileSquareShape::render(sf::RenderWindow* renderWindow)
{
	renderWindow->draw(*mSquare.pointer);
}

