#include "stdafx.h"
#include "Source\Game\GameBases\Editor.hpp"

#include "Source\Framework\Framework.hpp"


Editor::Editor()
	: mMenuView(this->getInitialMenuView(Framework::getRenderWindow())),
	  mTilesView(this->getInitialTilesView(Framework::getRenderWindow())),
	  mTileMap(),
	  mTileVertexArray(mTileMap),
	  mBorderVertexArray(mTileMap),
	  mBorderOfActualBorderDrawing(sf::Vector2i(), sf::Vector2i(), Border::Type::INSURMOUNTABLE),
	  mBorderVertexArrayOfActualBorderDrawing(mBorderOfActualBorderDrawing),
	  mMenuBackgroundRectangle(sf::Vector2f(0.f, 0.f), mMenuView.getSize(), sf::Color(70, 40, 10), false, -3.f, sf::Color(50, 30, 5)),
	  mLoadTextField(mPosOfFirstLoadSaveTextField,										mSizeOfLoadSaveTextFields, "./Data/TileMaps/", mySFML::Class::FontName::ARIAL, 2.f, mCharacterSizeOfTextFields, true, InputBehaviour::BOUNDED_FROM_BELOW, 16u),
	  mSaveTextField(mPosOfFirstLoadSaveTextField + mRelDistBetweenLoadSaveTextFilds,	mSizeOfLoadSaveTextFields, "./Data/TileMaps/", mySFML::Class::FontName::ARIAL, 2.f, mCharacterSizeOfTextFields, true, InputBehaviour::BOUNDED_FROM_BELOW, 16u),
	  mLoadButton(mPosOfFirstLoadSaveTextField + sf::Vector2f(mSizeOfLoadSaveTextFields.x, 0.f) + mDistBetweenTextFieldAndButton,										mSizeOfLoadSaveButtons, "Load", mySFML::Class::FontName::ARIAL, 2.f, mCharacterSizeOfButtons),
	  mSaveButton(mPosOfFirstLoadSaveTextField + mRelDistBetweenLoadSaveTextFilds + sf::Vector2f(mSizeOfLoadSaveTextFields.x, 0.f) + mDistBetweenTextFieldAndButton,	mSizeOfLoadSaveButtons, "Save", mySFML::Class::FontName::ARIAL, 2.f, mCharacterSizeOfButtons),
	  mTileSquareShapeOfLeftMouseTileType(mPosOfLeftMouseTileTypeSquare, mLeftMouseTileType, 2.f),
	  mTileSquareShapeOfRightMouseTileType(mPosOfLeftMouseTileTypeSquare + mRelDistBetweenTileTypeSquares, mRightMouseTileType, 2.f),
	  mRectShapeOfSelectionArea(mPosOfSelectionArea, static_cast<sf::Vector2f>(mSizeOfSelectionArea * TileMap::sSizeOfATile), sf::Color::White, false, 2.f),
	  mDropDownMenu(mPosOfDropDownMenu, mSizeOfSingleDropDownMenuField, mSizeOfDropMenu, mVectorOfTileTypeCategoryNamesInDropDownMenu, mySFML::Class::FontName::ARIAL),
	  mBorderDrawingModeCheckBox(mPosOfBorderDrawingModeCheckBox, true, false, false),
	  mBorderDrawingModeText(*mFonts.getFont(mySFML::Class::FontName::ARIAL), mPosOfBorderDrawingModeCheckBox + mRelDistOfBorderDrawingMoveText, "Border Drawing Mode", 14u),
	  mVertexArrayOfSelectionAreaGrid(sf::PrimitiveType::Lines),
	  mVertexArrayOfLastSelection(sf::PrimitiveType::LineStrip)
{
	this->handleDropDownMenuTileTypeCategoryChange();
	this->constructSelectionAreaGrid();
}

Editor::~Editor()
{
}


