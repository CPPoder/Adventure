#include "stdafx.h"
#include "Source\Collision\CollisionArea.hpp"


//Constructors
CollisionArea::CollisionArea()
{
}
CollisionArea::CollisionArea(CollisionArea const & collisionArea)
{
	this->set(collisionArea);
}
CollisionArea::CollisionArea(std::list<sf::Shape*> listOfShapes)
{
	this->set(listOfShapes);
}
CollisionArea::CollisionArea(sf::Shape* shape)
{
	this->addShape(shape);
}

//Destructor
CollisionArea::~CollisionArea()
{
	for (auto shape : mListOfShapes)
	{
		delete shape;
		shape = nullptr;
	}
	mListOfShapes.clear();
}


//Movement Setter
void CollisionArea::move(sf::Vector2f movement)
{
	for (auto shape : mListOfShapes)
	{
		shape->move(movement);
	}
}
void CollisionArea::rotateAround(sf::Vector2f origin, float angle)
{
	for (auto shape : mListOfShapes)
	{
		shape->setOrigin(origin);
		shape->rotate(angle);
		this->setOriginCorrect(shape);
	}
}


//Render
void CollisionArea::render(sf::RenderWindow* renderWindow) const
{
	for (auto shape : mListOfShapes)
	{
		renderWindow->draw(*shape);
	}
}


//Shape Setter
void CollisionArea::set(CollisionArea const & collisionArea)
{
	this->set(collisionArea.mListOfShapes);
}
void CollisionArea::set(std::list<sf::Shape*> listOfShapes)
{
	for (auto shape : listOfShapes)
	{
		this->addShape(shape);
	}
}
void CollisionArea::addShape(sf::Shape* shape)
{
	sf::RectangleShape* rectShapePointer = nullptr;
	sf::CircleShape* circleShapePointer = nullptr;
	if (this->tryToConvertToRectangleShape(shape, rectShapePointer))
	{
		mListOfShapes.push_back(this->setOriginTopLeft(new sf::RectangleShape(*rectShapePointer)));
	}
	if (this->tryToConvertToCircleShape(shape, circleShapePointer))
	{
		mListOfShapes.push_back(this->setOriginCentered(new sf::CircleShape(*circleShapePointer)));
	}
}


//Collision Check
bool CollisionArea::checkCollisionWith(sf::Shape* shape) const
{
	for (auto s : mListOfShapes)
	{
		if (this->checkCollisionBetween(s, shape))
		{
			return true;
		}
	}
	return false;
}



//Internal Functions
bool CollisionArea::tryToConvertToRectangleShape(sf::Shape* input, sf::RectangleShape* & output)
{
	sf::RectangleShape* rectangleShapePointer = dynamic_cast<sf::RectangleShape*>(input);
	if (rectangleShapePointer == nullptr)
	{
		output = nullptr;
		return false;
	}
	else
	{
		output = rectangleShapePointer;
		return true;
	}
}
bool CollisionArea::tryToConvertToCircleShape(sf::Shape* input, sf::CircleShape* & output)
{
	sf::CircleShape* circleShapePointer = dynamic_cast<sf::CircleShape*>(input);
	if (circleShapePointer == nullptr)
	{
		output = nullptr;
		return false;
	}
	else
	{
		output = circleShapePointer;
		return true;
	}
}
bool CollisionArea::checkIfInputIsRectangleShapeOrCircleShape(sf::Shape* input)
{
	return ((dynamic_cast<sf::CircleShape*>(input) != nullptr) || (dynamic_cast<sf::RectangleShape*>(input) != nullptr));
}


bool CollisionArea::checkCollisionBetween(sf::Shape* s1, sf::Shape* s2)
{
	sf::CircleShape* c1 = nullptr;
	sf::CircleShape* c2 = nullptr;
	sf::RectangleShape* r1 = nullptr;
	sf::RectangleShape* r2 = nullptr;
	if (tryToConvertToCircleShape(s1, c1))
	{
		if (tryToConvertToCircleShape(s2, c2))
		{
			return checkCollisionBetween(c1, c2);
		}
		if (tryToConvertToRectangleShape(s2, r2))
		{
			return checkCollisionBetween(c1, r2);
		}
	}
	if (tryToConvertToRectangleShape(s1, r1))
	{
		if (tryToConvertToCircleShape(s2, c2))
		{
			return checkCollisionBetween(c2, r1);
		}
		if (tryToConvertToRectangleShape(s2, r2))
		{
			return checkCollisionBetween(r1, r2);
		}
	}
	return false;
}

bool CollisionArea::checkCollisionBetween(sf::CircleShape* c1, sf::CircleShape* c2)
{
	return (mySFML::Simple::lengthOf(c1->getPosition() - c2->getPosition()) < (c1->getRadius() + c2->getRadius()));
}
bool CollisionArea::checkCollisionBetween(sf::CircleShape* c, sf::RectangleShape* r)
{
	//Continue here!
}
bool CollisionArea::checkCollisionBetween(sf::RectangleShape* r1, sf::RectangleShape* r2)
{
	return r1->getGlobalBounds().intersects(r2->getGlobalBounds());
}

sf::Shape* CollisionArea::setOriginCorrect(sf::Shape* s)
{

}
sf::CircleShape* CollisionArea::setOriginCentered(sf::CircleShape* c)
{

}
sf::RectangleShape* CollisionArea::setOriginTopLeft(sf::RectangleShape* r)
{

}
