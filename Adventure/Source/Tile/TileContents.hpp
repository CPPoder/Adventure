#ifndef TILECONTENTS_HPP
#define TILECONTENTS_HPP

#include "Source\Tile\TileType.hpp"

#include <iostream>

class TileContents
{
public:
	TileType tileType;

	TileContents() = default;
	TileContents(TileType _tileType);

	friend std::ostream& operator<<(std::ostream& oStream, TileContents const & tileContents)
	{
		oStream << static_cast<int>(tileContents.tileType);
		return oStream;
	}

};




#endif //TILECONTENTS_HPP