void Editor::update(sf::Time const & frametime, sf::RenderWindow* renderWindow)
{
	/*
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::N))
	{
		int i = 0;
		++i;
	}
	*/

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
		if (!mDropDownMenu.checkIsMouseOverDropMenu(static_cast<sf::Vector2f>(mousePos)))
		{
			sf::Vector2f mousePosRelToTilesViewport = static_cast<sf::Vector2f>(mousePos) - sf::Vector2f(leftPosOfViewport, 0.f);
			sf::Vector2f centerOfTilesViewport = sf::Vector2f(tilesViewport.width * renderWindowSize.x, tilesViewport.height * renderWindowSize.y) / 2.f;
			sf::Vector2f correction = (zoomFactor - 1) * (centerOfTilesViewport - mousePosRelToTilesViewport);
			float viewViewportQuotient = mTilesView.getSize().x / (tilesViewport.width * renderWindowSize.x); //Translates the correction from screenSpace into worldSpace

			mTilesView.zoom(zoomFactor);
			mTilesView.move(correction * viewViewportQuotient);
		}
	}
	if (EventManager::checkForEvent(EventManager::EventType::MOUSE_DRAGGED))
	{
		EventManager::MouseDraggedInfo draggedInfo = EventManager::getMouseDraggedInfo();
		if (draggedInfo.button == sf::Mouse::Button::Middle)
		{
			sf::Vector2f draggedDistance = renderWindow->mapPixelToCoords(draggedInfo.newPosition, mTilesView) - renderWindow->mapPixelToCoords(draggedInfo.oldPosition, mTilesView);
			mTilesView.move(-draggedDistance);
		}
	}

	//Draw Tiles With Mouse
	if (!mDrawBordersInsteadOfTiles)
	{
		sf::Vector2i mousePixelPos = sf::Mouse::getPosition(*renderWindow);
		sf::FloatRect rectOfTillesView = sf::FloatRect(renderWindow->getSize().x * mMenuScreenWidthRatio, 0.f, renderWindow->getSize().x * (1.f - mMenuScreenWidthRatio), static_cast<float>(renderWindow->getSize().y));
		bool mouseIsInTilesViewport = rectOfTillesView.contains(static_cast<sf::Vector2f>(mousePixelPos));
		bool leftMousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
		bool rightMousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Right);
		sf::Vector2f mouseCoords = renderWindow->mapPixelToCoords(sf::Mouse::getPosition(*renderWindow), mTilesView);
		bool changedTileMap = false;
		if (mouseCoords.x > 0.f && mouseCoords.y > 0.f && mouseIsInTilesViewport)
		{
			sf::Vector2u squareNumber = static_cast<sf::Vector2u>(mouseCoords / static_cast<float>(TileMap::sSizeOfATile));
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
			mTileVertexArray.setTileMap(mTileMap);
			mBorderVertexArray.setTileMap(mTileMap);
		}
	}
	

	//Update TextFields
	mLoadTextField.updateState(renderWindow, &mMenuView);
	mSaveTextField.updateState(renderWindow, &mMenuView);

	//Update Buttons
	mLoadButton.updateState(renderWindow);
	mSaveButton.updateState(renderWindow);

	//Manage Loading and Saving
	if (mLoadButton.getMouseReleasedEventOccured())
	{
		if (mTileMap.loadFromFile(mLoadTextField.getTextString()))
		{
			mSaveTextField.setTextString(mLoadTextField.getTextString());
			mTileVertexArray.setTileMap(mTileMap);
			mBorderVertexArray.setTileMap(mTileMap);
		}
	}
	if (mSaveButton.getMouseReleasedEventOccured())
	{
		if (mSaveTextField.getTextStringSize() > 16)
		{
			mTileMap.saveToFile(mSaveTextField.getTextString());
		}
	}

	//Update DropDownMenu
	mDropDownMenu.update(frametime, renderWindow);
	mBorderDrawingModeCheckBox.updateState(renderWindow);
	TileTypeCategory newTileTypeCategory = mVectorOfTileTypeCategoriesInDropDownMenu.at(mDropDownMenu.getCurrentChoice());
	if (newTileTypeCategory != mActiveTileTypeCategory)
	{
		mActiveTileTypeCategory = newTileTypeCategory;
		this->handleDropDownMenuTileTypeCategoryChange();
	}
	

	//Change MouseTileType
	if (EventManager::checkForEvent(EventManager::EventType::MOUSE_RELEASED))
	{
		EventManager::MouseInfo mouseInfo = EventManager::getReleasedMouseInfo();
		if ((mouseInfo.button == sf::Mouse::Button::Left) || (mouseInfo.button == sf::Mouse::Button::Right))
		{
			bool leftMouse = (mouseInfo.button == sf::Mouse::Button::Left);
			sf::Vector2f mousePos = static_cast<sf::Vector2f>(mouseInfo.position);
			if (mRectShapeOfSelectionArea.pointer->getGlobalBounds().contains(mousePos))
			{
				sf::Vector2u tilePos = static_cast<sf::Vector2u>((mousePos - mPosOfSelectionArea) / static_cast<float>(TileMap::sSizeOfATile));
				unsigned int tilePosInVector = tilePos.x + tilePos.y * mSizeOfSelectionArea.x;
				if (tilePosInVector >= mVectorOfTileTypesInSelectionArea.size())
				{
					return;
				}
				this->setSelectionVertexArray(tilePosInVector);
				TileType chosenTileType = mVectorOfTileTypesInSelectionArea.at(tilePosInVector);
				if (leftMouse)
				{
					mLeftMouseTileType = chosenTileType;
					mTileSquareShapeOfLeftMouseTileType.setTileType(chosenTileType);
				}
				else
				{
					mRightMouseTileType = chosenTileType;
					mTileSquareShapeOfRightMouseTileType.setTileType(chosenTileType);
				}
			}
		}
	}


	//Switch between Tile-Drawing and Border-Drawing-Mode
	if (mBorderDrawingModeCheckBox.getHasChangedState())
	{
		mDrawBordersInsteadOfTiles = mBorderDrawingModeCheckBox.getIsTicked();
		if (mDrawBordersInsteadOfTiles)
		{
			mDropDownMenu.setActive(false);
		}
		else
		{
			mDropDownMenu.setActive(true);
		}
	}


	//Draw Borders with Mouse
	if (mDrawBordersInsteadOfTiles)
	{
		if (mDrawBVAOfActualBorderDrawing)
		{
			sf::Vector2f mousePos = renderWindow->mapPixelToCoords(sf::Mouse::getPosition(*renderWindow), mTilesView);
			mBorderOfActualBorderDrawing.point2 = this->getNearestBorderVertex(mousePos);
			mBorderVertexArrayOfActualBorderDrawing.setSingleBorder(mBorderOfActualBorderDrawing);
			if (EventManager::checkForEvent(EventManager::EventType::MOUSE_RELEASED))
			{
				if (EventManager::getReleasedMouseInfo().button == sf::Mouse::Button::Left)
				{
					mDrawBVAOfActualBorderDrawing = false;
					mTileMap.addBorder(mBorderOfActualBorderDrawing);
					mBorderVertexArray.setTileMap(mTileMap);
				}
			}
		}
		else
		{
			if (EventManager::checkForEvent(EventManager::EventType::MOUSE_PRESSED))
			{
				EventManager::MouseInfo mousePressedInfo = EventManager::getPressedMouseInfo();
				if (mousePressedInfo.button == sf::Mouse::Button::Left)
				{
					mDrawBVAOfActualBorderDrawing = true;
					sf::Vector2f mousePos = renderWindow->mapPixelToCoords(mousePressedInfo.position, mTilesView);
					sf::Vector2i nearestVertexPos = this->getNearestBorderVertex(mousePos);
					mBorderOfActualBorderDrawing.point1 = nearestVertexPos;
					mBorderOfActualBorderDrawing.point2 = nearestVertexPos;
					mBorderOfActualBorderDrawing.type = mBorderTypeOfActualBorderDrawing;
					mBorderVertexArrayOfActualBorderDrawing.setSingleBorder(mBorderOfActualBorderDrawing);
				}
			}
		}
	}
	
}

