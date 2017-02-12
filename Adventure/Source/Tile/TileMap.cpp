#include "stdafx.h"
#include "Source\Tile\TileMap.hpp"

TileMap::TileMap()
{

}
TileMap::TileMap(std::string const & openFilePath)
{
	this->loadFromFile(openFilePath);
}
TileMap::~TileMap()
{

}

TileContents& TileMap::at(unsigned int x, unsigned int y)
{
	return mMatrixOfTileContents.at(y).at(x);
}
TileContents& TileMap::at(sf::Vector2u const & pos)
{
	return mMatrixOfTileContents.at(pos.y).at(pos.x);
}

TileContents const & TileMap::at(unsigned int x, unsigned int y) const
{
	return mMatrixOfTileContents.at(y).at(x);
}
TileContents const & TileMap::at(sf::Vector2u const & pos) const
{
	return mMatrixOfTileContents.at(pos.y).at(pos.x);
}


void TileMap::setAt(TileContents const & tileContents, unsigned int x, unsigned int y)
{
	//Insert empty vectors if y is too large
	unsigned int ySize = this->getYSize();
	if (y >= ySize)
	{
		unsigned int yDiff = y - ySize;
		for (unsigned int i = 0; i < yDiff + 1; ++i)
		{
			mMatrixOfTileContents.push_back(std::vector<TileContents>());
		}
		mMatrixOfTileContents.shrink_to_fit();
	}

	//Insert void TileContents into vector at y if x is too large
	unsigned int xSize = this->getXSizeAt(y);
	if (x >= xSize)
	{
		unsigned int xDiff = x - xSize;
		for (unsigned int i = 0; i < xDiff + 1; ++i)
		{
			mMatrixOfTileContents.at(y).push_back(TileContents(TileType::VOID));
		}
	}
	mMatrixOfTileContents.at(y).shrink_to_fit();

	//Do actual set job
	this->at(x, y) = tileContents;
}
void TileMap::setAt(TileContents const & tileContents, sf::Vector2u const & pos)
{
	this->setAt(tileContents, pos.x, pos.y);
}


bool TileMap::loadFromFile(std::string const & path)
{
	//Clear mVectorOfTileContents
	mMatrixOfTileContents.clear();

	//Extract lines from File
	std::ifstream inputFileStream(path);
	std::vector<std::string> linesOfFile;
	if (inputFileStream.good())
	{
		while (inputFileStream.good())
		{
			std::string line;
			std::getline(inputFileStream, line);
			linesOfFile.push_back(line);
		}
	}
	else
	{
		std::cerr << "Could not open File: " << path << std::endl;
		return false;
		//throw "TileMap::loadFromFile(std::string const & path) : Could not open File!";
	}

	//Use extracted lines and cut into integers and write into vectors
	std::vector<std::vector<TileType>> matOfTileTypes;
	for (auto line : linesOfFile)
	{
		std::vector<TileType> tileTypeVector;
		std::stringstream stringStream(line);
		while (stringStream.good())
		{
			int intData;
			stringStream >> intData;
			tileTypeVector.push_back(static_cast<TileType>(intData));
		}
		matOfTileTypes.push_back(tileTypeVector);
	}

	//Combine all extracted data (e.g. TileType, ItemType, Border, ...)
	mMatrixOfTileContents.reserve(matOfTileTypes.size());
	for (auto vecOfTileType : matOfTileTypes)
	{
		std::vector<TileContents> vecOfTileContents;
		vecOfTileContents.reserve(vecOfTileType.size());
		for (auto tileType : vecOfTileType)
		{
			TileContents tileContents;
			tileContents.tileType = tileType;
			vecOfTileContents.push_back(tileContents);
		}
		mMatrixOfTileContents.push_back(vecOfTileContents);
	}

	return true;
}

void TileMap::saveToFile(std::string const & path) const
{
	std::ofstream outFileStream(path, std::ios_base::trunc);

	bool firstVec = true;
	for (auto vec : mMatrixOfTileContents)
	{
		if (!firstVec)
		{
			outFileStream << std::endl;
		}
		bool firstTile = true;
		for (auto tileContents : vec)
		{
			if (!firstTile)
			{
				outFileStream << " ";
			}
			outFileStream << static_cast<int>(tileContents.tileType);
			firstTile = false;
		}
		firstVec = false;;
	}

	outFileStream.close();
}

unsigned int TileMap::getYSize() const
{
	return mMatrixOfTileContents.size();
}
unsigned int TileMap::getXSizeAt(unsigned int y) const
{
	return mMatrixOfTileContents.at(y).size();
}

void TileMap::outputOnTerminal() const
{
	for (auto vec : mMatrixOfTileContents)
	{
		for (auto tileContents : vec)
		{
			std::cout << tileContents;
		}
		std::cout << std::endl;
	}
}


sf::IntRect TileMap::getTextureRectForTileType(TileType tileType)
{
	return sf::IntRect(static_cast<int>(tileType) * sSizeOfATile, 0, sSizeOfATile, sSizeOfATile);
}

