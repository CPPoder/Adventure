#ifndef EDITOR_HPP
#define EDITOR_HPP

#include "SFML\Graphics.hpp"

#include "Source\Tile\TileMap.hpp"
#include "Source\Tile\TileSquares.hpp"



class Editor
{
private:
	TileMap mTileMap;
	TileSquares mTileSquares;
	mySFML::Class::RectShape rect;
	float mMenuScreenWidthRatio;

	TileType mLeftMouseTileType = TileType::DIRT;
	TileType mRightMouseTileType = TileType::GRAS;

public:
	Editor();

	void update(sf::Time const & frametime, sf::RenderWindow* renderWindow);
	void render(sf::RenderWindow* renderWindow);

private:
	sf::View getMenuView(sf::RenderWindow* renderWindow);
	sf::View getTilesView(sf::RenderWindow* renderWindow);



};



#endif //EDITOR_HPP

