#include "stdafx.h"
#include "Source\Game\Editor.hpp"

#include "Source\Framework\Framework.hpp"


Editor::Editor()
	: mTileMap("./Data/TileMaps/test.tm"),
	  mTileSquares(mTileMap),
	  mMenuScreenWidthRatio(0.3f),
	  rect(sf::Vector2f(0.f, 0.f), sf::Vector2f(700.f, 700.f), sf::Color::Green, false),
	  mTextField(sf::Vector2f(50.f, 100.f), sf::Vector2f(150.f, 50.f), "Te", mySFML::Class::FontName::INFORMAL_ROMAN, 2.f, 24u, true),
	  mMenuView(this->getInitialMenuView(Framework::getRenderWindow())),
	  mTilesView(this->getInitialTilesView(Framework::getRenderWindow()))
{
	
}

Editor::~Editor()
{
	mTileMap.saveToFile("./Data/TileMaps/out.tm");
}


void Editor::update(sf::Time const & frametime, sf::RenderWindow* renderWindow)
{
	//Change TilesView
	if (EventManager::checkForEvent(EventManager::EventType::MOUSE_WHEEL_SCROLLED))
	{
		//Determine zoomFactor
		float delta = EventManager::getMouseWheelScrolledInfo().delta;
		float constexpr zoomConstant = 500.f;
		float zoomFactor = pow((1 - 0.01f * delta), zoomConstant * frametime.asSeconds());
		
		//******************************************************************************************
		//Determine offset
		//Let f(x^\vec) = z * x^\vec + (1-z) * c^\vec
		//be the zoom map without correction, where z = zoomFactor, c^\vec = centerOfTilesViewport.
		//
		//Let further be g(x^\vec) = f(x^\vec) + \chi
		//the zoom map with correction, whicht satisfies the fixpoint condition: g(m^\vec) = m^\vec,
		//where m^\vec = mousePosRelToTilesViewport.
		//
		//Then \chi is determined to be: \chi = (z-1) * (c^\vec - m^\vec).
		//******************************************************************************************
		sf::FloatRect tilesViewport = mTilesView.getViewport();
		sf::Vector2f renderWindowSize = static_cast<sf::Vector2f>(renderWindow->getSize());
		float leftPosOfViewport = tilesViewport.left * renderWindowSize.x;
		sf::Vector2i mousePos = EventManager::getMouseWheelScrolledInfo().position; //Should be fixpoint
		sf::Vector2f mousePosRelToTilesViewport = static_cast<sf::Vector2f>(mousePos) - sf::Vector2f(leftPosOfViewport, 0.f);
		sf::Vector2f centerOfTilesViewport = sf::Vector2f(tilesViewport.width * renderWindowSize.x, tilesViewport.height * renderWindowSize.y) / 2.f;
		sf::Vector2f correction = (zoomFactor - 1) * (centerOfTilesViewport - mousePosRelToTilesViewport);
		float viewViewportQuotient = mTilesView.getSize().x / (tilesViewport.width * renderWindowSize.x); //Translates the correction from screenSpace into worldSpace
		
		mTilesView.zoom(zoomFactor);
		mTilesView.move(correction * viewViewportQuotient);
	}

	//Draw Tiles With Mouse
	bool leftMousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
	bool rightMousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Right);
	sf::Vector2f mouseCoords = renderWindow->mapPixelToCoords(sf::Mouse::getPosition(*renderWindow), mTilesView);
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
	mTextField.updateState(renderWindow, &mMenuView);
}

void Editor::render(sf::RenderWindow* renderWindow)
{
	//Memorize Initial View
	sf::View initialView = renderWindow->getView();

	//Render Menu Stuff
	renderWindow->setView(mMenuView);
	renderWindow->draw(*rect.pointer);
	mTextField.render(renderWindow);

	//Render Tile Stuff
	renderWindow->setView(mTilesView);
	mTileSquares.render(renderWindow);

	//Reset Initial View
	renderWindow->setView(initialView);
}



sf::View Editor::getInitialMenuView(sf::RenderWindow const * renderWindow) const
{
	sf::Vector2f windowSize = static_cast<sf::Vector2f>(renderWindow->getSize());
	sf::Vector2f menuSize = sf::Vector2f(windowSize.x * mMenuScreenWidthRatio, windowSize.y);

	sf::View view;
	view.reset(sf::FloatRect(0.f, 0.f, menuSize.x, menuSize.y));
	view.setViewport(sf::FloatRect(0.f, 0.f, mMenuScreenWidthRatio, 1.f));

	return view;
}

sf::View Editor::getInitialTilesView(sf::RenderWindow const * renderWindow) const
{
	sf::Vector2f windowSize = static_cast<sf::Vector2f>(renderWindow->getSize());
	sf::Vector2f squaresScreenSize = windowSize - sf::Vector2f(windowSize.x * mMenuScreenWidthRatio, 0.f);

	sf::View view;
	view.reset(sf::FloatRect(0.f, 0.f, squaresScreenSize.x, squaresScreenSize.y));
	view.setViewport(sf::FloatRect(mMenuScreenWidthRatio, 0.f, 1.f - mMenuScreenWidthRatio, 1.f));
	
	return view;
}

