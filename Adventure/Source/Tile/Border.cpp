#include "stdafx.h"
#include "Source\Tile\Border.hpp"


Border::Border(sf::Vector2i const & _point1, sf::Vector2i const & _point2, Type _type)
	: point1(_point1),
	  point2(_point2),
	  type(_type)
{
}

Border::Border(Border const & border)
	: point1(border.point1),
	  point2(border.point2),
	  type(border.type)
{
}


void Border::set(Border const & border)
{
	point1 = border.point1;
	point2 = border.point2;
	type = border.type;
}


bool Border::operator==(Border const & border) const
{
	return ((point1 == border.point1) && (point2 == border.point2) && (type == border.type));
}

