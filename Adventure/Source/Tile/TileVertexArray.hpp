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

public:
	TileVertexArray(TileMap const & tileMap);
	~TileVertexArray();

	void setTileMap(TileMap const & tileMap);

	void render(sf::RenderWindow* renderWindow) const;


public:
	static sf::IntRect getTextureRectForTileType(TileType tileType);


};




#endif //TILEVERTEXARRAY_HPP

