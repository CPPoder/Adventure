#include "stdafx.h"
#include "Source\ControlElements\DropDownMenu.hpp"


DropDownMenu::DropDownMenu(sf::Vector2f const & position, sf::Vector2f const & sizeOfSingleField, sf::Vector2f const & sizeOfDropMenu, std::vector<std::string> const & vectorOfChoiceTexts, mySFML::Class::FontName fontName, DropDownMenuSettings const & dropDownMenuSettings)
	: pFont(mFonts.getFont(fontName)),
	  mDropDownMenuSettings(dropDownMenuSettings),
	  mPosition(position),
	  mSizeOfSingleField(sizeOfSingleField),
	  mSizeOfDropMenu(sizeOfDropMenu),
	  mVectorOfChoiceTexts(vectorOfChoiceTexts),
	  mNumberOfChoices(vectorOfChoiceTexts.size())
{
	this->setInternalObjects();
}

DropDownMenu::~DropDownMenu()
{

}



void DropDownMenu::update(sf::Time const & frametime, sf::RenderWindow const * renderWindow)
{
	
}

void DropDownMenu::render(sf::RenderWindow * renderWindow)
{
	for (auto& rect : mVectorOfRectShapes)
	{
		renderWindow->draw(*rect.pointer);
	}
	for (auto& text : mVectorOfTexts)
	{
		renderWindow->draw(*text.pointer);
	}
}


void DropDownMenu::setPosition(sf::Vector2f const & position)
{
	mPosition = position;
	this->setInternalObjects();
}

void DropDownMenu::move(sf::Vector2f const & direction)
{
	mPosition += direction;
	this->setInternalObjects();
}

void DropDownMenu::setSizeOfSingleField(sf::Vector2f const & size)
{
	mSizeOfSingleField = size;
	this->setInternalObjects();
}

void DropDownMenu::setSizeOfDropMenu(sf::Vector2f const & size)
{
	mSizeOfDropMenu = size;
	this->setInternalObjects();
}

void DropDownMenu::setVectorOfChoiceTexts(std::vector<std::string> const & vectorOfTexts)
{
	mVectorOfChoiceTexts = vectorOfTexts;
	mNumberOfChoices = vectorOfTexts.size();
	this->setInternalObjects();
}

void DropDownMenu::addChoice(std::string const & text)
{
	mVectorOfChoiceTexts.push_back(text);
	mNumberOfChoices += 1;
	this->setInternalObjects();
}

void DropDownMenu::setActive(bool active)
{
	mIsActive = active;
	this->setInternalObjects();
}

void DropDownMenu::setCurrentChoice(unsigned int choiceNumber)
{
	mCurrentChoice = choiceNumber;
	this->setInternalObjects();
}

void DropDownMenu::setTextOfCurrentChoice(std::string const & text)
{
	mVectorOfChoiceTexts.at(mCurrentChoice) = text;
	this->setInternalObjects();
}

void DropDownMenu::setTextOfChoice(std::string const & text, unsigned int choiceNumber)
{
	mVectorOfChoiceTexts.at(choiceNumber) = text;
}



sf::Vector2f DropDownMenu::getPosition() const
{
	return mPosition;
}

sf::Vector2f DropDownMenu::getSizeOfSingleField() const
{
	return mSizeOfSingleField;
}

sf::Vector2f DropDownMenu::getSizeOfDropMenu() const
{
	return mSizeOfDropMenu;
}

bool DropDownMenu::getIsActive() const
{
	return mIsActive;
}

unsigned int DropDownMenu::getCurrentChoice() const
{
	return mCurrentChoice;
}

std::string DropDownMenu::getStringOfCurrentChoice() const
{
	return mVectorOfChoiceTexts.at(mCurrentChoice);
}

std::string DropDownMenu::getStringOfChoice(unsigned int choiceNumber) const
{
	return mVectorOfChoiceTexts.at(choiceNumber);
}



