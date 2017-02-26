#ifndef BORDERVERTEXARRAY_HPP
#define BORDERVERTEXARRAY_HPP


#include "SFML\Graphics.hpp"

#include "Source\Tile\Border.hpp"
#include "Source\Tile\TileMap.hpp"

#include "mySFMLVectorFunctions.hpp"


class BorderVertexArray
{
private:
	sf::VertexArray *pVertexArray;

public:
	BorderVertexArray(TileMap const & tileMap);
	BorderVertexArray(Border const & singleBorder);
	~BorderVertexArray();

	void setTileMap(TileMap const & tileMap);
	void setSingleBorder(Border const & singleBorder);

	void render(sf::RenderWindow* renderWindow) const;

public:
	static sf::Color getColorOfBorderType(Border::Type borderType);

};



#endif //BORDERVERTEXARRAY_HPP

