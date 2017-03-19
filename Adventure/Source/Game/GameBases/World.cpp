#include "stdafx.h"
#include "Source\Game\GameBases\World.hpp"
#include "Source\Framework\Framework.hpp"

World::World()
	: mTileMap("./Data/TileMaps/Map.tm"),
	  mTileVertexArray(mTileMap),
	  mPlayer(sf::Vector2f(400.f, 200.f))
{
	mActualView = Framework::getRenderWindow()->getView();
	mActualView.zoom(0.5f);
	mWantedView = mActualView;

	SoundManager::playMusic(MusicName::THE_BEGINNING, 25.f);

	mListOfFireBalls.push_back(new Magic::FireBall(sf::Vector2f(100.f, 100.f), sf::Vector2f(250.f, 0.f), 1.f));
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
	//Update Player
	mPlayer.update(frametime, renderWindow, mTileMap);

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

	mTileVertexArray.render(renderWindow);
	mPlayer.render(renderWindow);
	for (auto& fireBall : mListOfFireBalls)
	{
		fireBall->render(renderWindow);
	}
	

	renderWindow->setView(originalView);
	renderWindow->draw(*mySFML::Class::RectShape(sf::Vector2f(), originalView.getSize(), mColorOfAmbientLayer, false).pointer);
}

