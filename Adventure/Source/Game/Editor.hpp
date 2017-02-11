#ifndef EDITOR_HPP
#define EDITOR_HPP

#include "SFML\Graphics.hpp"

#include "Source\Tile\TileMap.hpp"
#include "Source\Tile\TileSquares.hpp"
#include "Source\ControlElements\TextField.hpp"



class Editor
{
private:
	TileMap mTileMap;
	TileSquares mTileSquares;
	mySFML::Class::RectShape rect;
	float mMenuScreenWidthRatio;

	TileType mLeftMouseTileType = TileType::DIRT;
	TileType mRightMouseTileType = TileType::GRAS;

	TextField mTextField;

	sf::View mMenuView;
	sf::View mTilesView;

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

