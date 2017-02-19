#include "stdafx.h"
#include "Source\Framework\TextureManager.hpp"



void TextureManager::Init()
{
	sf::Texture* tileTextureAtlas = new sf::Texture;
	tileTextureAtlas->loadFromFile("./Data/Textures/TextureAtlas_Tile.png");
	mMapOfTextures.insert(std::make_pair(TextureManager::TextureName::TILE_TEXTURE_ATLAS, tileTextureAtlas));

	sf::Texture* playerTextureAtlas = new sf::Texture;
	playerTextureAtlas->loadFromFile("./Data/Textures/TestPlayer.png");
	mMapOfTextures.insert(std::make_pair(TextureManager::TextureName::PLAYER_TEXTURE_ATLAS, playerTextureAtlas));
}

sf::Texture const * TextureManager::getTexture(TextureName textureName)
{
	return mMapOfTextures.at(textureName);
}
sf::Texture * TextureManager::getTextureChangeable(TextureName textureName)
{
	return mMapOfTextures.at(textureName);
}







std::map<TextureManager::TextureName, sf::Texture*> TextureManager::mMapOfTextures = std::map<TextureManager::TextureName, sf::Texture*>();