void DropDownMenu::setInternalObjects()
{
	//Check if mCurrentPositionInDropMenu is still valid
	if (mCurrentPositionInDropMenu > mNumberOfChoices * mSizeOfSingleField.y)
	{
		mCurrentPositionInDropMenu = 0.f;
	}

	//Set internal State describing variables
	mBarSizeRatio = myMath::Simple::min(mSizeOfDropMenu.y / (mNumberOfChoices * mSizeOfSingleField.y), 1.f);
	mBarPosRatio = (mCurrentPositionInDropMenu + mSizeOfSingleField.y / 2.f) / (mNumberOfChoices * mSizeOfSingleField.y);

	//Set Actually Chosen Rectangle & Text
	mVectorOfRectShapes.push_back(mySFML::Class::RectShape(this->constructActualChoiceRectPos(), mSizeOfSingleField, constructActualChoiceRectFillColor(), false, -2.f, constructActualChoiceRectOutlColor()));
	mVectorOfTexts.push_back(mySFML::Class::Text(*pFont, constructActualChoiceTextPos(), mVectorOfChoiceTexts.at(mCurrentChoice), mCharacterSize, constructActualChoiceTextColor()));

	//Set all visible Choice Rectangles & Texts
	sf::Vector2u visibilityBounds = this->getBoundsForVisibleRectangles();
	for (unsigned int i = visibilityBounds.x; i < visibilityBounds.y; ++i)
	{
		mVectorOfRectShapes.push_back(mySFML::Class::RectShape(this->constructChoiceRectPos(i), mSizeOfSingleField, this->constructChoiceRectFillColor(i), false, -1.f, this->constructChoiceRectOutlColor(i)));
		mVectorOfTexts.push_back(mySFML::Class::Text(*pFont, this->constructChoiceTextPos(i), mVectorOfChoiceTexts.at(i), mCharacterSize, this->constructChoiceTextColor(i)));
	}

	//Set Bar

}





sf::Vector2f DropDownMenu::constructActualChoiceRectPos() const
{
	return mPosition;
}
sf::Color DropDownMenu::constructActualChoiceRectFillColor() const
{
	if (mIsActive)
	{
		return mDropDownMenuSettings.colorSettings.normalActualChoiceBackgroundColor;
	}
	else
	{
		return mDropDownMenuSettings.colorSettings.inactiveActualChoiceBackgroundColor;
	}
}
sf::Color DropDownMenu::constructActualChoiceRectOutlColor() const
{
	if (mIsActive)
	{
		return mDropDownMenuSettings.colorSettings.normalActualChoiceOutlineColor;
	}
	else
	{
		return mDropDownMenuSettings.colorSettings.inactiveActualChoiceOutlineColor;
	}
}

sf::Vector2f DropDownMenu::constructActualChoiceTextPos() const
{
	sf::Text text(mVectorOfChoiceTexts.at(mCurrentChoice), *pFont, mCharacterSize);
	sf::FloatRect textBounds = text.getGlobalBounds();
	sf::Vector2f textSize = sf::Vector2f(textBounds.width, textBounds.height);
	return (mPosition + sf::Vector2f(2.f, (mSizeOfSingleField.y - textSize.y) / 2.f));
}
sf::Color DropDownMenu::constructActualChoiceTextColor() const
{
	if (mIsActive)
	{
		return mDropDownMenuSettings.colorSettings.normalActualChoiceTextColor;
	}
	else
	{
		return mDropDownMenuSettings.colorSettings.inactiveActualChoiceTextColor;
	}
}


sf::Vector2u DropDownMenu::getBoundsForVisibleRectangles() const
{
	unsigned int lowerBound = static_cast<unsigned int>(mCurrentPositionInDropMenu / mSizeOfSingleField.y);
	unsigned int upperBound = static_cast<unsigned int>((mCurrentPositionInDropMenu + mSizeOfDropMenu.y) / mSizeOfSingleField.y);
	return sf::Vector2u(myMath::Simple::trim(0u, lowerBound, mNumberOfChoices), myMath::Simple::trim(0u, upperBound, mNumberOfChoices));
}


sf::Vector2f DropDownMenu::constructChoiceRectPos(unsigned int choiceNumber) const
{

}
sf::Color DropDownMenu::constructChoiceRectFillColor(unsigned int choiceNumber) const
{
	if (mIsAnyChoiceTouched && choiceNumber == mTouchedChoice)
	{

	}
	else
	{

	}
}
sf::Color DropDownMenu::constructChoiceRectOutlColor(unsigned int choiceNumber) const
{

}

sf::Vector2f DropDownMenu::constructChoiceTextPos(unsigned int choiceNumber) const
{

}
sf::Color DropDownMenu::constructChoiceTextColor(unsigned int choiceNumber) const
{

}


