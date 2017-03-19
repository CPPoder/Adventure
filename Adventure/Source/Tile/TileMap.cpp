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
			mMatrixOfTileContents.at(y).push_back(TileContents(0u));
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


void TileMap::addBorder(Border const & border)
{
	for (auto b : mListOfBorders)
	{
		if (b == border)
		{
			return;
		}
	}
	mListOfBorders.push_back(border);
}

std::list<Border> const & TileMap::getListOfBorders() const
{
	return mListOfBorders;
}


bool TileMap::loadFromFile(std::string const & path)
{
	//Extract lines from File
	std::ifstream inputFileStream(path);
	std::vector<std::string> linesOfFile;
	if (inputFileStream.good())
	{
		mMatrixOfTileContents.clear();
		mListOfBorders.clear();
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
	}

	//linesOfFile contains now all Lines as seperate entries! Now: Cut into seperate vectors for different data structure sections!
	std::vector<std::string> linesOfTileContents;
	std::vector<std::string> linesOfBorders;
	bool tileContentsSection = false;
	for (auto line : linesOfFile)
	{
		if (tileContentsSection && line == "<TileContents:End>")
		{
			break;
		}
		if (tileContentsSection)
		{
			linesOfTileContents.push_back(line);
		}
		if (!tileContentsSection && line == "<TileContents:Begin>")
		{
			tileContentsSection = true;
		}
	}
	bool bordersSection = false;
	for (auto line : linesOfFile)
	{
		if (bordersSection && line == "<Borders:End>")
		{
			break;
		}
		if (bordersSection)
		{
			linesOfBorders.push_back(line);
		}
		if (!bordersSection && line == "<Borders:Begin>")
		{
			bordersSection = true;
		}
	}

	//Use extracted TileContentLines, cut into integers and write into vectors
	std::vector<std::vector<TileType>> matOfTileTypes;
	for (auto line : linesOfTileContents)
	{
		std::vector<TileType> tileTypeVector;
		if (!line.empty())
		{
			std::stringstream stringStream(line);
			while (stringStream.good())
			{
				int intData;
				stringStream >> intData; //Here occured an error!!! For "Big.tm" -858993460 occured, because an empty stringstream is somehow good but extraction fails!!!
				tileTypeVector.push_back(static_cast<TileType>(intData));
			}
			matOfTileTypes.push_back(tileTypeVector);
		}
		else
		{
			matOfTileTypes.push_back(tileTypeVector);
		}
	}

	//Use extracted BorderLines, cut into integers and write into vectors
	std::list<Border> listOfBorders;
	for (auto line : linesOfBorders)
	{
		std::stringstream stringStream(line);
		while (stringStream.good())
		{
			int p1x, p1y, p2x, p2y, type;
			stringStream >> p1x >> p1y >> p2x >> p2y >> type;
			listOfBorders.push_back(Border(sf::Vector2i(p1x, p1y), sf::Vector2i(p2x, p2y), static_cast<Border::Type>(type)));
		}
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
	mListOfBorders = listOfBorders;

	return true;
}

void TileMap::saveToFile(std::string const & path) const
{
	//OpenFileStream
	std::ofstream outFileStream(path, std::ios_base::trunc);

	//Save TileContents
	outFileStream << "<TileContents:Begin>" << std::endl;
	for (auto vec : mMatrixOfTileContents)
	{
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
		outFileStream << std::endl;
	}
	outFileStream << "<TileContents:End>" << std::endl;

	//Save Borders
	outFileStream << "<Borders:Begin>" << std::endl;
	for (auto border : mListOfBorders)
	{
		outFileStream << border.point1.x << " " << border.point1.y << " " << border.point2.x << " " << border.point2.y << " " << static_cast<int>(border.type) << std::endl;
	}
	outFileStream << "<Borders:End>" << std::endl;

	//Close FileStream
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
	sf::Vector2u tileTypePos = TileTypeProperties::getPosition(tileType);
	return sf::IntRect(tileTypePos.x * sSizeOfATile, tileTypePos.y * sSizeOfATile, sSizeOfATile, sSizeOfATile);
}

