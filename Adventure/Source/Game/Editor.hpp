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

public:
	Editor();

	void update(sf::Time const & frametime, sf::RenderWindow* renderWindow);
	void render(sf::RenderWindow* renderWindow);




};



#endif //EDITOR_HPP

