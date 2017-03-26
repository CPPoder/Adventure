#include "stdafx.h"
#include "Source\Game\GameBases\World.hpp"
#include "Source\Framework\Framework.hpp"

World::World()
	: mTileMap("./Data/TileMaps/Map.tm"),
	  mTileVertexArray(mTileMap),
	  mSpriteOfWaterWaves(*TextureManager::getTexture(TextureManager::TextureName::WATER_WAVES_TEXTURE)),
	  mPlayer(sf::Vector2f(400.f, 500.f)),
	  mWolf(sf::Vector2f(500.f, 50.f))
{
	mSpriteOfWaterWaves.setPosition(sf::Vector2f());
	mSpriteOfWaterWaves.setTextureRect(this->calculateWaterWavesTextureRect());

	mActualView = Framework::getRenderWindow()->getView();
	mActualView.zoom(0.5f);
	mWantedView = mActualView;

	SoundManager::playMusic(MusicName::THE_BEGINNING, 25.f);
}

World::~World()
{
	for (auto fireBall : mListOfFireBalls)
	{
		delete fireBall;
	}
	mListOfFireBalls.clear();
}

void World::update(sf::Time const & frametime, sf::RenderWindow* renderWindow)
{
	//Update WaterWaves
	mSpriteOfWaterWaves.setTextureRect(this->calculateWaterWavesTextureRect());

	//Update Player
	mPlayer.update(frametime, renderWindow, mTileMap);

	//Update Wolf
	mWolf.update(frametime, renderWindow, mTileMap);

	//Update FireBalls
	std::list<Magic::FireBall*>& playersFireBallList = mPlayer.getAccessToListOfFireBalls();
	if (!playersFireBallList.empty())
	{
		mListOfFireBalls.insert(mListOfFireBalls.end(), playersFireBallList.begin(), playersFireBallList.end());
		playersFireBallList.clear();
	}
	
	for (auto& fireBall : mListOfFireBalls)
	{
		fireBall->update(frametime, renderWindow);
	}
	for (auto it = mListOfFireBalls.begin(); it != mListOfFireBalls.end(); )
	{
		if ((*it)->getDurationExceeded())
		{
			delete *it;
			it = mListOfFireBalls.erase(it);
		}
		else
		{
			++it;
		}
	}

	//Update Wanted View
	mWantedView.setCenter(mPlayer.getPosition());

	//Update Actual View
	float constexpr resistanceConstant = 1.0E-10f;
	float const resistanceFactor = pow(resistanceConstant, frametime.asSeconds());
	float const actualisationFactor = 1.f - resistanceFactor;
	sf::Vector2f newCenter = mWantedView.getCenter() * actualisationFactor + mActualView.getCenter() * resistanceFactor;
	sf::Vector2f newSize = mWantedView.getSize() * actualisationFactor + mActualView.getSize() * resistanceFactor;
	mActualView.setCenter(newCenter);
	mActualView.setSize(newSize);

}

void World::render(sf::RenderWindow* renderWindow)
{
	sf::View originalView = renderWindow->getView();
	renderWindow->setView(mActualView);

	renderWindow->draw(mSpriteOfWaterWaves);
	mTileVertexArray.render(renderWindow);
	mPlayer.render(renderWindow);
	mWolf.render(renderWindow);
	for (auto& fireBall : mListOfFireBalls)
	{
		fireBall->render(renderWindow);
	}
	

	renderWindow->setView(originalView);
	renderWindow->draw(*mySFML::Class::RectShape(sf::Vector2f(), originalView.getSize(), mColorOfAmbientLayer, false).pointer);
}





sf::IntRect World::calculateWaterWavesTextureRect() const
{
	unsigned int constexpr numberOfWaveStates = 32u;
	sf::Time const timeOfFullWaveCycle = sf::seconds(8.0f);
	static sf::Clock waveClock;
	static sf::Time timeSinceLastWaveStateChange(sf::Time::Zero);
	timeSinceLastWaveStateChange += waveClock.restart();
	static unsigned int actualWaveState(0u);
	bool waveStateHasChanged = false;
	if (timeSinceLastWaveStateChange >= timeOfFullWaveCycle / static_cast<float>(numberOfWaveStates))
	{
		timeSinceLastWaveStateChange -= timeOfFullWaveCycle / static_cast<float>(numberOfWaveStates);
		waveStateHasChanged = true;
		++actualWaveState;
		if (actualWaveState >= numberOfWaveStates)
		{
			actualWaveState = 0u;
		}
	}
	static bool firstCalculationOfWavesTextureRect(true);
	static sf::IntRect actualIntRect;
	if (waveStateHasChanged || firstCalculationOfWavesTextureRect)
	{
		firstCalculationOfWavesTextureRect = false;
		sf::Vector2u tileMapSize = mTileMap.getSize();
		actualIntRect = sf::IntRect(-static_cast<int>(actualWaveState), -static_cast<int>(actualWaveState), tileMapSize.x * TileMap::sSizeOfATile, tileMapSize.y * TileMap::sSizeOfATile);
	}
	return actualIntRect;
}
