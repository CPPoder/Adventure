#include "stdafx.h"
#include "Source\Tile\BorderVertexArray.hpp"


BorderVertexArray::BorderVertexArray(TileMap const & tileMap)
	: pVertexArray(new sf::VertexArray(sf::Lines))
{
	this->setTileMap(tileMap);
}
BorderVertexArray::BorderVertexArray(Border const & singleBorder)
	: pVertexArray(new sf::VertexArray(sf::Lines))
{
	this->setSingleBorder(singleBorder);
}

BorderVertexArray::~BorderVertexArray()
{
	delete pVertexArray;
	pVertexArray = nullptr;
}


void BorderVertexArray::setTileMap(TileMap const & tileMap)
{
	pVertexArray->clear();
	std::list<Border> const & listOfBorders = tileMap.getListOfBorders();
	for (auto border : listOfBorders)
	{
		sf::Color color = this->getColorOfBorderType(border.type);
		sf::Vertex vertex1(static_cast<sf::Vector2f>(border.point1) * static_cast<float>(TileMap::sSizeOfATile), color);
		sf::Vertex vertex2(static_cast<sf::Vector2f>(border.point2) * static_cast<float>(TileMap::sSizeOfATile), color);
		pVertexArray->append(vertex1);
		pVertexArray->append(vertex2);
	}
}

void BorderVertexArray::setSingleBorder(Border const & singleBorder)
{
	pVertexArray->clear();
	sf::Color color = this->getColorOfBorderType(singleBorder.type);
	sf::Vertex vertex1(static_cast<sf::Vector2f>(singleBorder.point1) * static_cast<float>(TileMap::sSizeOfATile), color);
	sf::Vertex vertex2(static_cast<sf::Vector2f>(singleBorder.point2) * static_cast<float>(TileMap::sSizeOfATile), color);
	pVertexArray->append(vertex1);
	pVertexArray->append(vertex2);
}

void BorderVertexArray::render(sf::RenderWindow* renderWindow) const
{
	renderWindow->draw(*pVertexArray);
}


sf::Color BorderVertexArray::getColorOfBorderType(Border::Type borderType)
{
	switch (borderType)
	{
	case Border::Type::INSURMOUNTABLE:
		return sf::Color::Red;
	}
}
