#ifndef EDITOR_HPP
#define EDITOR_HPP

#include "SFML\Graphics.hpp"

#include "Source\Tile\TileMap.hpp"
#include "Source\Tile\TileVertexArray.hpp"
#include "Source\ControlElements\TextField.hpp"
#include "Source\ControlElements\Button.hpp"
#include "Source\Tile\TileSquareShape.hpp"
#include "Source\ControlElements\DropDownMenu.hpp"



class Editor
{
private:
	//Editor Variables
	float mMenuScreenWidthRatio = 0.3f;

	sf::View mMenuView;
	sf::View mTilesView;

	//Interaction Variables
	TileType mLeftMouseTileType = TileType::DIRT;
	TileType mRightMouseTileType = TileType::GRAS;

	//Tile Variables
	TileMap mTileMap;
	TileVertexArray mTileVertexArray;

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
	sf::Vector2f const mPosOfLeftMouseTileTypeSquare		= sf::Vector2f(50.f, 150.f);
	sf::Vector2f const mRelDistBetweenTileTypeSquares		= sf::Vector2f(50.f, 0.f);
	TileSquareShape mTileSquareShapeOfLeftMouseTileType;
	TileSquareShape mTileSquareShapeOfRightMouseTileType;
	sf::Vector2u const mSizeOfSelectionArea					= sf::Vector2u(7u, 10u);
	sf::Vector2f const mPosOfSelectionArea					= sf::Vector2f(20.f, 450.f);
	mySFML::Class::RectShape mRectShapeOfSelectionArea;
	sf::Vector2f const mPosOfDropDownMenu					= sf::Vector2f(20.f, 250.f);
	sf::Vector2f const mSizeOfSingleDropDownMenuField		= sf::Vector2f(200.f, 30.f);
	unsigned int const mNumberOfFieldsInDropMenu			= 4u;
	sf::Vector2f const mSizeOfDropMenu						= sf::Vector2f(mSizeOfSingleDropDownMenuField.x, mSizeOfSingleDropDownMenuField.y * mNumberOfFieldsInDropMenu);
	unsigned int const mCharacterSizeOfDropDownMenu			= 14u;
	DropDownMenu mDropDownMenu;

	
	

public:
	Editor();
	~Editor();

	void update(sf::Time const & frametime, sf::RenderWindow* renderWindow);
	void render(sf::RenderWindow* renderWindow);

private:
	sf::View getInitialMenuView(sf::RenderWindow const * renderWindow) const;
	sf::View getInitialTilesView(sf::RenderWindow const * renderWindow) const;



};



#endif //EDITOR_HPP

