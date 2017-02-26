#ifndef BORDER_HPP
#define BORDER_HPP


#include "SFML\Graphics.hpp"


class Border
{
public:
	enum class Type //Can be used to describe several types of Borders, e.g. Hole, Water, Wall, ...
	{
		INSURMOUNTABLE,


		NUM_OF_BORDER_TYPES
	};


public:
	sf::Vector2i point1;
	sf::Vector2i point2;
	Type type;


public:
	Border(sf::Vector2i const & _point1, sf::Vector2i const & _point2, Type _type);
	Border(Border const & border);

	void set(Border const & border);

	bool operator==(Border const & border) const;

};





#endif //BORDER_HPP

