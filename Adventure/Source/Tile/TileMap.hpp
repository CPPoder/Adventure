#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include "myUsefulMath.hpp"

#include "SFML\Graphics.hpp"

#include "Source\Tile\TileContents.hpp"
#include "Source\Tile\Border.hpp"

#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>


class TileMap
{
private:
	std::vector<std::vector<TileContents>> mMatrixOfTileContents;
	std::list<Border> mListOfBorders;

public:
	TileMap();
	TileMap(std::string const & openFilePath);
	~TileMap();

	TileContents& at(unsigned int x, unsigned int y);
	TileContents& at(sf::Vector2u const & pos);

	TileContents const & at(unsigned int x, unsigned int y) const;
	TileContents const & at(sf::Vector2u const & pos) const;

	void setAt(TileContents const & tileContents, unsigned int x, unsigned int y);
	void setAt(TileContents const & tileContents, sf::Vector2u const & pos);

	void addBorder(Border const & border);
	std::list<Border> const & getListOfBorders() const;

	bool loadFromFile(std::string const & path);
	void saveToFile(std::string const & path) const;

	unsigned int getYSize() const;
	unsigned int getXSizeAt(unsigned int y) const;
	sf::Vector2u getSize() const;

	void outputOnTerminal() const;

public:
	static constexpr unsigned int sSizeOfATile = 32u;
	static sf::IntRect getTextureRectForTileType(TileType tileType);


};



#endif //TILEMAP_HPP