void Editor::render(sf::RenderWindow* renderWindow)
{
	//Memorize Initial View
	sf::View initialView = renderWindow->getView();

	//Render Menu Stuff
	renderWindow->setView(mMenuView);
	renderWindow->draw(*mMenuBackgroundRectangle.pointer);
	mLoadTextField.render(renderWindow);
	mSaveTextField.render(renderWindow);
	mLoadButton.render(renderWindow);
	mSaveButton.render(renderWindow);
	mTileSquareShapeOfLeftMouseTileType.render(renderWindow);
	mTileSquareShapeOfRightMouseTileType.render(renderWindow);
	renderWindow->draw(*mRectShapeOfSelectionArea.pointer);
	mDropDownMenu.render(renderWindow);
	mBorderDrawingModeCheckBox.render(renderWindow);
	renderWindow->draw(*mBorderDrawingModeText.pointer);
	for (auto tileSquareShape : mVectorOfTileSquareShapesInSelectionArea)
	{
		tileSquareShape.render(renderWindow);
	}
	renderWindow->draw(mVertexArrayOfSelectionAreaGrid);
	renderWindow->draw(mVertexArrayOfLastSelection);

	//Render Tile Stuff
	renderWindow->setView(mTilesView);
	mTileVertexArray.render(renderWindow);
	mBorderVertexArray.render(renderWindow);
	if (mDrawBVAOfActualBorderDrawing)
	{
		mBorderVertexArrayOfActualBorderDrawing.render(renderWindow);
	}

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


TileType Editor::getNextTileType(TileType tileType) const
{
	TileType newTileType = static_cast<TileType>(static_cast<int>(tileType) + 1);
	if (newTileType == TileType::NUM_OF_TILE_TYPES)
	{
		return static_cast<TileType>(0);
	}
	else
	{
		return newTileType;
	}
}
TileType Editor::getPreviousTileType(TileType tileType) const
{
	if (static_cast<int>(tileType) == 0)
	{
		return static_cast<TileType>(static_cast<int>(TileType::NUM_OF_TILE_TYPES) - 1);
	}
	else
	{
		return static_cast<TileType>(static_cast<int>(tileType) - 1);
	}
}

sf::Vector2i Editor::getNearestBorderVertex(sf::Vector2f const & mousePos) const
{
	return static_cast<sf::Vector2i>((mousePos / static_cast<float>(TileMap::sSizeOfATile) + sf::Vector2f(0.5f, 0.5f)));
}


void Editor::handleDropDownMenuTileTypeCategoryChange()
{
	//Fill mVectorOfTileTypesInSelectionArea
	mVectorOfTileTypesInSelectionArea.clear();
	for (unsigned int i = 0; i < static_cast<unsigned int>(TileType::NUM_OF_TILE_TYPES); ++i)
	{
		if (TileTypeProperties::getCategory(static_cast<TileType>(i)) == mActiveTileTypeCategory)
		{
			mVectorOfTileTypesInSelectionArea.push_back(static_cast<TileType>(i));
		}
	}
	mVectorOfTileTypesInSelectionArea.shrink_to_fit();

	//Create TileSquareShapes in SelectionArea
	mVectorOfTileSquareShapesInSelectionArea.clear();
	unsigned int size = mVectorOfTileTypesInSelectionArea.size();
	mVectorOfTileSquareShapesInSelectionArea.reserve(size);
	for (unsigned int i = 0; i < size; ++i)
	{
		sf::Vector2u position = sf::Vector2u(i % mSizeOfSelectionArea.x, i / mSizeOfSelectionArea.x);
		sf::Vector2f realPos = mPosOfSelectionArea + sf::Vector2f(position * TileMap::sSizeOfATile);
		mVectorOfTileSquareShapesInSelectionArea.push_back(TileSquareShape(realPos, mVectorOfTileTypesInSelectionArea.at(i)));
	}

	//Clear Selection VertexArray
	this->setSelectionVertexArray(0u, true);
}


void Editor::constructSelectionAreaGrid()
{
	for (unsigned int x = 1; x < mSizeOfSelectionArea.x; ++x)
	{
		sf::Vertex vertex1(mPosOfSelectionArea + static_cast<sf::Vector2f>(sf::Vector2u(x, 0u) * TileMap::sSizeOfATile), sf::Color::Black);
		sf::Vertex vertex2(mPosOfSelectionArea + static_cast<sf::Vector2f>(sf::Vector2u(x, mSizeOfSelectionArea.y) * TileMap::sSizeOfATile), sf::Color::Black);
		mVertexArrayOfSelectionAreaGrid.append(vertex1);
		mVertexArrayOfSelectionAreaGrid.append(vertex2);
	}
	for (unsigned int y = 1; y < mSizeOfSelectionArea.y; ++y)
	{
		sf::Vertex vertex1(mPosOfSelectionArea + static_cast<sf::Vector2f>(sf::Vector2u(0u, y) * TileMap::sSizeOfATile), sf::Color::Black);
		sf::Vertex vertex2(mPosOfSelectionArea + static_cast<sf::Vector2f>(sf::Vector2u(mSizeOfSelectionArea.x, y) * TileMap::sSizeOfATile), sf::Color::Black);
		mVertexArrayOfSelectionAreaGrid.append(vertex1);
		mVertexArrayOfSelectionAreaGrid.append(vertex2);
	}
}


void Editor::setSelectionVertexArray(unsigned int posInVectorOfTileTypes, bool clear)
{
	mVertexArrayOfLastSelection.clear();
	if (clear)
	{
		return;
	}
	sf::Vector2u pos(posInVectorOfTileTypes % mSizeOfSelectionArea.x, posInVectorOfTileTypes / mSizeOfSelectionArea.x);
	sf::Vertex v1(mPosOfSelectionArea + static_cast<sf::Vector2f>(sf::Vector2u(pos.x + 0u, pos.y + 0u) * TileMap::sSizeOfATile), sf::Color::Red);
	sf::Vertex v2(mPosOfSelectionArea + static_cast<sf::Vector2f>(sf::Vector2u(pos.x + 1u, pos.y + 0u) * TileMap::sSizeOfATile), sf::Color::Red);
	sf::Vertex v3(mPosOfSelectionArea + static_cast<sf::Vector2f>(sf::Vector2u(pos.x + 1u, pos.y + 1u) * TileMap::sSizeOfATile), sf::Color::Red);
	sf::Vertex v4(mPosOfSelectionArea + static_cast<sf::Vector2f>(sf::Vector2u(pos.x + 0u, pos.y + 1u) * TileMap::sSizeOfATile), sf::Color::Red);
	sf::Vertex v5(mPosOfSelectionArea + static_cast<sf::Vector2f>(sf::Vector2u(pos.x + 0u, pos.y + 0u) * TileMap::sSizeOfATile), sf::Color::Red);
	mVertexArrayOfLastSelection.append(v1);
	mVertexArrayOfLastSelection.append(v2);
	mVertexArrayOfLastSelection.append(v3);
	mVertexArrayOfLastSelection.append(v4);
	mVertexArrayOfLastSelection.append(v5);
}


