#ifndef EDITOR_HPP
#define EDITOR_HPP

#include "SFML\Graphics.hpp"

#include "Source\Tile\TileMap.hpp"
#include "Source\Tile\TileVertexArray.hpp"
#include "Source\Tile\BorderVertexArray.hpp"
#include "Source\ControlElements\TextField.hpp"
#include "Source\ControlElements\Button.hpp"
#include "Source\ControlElements\CheckBox.hpp"
#include "Source\Tile\TileSquareShape.hpp"
#include "Source\ControlElements\DropDownMenu.hpp"

#include <vector>
#include <list>



class Editor
{
private:
	//Fonts
	mySFML::Class::Fonts mFonts;

	//Editor Variables
	float mMenuScreenWidthRatio = 0.3f;
	sf::View mMenuView;
	sf::View mTilesView;

	//Interaction Variables
	TileType mLeftMouseTileType = 1u;
	TileType mRightMouseTileType = 1u;
	bool mDrawBordersInsteadOfTiles = false;

	//Tile Variables
	TileMap mTileMap;
	TileVertexArray mTileVertexArray;
	BorderVertexArray mBorderVertexArray;
	Border mBorderOfActualBorderDrawing;
	BorderVertexArray mBorderVertexArrayOfActualBorderDrawing;
	bool mDrawBVAOfActualBorderDrawing = false;
	Border::Type mBorderTypeOfActualBorderDrawing = Border::Type::INSURMOUNTABLE;
	sf::VertexArray mVertexArrayOfTilesAreaGrid;
	sf::Vector2i mLeftUpNeededTilesGridVertexPos;
	sf::Vector2i mRightDownNeededTilesGridVertexPos;
	bool mDrawVertexArrayOfTilesAreaGrid = true;
	sf::Color mColorOfTilesAreaGrid = sf::Color::Red;

	//Menu Variables (Basic)
	mySFML::Class::RectShape mMenuBackgroundRectangle;

	//Menu Variables (Load/Save)
	sf::Vector2f const mPosOfFirstLoadSaveTextField			= sf::Vector2f(10.f, 30.f);
	sf::Vector2f const mRelDistBetweenLoadSaveTextFilds		= sf::Vector2f(0.f, 45.f);
	sf::Vector2f const mSizeOfLoadSaveTextFields			= sf::Vector2f(220.f, 30.f);
	unsigned int const mCharacterSizeOfTextFields			= 12u;
	unsigned int const mCharacterSizeOfButtons				= 14u;
	sf::Vector2f const mDistBetweenTextFieldAndButton		= sf::Vector2f(10.f, 0.f);
	sf::Vector2f const mSizeOfLoadSaveButtons				= sf::Vector2f(50.f, mSizeOfLoadSaveTextFields.y);
	TextField mLoadTextField;
	TextField mSaveTextField;
	Button mLoadButton;
	Button mSaveButton;

	//Menu Variables (TileType Selection)
	sf::Vector2f const mPosOfLeftMouseTileTypeSquare		= sf::Vector2f(70.f, 320.f);
	sf::Vector2f const mRelDistBetweenTileTypeSquares		= sf::Vector2f(60.f, 0.f);
	TileSquareShape mTileSquareShapeOfLeftMouseTileType;
	TileSquareShape mTileSquareShapeOfRightMouseTileType;

	sf::Vector2f const mPosOfDropDownMenu					= sf::Vector2f(20.f, 400.f);
	sf::Vector2f const mSizeOfSingleDropDownMenuField		= sf::Vector2f(200.f, 30.f);
	unsigned int const mNumberOfFieldsInDropMenu			= 4u;
	sf::Vector2f const mSizeOfDropMenu						= sf::Vector2f(mSizeOfSingleDropDownMenuField.x, mSizeOfSingleDropDownMenuField.y * mNumberOfFieldsInDropMenu);
	unsigned int const mCharacterSizeOfDropDownMenu			= 14u;
	std::vector<TileTypeCategory> mVectorOfTileTypeCategoriesInDropDownMenu = { TileTypeCategory::GRASS,
																				TileTypeCategory::DIRT,
																				TileTypeCategory::WATER,
																				TileTypeCategory::BRICKED };
	std::vector<std::string> mVectorOfTileTypeCategoryNamesInDropDownMenu = { "Grass", "Dirt", "Water", "Bricked" };
	DropDownMenu mDropDownMenu;

	sf::Vector2u const mSizeOfSelectionArea					= sf::Vector2u(7u, 10u);
	sf::Vector2f const mPosOfSelectionArea					= sf::Vector2f(20.f, 450.f);
	mySFML::Class::RectShape mRectShapeOfSelectionArea;
	std::vector<TileType> mVectorOfTileTypesInSelectionArea;
	TileTypeCategory mActiveTileTypeCategory				= TileTypeCategory::GRASS;
	std::vector<TileSquareShape> mVectorOfTileSquareShapesInSelectionArea;
	sf::VertexArray mVertexArrayOfSelectionAreaGrid;
	sf::VertexArray mVertexArrayOfLastSelection;

	sf::Vector2f const mPosOfBorderDrawingModeCheckBox		= sf::Vector2f(30.f, 370.f);
	sf::Vector2f const mRelDistOfBorderDrawingMoveText		= sf::Vector2f(25.f, 0.f);
	CheckBox mBorderDrawingModeCheckBox;
	mySFML::Class::Text mBorderDrawingModeText;


	//Menu Variables (Tiles Grid Selection)
	sf::Vector2f const mPosOfGridDrawingCheckBox			= sf::Vector2f(30.f, 130.f);
	sf::Vector2f const mRelDistOfGridDrawingText			= sf::Vector2f(25.f, 0.f);
	CheckBox mGridDrawingCheckBox;
	mySFML::Class::Text mGridDrawingText;
	
	
	

public:
	Editor();
	~Editor();

	void update(sf::Time const & frametime, sf::RenderWindow* renderWindow);
	void render(sf::RenderWindow* renderWindow);

private:
	sf::View getInitialMenuView(sf::RenderWindow const * renderWindow) const;
	sf::View getInitialTilesView(sf::RenderWindow const * renderWindow) const;
	TileType getPreviousTileType(TileType tileType) const;
	TileType getNextTileType(TileType tileType) const;
	sf::Vector2i getNearestBorderVertex(sf::Vector2f const & mousePos) const;

	void handleDropDownMenuTileTypeCategoryChange();
	void constructSelectionAreaGrid();
	void changeTilesAreaGridIfNeeded();
	void constructTilesAreaGrid();
	void setSelectionVertexArray(unsigned int posInVectorOfTileTypes, bool clear = false);


};



#endif //EDITOR_HPP

