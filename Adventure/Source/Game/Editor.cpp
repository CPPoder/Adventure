#include "stdafx.h"
#include "Source\Game\Editor.hpp"



Editor::Editor()
	: mTileMap("./Data/TileMaps/test.tm"),
	  mTileSquares(mTileMap),
	  mMenuScreenWidthRatio(0.3f),
	  rect(sf::Vector2f(0.f, 0.f), sf::Vector2f(700.f, 700.f), sf::Color::Green, false),
	  mTextField(sf::Vector2f(50.f, 100.f), sf::Vector2f(150.f, 50.f), "Test! Text!", mySFML::Class::FontName::INFORMAL_ROMAN, 2.f, 24u, true)
{
	
}

Editor::~Editor()
{
	mTileMap.saveToFile("./Data/TileMaps/out.tm");
}


void Editor::update(sf::Time const & frametime, sf::RenderWindow* renderWindow)
{
	//Draw Tiles
	bool leftMousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
	bool rightMousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Right);
	sf::Vector2f mouseCoords = renderWindow->mapPixelToCoords(sf::Mouse::getPosition(*renderWindow), this->getTilesView(renderWindow));
	bool changedTileMap = false;
	if (mouseCoords.x > 0.f && mouseCoords.y > 0.f)
	{
		sf::Vector2u squareNumber = static_cast<sf::Vector2u>(mouseCoords / static_cast<float>(TileSquare::sSizeOfATile));
		if (leftMousePressed && !rightMousePressed)
		{
			mTileMap.setAt(mLeftMouseTileType, squareNumber);
			changedTileMap = true;
		}
		if (!leftMousePressed && rightMousePressed)
		{
			mTileMap.setAt(mRightMouseTileType, squareNumber);
			changedTileMap = true;
		}
	}
	if (changedTileMap)
	{
		mTileSquares = TileSquares(mTileMap);
	}

	//TextField
	mTextField.updateState(renderWindow, &getMenuView(renderWindow));
}

void Editor::render(sf::RenderWindow* renderWindow)
{
	//Render Menu Stuff
	renderWindow->setView(this->getMenuView(renderWindow));
	renderWindow->draw(*rect.pointer);
	mTextField.render(renderWindow);

	//Render Tile Stuff
	renderWindow->setView(this->getTilesView(renderWindow));
	mTileSquares.render(renderWindow);
}



sf::View Editor::getMenuView(sf::RenderWindow* renderWindow)
{
	sf::Vector2f windowSize = static_cast<sf::Vector2f>(renderWindow->getSize());
	sf::Vector2f menuSize = sf::Vector2f(windowSize.x * mMenuScreenWidthRatio, windowSize.y);

	sf::View view;
	view.reset(sf::FloatRect(0.f, 0.f, menuSize.x, menuSize.y));
	view.setViewport(sf::FloatRect(0.f, 0.f, mMenuScreenWidthRatio, 1.f));

	return view;
}

sf::View Editor::getTilesView(sf::RenderWindow* renderWindow)
{
	sf::Vector2f windowSize = static_cast<sf::Vector2f>(renderWindow->getSize());
	sf::Vector2f squaresScreenSize = windowSize - sf::Vector2f(windowSize.x * mMenuScreenWidthRatio, 0.f);

	sf::View view;
	view.reset(sf::FloatRect(0.f, 0.f, squaresScreenSize.x, squaresScreenSize.y));
	view.setViewport(sf::FloatRect(mMenuScreenWidthRatio, 0.f, 1.f - mMenuScreenWidthRatio, 1.f));
	
	return view;
}

