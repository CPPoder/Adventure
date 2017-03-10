#include "stdafx.h"
#include "Source\Game\GameBases\World.hpp"
#include "Source\Framework\Framework.hpp"

World::World()
	: mTileMap("./Data/TileMaps/LittleMap.tm"),
	  mTileVertexArray(mTileMap),
	  mPlayer(sf::Vector2f(200.f, 200.f))
{
	mActualView = Framework::getRenderWindow()->getView();
	mActualView.zoom(0.5f);
	mWantedView = mActualView;

	SoundManager::playMusic(MusicName::THE_BEGINNING, 25.f);
}

World::~World()
{
}

void World::update(sf::Time const & frametime, sf::RenderWindow* renderWindow)
{
	//Update Player
	mPlayer.update(frametime, renderWindow, mTileMap);

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

	renderWindow->setView(originalView);
	renderWindow->draw(*mySFML::Class::RectShape(sf::Vector2f(), originalView.getSize(), mColorOfAmbientLayer, false).pointer);
}

