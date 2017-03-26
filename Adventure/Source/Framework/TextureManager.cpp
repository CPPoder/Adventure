#include "stdafx.h"
#include "Source\Framework\TextureManager.hpp"



void TextureManager::Init()
{
	sf::Texture* checkBoxTextureAtlas = new sf::Texture;
	checkBoxTextureAtlas->loadFromFile("./Data/Textures/CheckBox.png");
	mMapOfTextures.insert(std::make_pair(TextureManager::TextureName::CHECK_BOX_TEXTURE_ATLAS, checkBoxTextureAtlas));

	sf::Texture* tileTextureAtlas = new sf::Texture;
	tileTextureAtlas->loadFromFile("./Data/Textures/TextureAtlas_Tile.png");
	mMapOfTextures.insert(std::make_pair(TextureManager::TextureName::TILE_TEXTURE_ATLAS, tileTextureAtlas));

	sf::Texture* playerTextureAtlas = new sf::Texture;
	playerTextureAtlas->loadFromFile("./Data/Textures/Player_T.png");
	mMapOfTextures.insert(std::make_pair(TextureManager::TextureName::PLAYER_TEXTURE_ATLAS, playerTextureAtlas));

	sf::Texture* wolfTextureAtlas = new sf::Texture;
	wolfTextureAtlas->loadFromFile("./Data/Textures/Wolf.png");
	mMapOfTextures.insert(std::make_pair(TextureManager::TextureName::WOLF_TEXTURE_ATLAS, wolfTextureAtlas));

	sf::Texture* waterWavesTexture = new sf::Texture;
	waterWavesTexture->loadFromFile("./Data/Textures/WaterWaves.png");
	waterWavesTexture->setRepeated(true);
	mMapOfTextures.insert(std::make_pair(TextureManager::TextureName::WATER_WAVES_TEXTURE, waterWavesTexture));
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

