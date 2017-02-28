#include "stdafx.h"
#include "Source\Collision\CollisionArea.hpp"

#include <functional>


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
		mListOfShapes.push_back(this->setOriginTopLeft(new sf::RectangleShape(*rectShapePointer))); //SetOriginTopLeft does nothing at the moment!!!
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
bool CollisionArea::checkCollisionWith(Line const & line) const
{
	for (auto s : mListOfShapes)
	{
		if (this->checkCollisionBetween(s, line))
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
bool CollisionArea::checkCollisionBetween(sf::Shape* s, Line l)
{
	sf::RectangleShape* r = nullptr;
	sf::CircleShape* c = nullptr;
	if (tryToConvertToRectangleShape(s, r))
	{
		return checkCollisionBetween(r, l);
	}
	if (tryToConvertToCircleShape(s, c))
	{
		return checkCollisionBetween(c, l);
	}
	return false;
}

bool CollisionArea::checkCollisionBetween(sf::CircleShape* c1, sf::CircleShape* c2)
{
	return (mySFML::Simple::lengthOf(c1->getPosition() - c2->getPosition()) < (c1->getRadius() + c2->getRadius()));
}
bool CollisionArea::checkCollisionBetween(sf::CircleShape* c, sf::RectangleShape* r)
{
	return false;
}
bool CollisionArea::checkCollisionBetween(sf::RectangleShape* r1, sf::RectangleShape* r2)
{
	std::vector<sf::Vector2f> cornerPositions1 = getCornerPositionsOf(r1);
	std::vector<sf::Vector2f> cornerPositions2 = getCornerPositionsOf(r2);

	std::function<bool(Line const &, std::vector<sf::Vector2f> const &, std::vector<sf::Vector2f> const &)> checkIfProjectionsOntoLineOverlap = 
		[](Line const & line, std::vector<sf::Vector2f> const & cornerPositions1, std::vector<sf::Vector2f> const & cornerPositions2) -> bool
	{
		float r2Min, r2Max;
		bool minMax2Initialized = false;
		for (auto point : cornerPositions2)
		{
			float projection = line.projectPointOnLine(point);
			if (minMax2Initialized)
			{
				r2Min = myMath::Simple::min(r2Min, projection);
				r2Max = myMath::Simple::max(r2Max, projection);
			}
			else
			{
				r2Min = projection;
				r2Max = projection;
				minMax2Initialized = true;
			}
		}
		float r1Min, r1Max;
		bool minMax1Initialized = false;
		for (auto point : cornerPositions1)
		{
			float projection = line.projectPointOnLine(point);
			if (minMax1Initialized)
			{
				r1Min = myMath::Simple::min(r1Min, projection);
				r1Max = myMath::Simple::max(r1Max, projection);
			}
			else
			{
				r1Min = projection;
				r1Max = projection;
				minMax1Initialized = true;
			}
		}
		float a;
		float b;

		return myMath::Simple::checkIfIntervalsOverlap(r1Min, r1Max, r2Min, r2Max, a, b);
	};

	if (!checkIfProjectionsOntoLineOverlap(Line(cornerPositions1.at(0), cornerPositions1.at(1)), cornerPositions1, cornerPositions2))
	{
		return false;
	}
	else if (!checkIfProjectionsOntoLineOverlap(Line(cornerPositions1.at(1), cornerPositions1.at(2)), cornerPositions1, cornerPositions2))
	{
		return false;
	}
	else if (!checkIfProjectionsOntoLineOverlap(Line(cornerPositions2.at(0), cornerPositions2.at(1)), cornerPositions1, cornerPositions2))
	{
		return false;
	}
	else if (!checkIfProjectionsOntoLineOverlap(Line(cornerPositions2.at(1), cornerPositions2.at(2)), cornerPositions1, cornerPositions2))
	{
		return false;
	}
	else
	{
		return true;
	}
}
bool CollisionArea::checkCollisionBetween(sf::CircleShape* c, Line const & l)
{
	return true;
}
bool CollisionArea::checkCollisionBetween(sf::RectangleShape* r, Line const & l)
{
	sf::Transform inverseTrafo(r->getInverseTransform());
	sf::FloatRect localBounds = r->getLocalBounds();
	bool someEndpointInside = (localBounds.contains(inverseTrafo.transformPoint(l.vertex1)) || localBounds.contains(inverseTrafo.transformPoint(l.vertex2)));
	if (someEndpointInside)
	{
		return true;
	}
	auto cornerPositions = getCornerPositionsOf(r);
	Line line1(cornerPositions.at(0), cornerPositions.at(1));
	if (line1.intersects(l))
	{
		return true;
	}
	Line line2(cornerPositions.at(1), cornerPositions.at(2));
	if (line2.intersects(l))
	{
		return true;
	}
	Line line3(cornerPositions.at(2), cornerPositions.at(3));
	if (line3.intersects(l))
	{
		return true;
	}
	Line line4(cornerPositions.at(3), cornerPositions.at(0));
	if (line4.intersects(l))
	{
		return true;
	}
	return false;
}

sf::Shape* CollisionArea::setOriginCorrect(sf::Shape* s)
{
	sf::RectangleShape* r = nullptr;
	sf::CircleShape* c = nullptr;
	if (tryToConvertToRectangleShape(s, r))
	{
		return setOriginTopLeft(r);
	}
	if (tryToConvertToCircleShape(s, c))
	{
		return setOriginCentered(c);
	}
}
sf::CircleShape* CollisionArea::setOriginCentered(sf::CircleShape* c)
{
	sf::FloatRect globalBounds = c->getGlobalBounds();
	c->setOrigin(globalBounds.left + globalBounds.width / 2.f, globalBounds.top + globalBounds.height / 2.f);
	return c;
}
sf::RectangleShape* CollisionArea::setOriginTopLeft(sf::RectangleShape* r) //I don't see anymore why I would need this! Thus, does nothing at the moment!!!
{
	return r;
}

std::vector<sf::Vector2f> CollisionArea::getCornerPositionsOf(sf::RectangleShape* r)
{
	sf::Transform trafo = r->getTransform();
	sf::FloatRect localBounds = r->getLocalBounds();
	sf::Vector2f topLeft = sf::Vector2f(localBounds.left, localBounds.top);
	sf::Vector2f size = sf::Vector2f(localBounds.width, localBounds.height);

	std::vector<sf::Vector2f> cornerPositions;
	cornerPositions.reserve(4);

	cornerPositions.push_back(trafo.transformPoint(topLeft));
	cornerPositions.push_back(trafo.transformPoint(topLeft + sf::Vector2f(0.f, size.y)));
	cornerPositions.push_back(trafo.transformPoint(topLeft + size));
	cornerPositions.push_back(trafo.transformPoint(topLeft + sf::Vector2f(size.x, 0.f)));

	return cornerPositions;
}