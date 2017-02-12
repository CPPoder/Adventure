#ifndef EDITOR_HPP
#define EDITOR_HPP

#include "SFML\Graphics.hpp"

#include "Source\Tile\TileMap.hpp"
#include "Source\Tile\TileVertexArray.hpp"
#include "Source\ControlElements\TextField.hpp"
#include "Source\ControlElements\Button.hpp"



class Editor
{
private:
	//Editor Variables
	float mMenuScreenWidthRatio = 0.3f;

	sf::View mMenuView;
	sf::View mTilesView;

	//Tile Variables
	TileMap mTileMap;
	TileVertexArray mTileVertexArray;

	//Menu Variables
	mySFML::Class::RectShape mMenuBackgroundRectangle;
	sf::Vector2f const mPosOfFirstLoadSaveTextField = sf::Vector2f(10.f, 30.f);
	sf::Vector2f const mRelDistBetweenLoadSaveTextFilds = sf::Vector2f(0.f, 45.f);
	sf::Vector2f const mSizeOfLoadSaveTextFields = sf::Vector2f(220.f, 30.f);
	unsigned int const mCharacterSizeOfTextFields = 12u;
	unsigned int const mCharacterSizeOfButtons = 14u;
	sf::Vector2f const mDistBetweenTextFieldAndButton = sf::Vector2f(10.f, 0.f);
	sf::Vector2f const mSizeOfLoadSaveButtons = sf::Vector2f(50.f, mSizeOfLoadSaveTextFields.y);
	TextField mLoadTextField;
	TextField mSaveTextField;
	Button mLoadButton;
	Button mSaveButton;

	//Interaction Variables
	TileType mLeftMouseTileType = TileType::DIRT;
	TileType mRightMouseTileType = TileType::GRAS;
	

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

