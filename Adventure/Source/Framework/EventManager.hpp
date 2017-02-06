#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP

#include "SFML\Graphics.hpp"

#include <iostream>


class EventManager
{
public:
	enum class EventType
	{
		MOUSE_PRESSED,
		MOUSE_RELEASED,
		KEY_PRESSED,
		KEY_RELEASED,

		NUM_OF_EVENT_TYPES
	};

	struct MouseInfo
	{
		sf::Mouse::Button button;
		sf::Vector2i position;

		MouseInfo(sf::Mouse::Button const & _button, sf::Vector2i const & _position)
			: button(_button), position(_position)
		{
		}
	};

	struct KeyInfo
	{
		sf::Keyboard::Key key;
		bool control;
		bool alt;
		bool shift;
		bool system;

		KeyInfo(sf::Keyboard::Key const & _key, bool _control, bool _alt, bool _shift, bool _system)
			: key(_key), control(_control), alt(_alt), shift(_shift), system(_system)
		{
		}
	};


private:
	//Mouse Pressed
	static bool					mIsMousePressed;
	static sf::Mouse::Button	mPressedMouseButton;
	static sf::Vector2i			mPressedMousePosition;

	//Mouse Released
	static bool					mIsMouseReleased;
	static sf::Mouse::Button	mReleasedMouseButton;
	static sf::Vector2i			mReleasedMousePosition;


	//KeyPressed
	static bool					mIsKeyPressed;
	static sf::Keyboard::Key	mPressedKey;
	static bool					mPressedKeyWithControl;
	static bool					mPressedKeyWithAlt;
	static bool					mPressedKeyWithShift;
	static bool					mPressedKeyWithSystem;

	//KeyReleased
	static bool					mIsKeyReleased;
	static sf::Keyboard::Key	mReleasedKey;
	static bool					mReleasedKeyWithControl;
	static bool					mReleasedKeyWithAlt;
	static bool					mReleasedKeyWithShift;
	static bool					mReleasedKeyWithSystem;


public:
	//Delete Constructors, since EventManager is not meant to be instantiated!
	EventManager() = delete;
	~EventManager() = delete;
	EventManager(EventManager const &) = delete;
	EventManager& operator=(EventManager const &) = delete;


	////////
	//Getter

	static bool checkForEvent(EventType eventType);
	static MouseInfo getPressedMouseInfo();
	static MouseInfo getReleasedMouseInfo();
	static KeyInfo getPressedKeyInfo();
	static KeyInfo getReleasedKeyInfo();


	////////
	//Setter

	static void reset();
	static void setPressedMouseEvent(MouseInfo mouseInfo);
	static void setReleasedMouseEvent(MouseInfo mouseInfo);
	static void setPressedKeyEvent(KeyInfo keyInfo);
	static void setReleasedKeyEvent(KeyInfo keyInfo);



};




#endif //EVENTMANAGER_HPP

