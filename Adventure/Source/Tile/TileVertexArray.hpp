#ifndef TILEVERTEXARRAY_HPP
#define TILEVERTEXARRAY_HPP


#include "SFML\Graphics.hpp"

#include "Source\Tile\TileMap.hpp"
#include "Source\Framework\TextureManager.hpp"

#include "mySFMLVectorFunctions.hpp"


class TileVertexArray
{
private:
	sf::Texture const *pTextureAtlasOfTiles;
	sf::VertexArray *pVertexArray;
	float mEpsilon = 1.0E-04f;

public:
	TileVertexArray(TileMap const & tileMap);
	~TileVertexArray();

	void setTileMap(TileMap const & tileMap);

	void render(sf::RenderWindow* renderWindow) const;

};




#endif //TILEVERTEXARRAY_HPP

