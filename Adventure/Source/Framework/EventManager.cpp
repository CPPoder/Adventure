#include "stdafx.h"
#include "Source\Framework\EventManager.hpp"

////////
//Getter

bool EventManager::checkForEvent(EventType eventType)
{
	switch (eventType)
	{
	case EventType::KEY_PRESSED:
		return mIsKeyPressed;
	case EventType::KEY_RELEASED:
		return mIsKeyReleased;
	case EventType::MOUSE_WHEEL_SCROLLED:
		return mIsMouseWheelScrolled;
	case EventType::MOUSE_PRESSED:
		return mIsMousePressed;
	case EventType::MOUSE_RELEASED:
		return mIsMouseReleased;
	case EventType::TEXT_ENTERED:
		return mIsTextEntered;
	}
}

EventManager::MouseInfo EventManager::getPressedMouseInfo()
{
	return EventManager::MouseInfo(mPressedMouseButton, mPressedMousePosition);
}
EventManager::MouseInfo EventManager::getReleasedMouseInfo()
{
	return EventManager::MouseInfo(mReleasedMouseButton, mReleasedMousePosition);
}
EventManager::MouseWheelInfo EventManager::getMouseWheelScrolledInfo()
{
	return EventManager::MouseWheelInfo(mMouseWheelScrolledDelta, MMouseWheelScrolledPosition);
}
EventManager::KeyInfo EventManager::getPressedKeyInfo()
{
	return EventManager::KeyInfo(mPressedKey, mPressedKeyWithControl, mPressedKeyWithAlt, mPressedKeyWithShift, mPressedKeyWithSystem);
}
EventManager::KeyInfo EventManager::getReleasedKeyInfo()
{
	return EventManager::KeyInfo(mReleasedKey, mReleasedKeyWithControl, mReleasedKeyWithAlt, mReleasedKeyWithShift, mReleasedKeyWithSystem);
}
std::string EventManager::getTextEnteredText(TextMode textMode)
{
	switch (textMode)
	{
	case TextMode::UNFILTERED:
		return mText;
	case TextMode::FILTER_FOR_ASCII:
	{
		std::string string;
		for (sf::String::ConstIterator it = mText.begin(); it != mText.end(); ++it)
		{
			if (*it < 128)
			{
				string.push_back(static_cast<char>(*it));
			}
		}
		return string;
	}
	case TextMode::FILTER_FOR_PRINTABLE_ASCII:
	{
		std::string string;
		for (sf::String::ConstIterator it = mText.begin(); it != mText.end(); ++it)
		{
			if (*it < 128 && *it > 31 && *it != 127)
			{
				string.push_back(static_cast<char>(*it));
			}
		}
		return string;
	}
	}
}



////////
//Setter

void EventManager::reset()
{
	mIsKeyPressed = false;
	mIsKeyReleased = false;
	mIsMouseWheelScrolled = false;
	mIsMousePressed = false;
	mIsMouseReleased = false;
	mIsTextEntered = false;
	mText = "";
}
void EventManager::setPressedMouseEvent(EventManager::MouseInfo mouseInfo)
{
	mIsMousePressed = true;
	mPressedMouseButton = mouseInfo.button;
	mPressedMousePosition = mouseInfo.position;
}
void EventManager::setReleasedMouseEvent(EventManager::MouseInfo mouseInfo)
{
	mIsMouseReleased = true;
	mReleasedMouseButton = mouseInfo.button;
	mReleasedMousePosition = mouseInfo.position;
}
void EventManager::setMouseWheelScrolledEvent(EventManager::MouseWheelInfo mouseWheelInfo)
{
	mIsMouseWheelScrolled = true;
	mMouseWheelScrolledDelta = mouseWheelInfo.delta;
	MMouseWheelScrolledPosition = mouseWheelInfo.position;
}
void EventManager::setPressedKeyEvent(EventManager::KeyInfo keyInfo)
{
	mIsKeyPressed = true;
	mPressedKey = keyInfo.key;
	mPressedKeyWithControl = keyInfo.control;
	mPressedKeyWithAlt = keyInfo.alt;
	mPressedKeyWithShift = keyInfo.shift;
	mPressedKeyWithSystem = keyInfo.system;

}
void EventManager::setReleasedKeyEvent(EventManager::KeyInfo keyInfo)
{
	mIsKeyReleased = true;
	mReleasedKey = keyInfo.key;
	mReleasedKeyWithControl = keyInfo.control;
	mReleasedKeyWithAlt = keyInfo.alt;
	mReleasedKeyWithShift = keyInfo.shift;
	mReleasedKeyWithSystem = keyInfo.system;
}
void EventManager::setTextEnteredEvent(sf::String const & text)
{
	mIsTextEntered = true;
	mText += text;
}





///////////////////////////////////
//Initialize Static Membervariables

//Mouse Pressed
bool				EventManager::mIsMousePressed				=	false;
sf::Mouse::Button	EventManager::mPressedMouseButton			=	sf::Mouse::Button::Left;
sf::Vector2i		EventManager::mPressedMousePosition			=	sf::Vector2i();

//Mouse Released
bool				EventManager::mIsMouseReleased				=	false;
sf::Mouse::Button	EventManager::mReleasedMouseButton			=	sf::Mouse::Button::Left;
sf::Vector2i		EventManager::mReleasedMousePosition		=	sf::Vector2i();


//Mouse Wheel Scrolled
bool				EventManager::mIsMouseWheelScrolled			=	false;
float				EventManager::mMouseWheelScrolledDelta		=	0.f;
sf::Vector2i		EventManager::MMouseWheelScrolledPosition	=	sf::Vector2i();


//KeyPressed
bool				EventManager::mIsKeyPressed					=	false;
sf::Keyboard::Key	EventManager::mPressedKey					=	sf::Keyboard::Key::A;
bool				EventManager::mPressedKeyWithControl		=	false;
bool				EventManager::mPressedKeyWithAlt			=	false;
bool				EventManager::mPressedKeyWithShift			=	false;
bool				EventManager::mPressedKeyWithSystem			=	false;

//KeyReleased
bool				EventManager::mIsKeyReleased				=	false;
sf::Keyboard::Key	EventManager::mReleasedKey					=	sf::Keyboard::Key::A;
bool				EventManager::mReleasedKeyWithControl		=	false;
bool				EventManager::mReleasedKeyWithAlt			=	false;
bool				EventManager::mReleasedKeyWithShift			=	false;
bool				EventManager::mReleasedKeyWithSystem		=	false;

//TextEntered
bool				EventManager::mIsTextEntered				=	false;
sf::String			EventManager::mText							=	"";
