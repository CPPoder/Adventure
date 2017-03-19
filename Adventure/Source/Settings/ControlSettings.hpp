#ifndef CONTROLSETTINGS_HPP
#define CONTROLSETTINGS_HPP

#include "SFML\Graphics.hpp"

#include <set>
#include <map>
#include <utility>
#include <iostream>


namespace Settings
{

	class ControlSettings
	{
	public:
		typedef std::set<sf::Keyboard::Key> KeySet;

		enum class Action
		{
			CHANGE_FPS_VISIBILITY,

			WALK_UP,
			WALK_LEFT,
			WALK_DOWN,
			WALK_RIGHT,

			ATTACK,

			NUM_OF_CONTROL_CATEGORIES
		};

	private:
		static std::map<Action, KeySet> sMapOfKeySets;

	public:
		ControlSettings() = delete;
		~ControlSettings() = delete;
		ControlSettings(ControlSettings const &) = delete;
		ControlSettings& operator=(ControlSettings const &) = delete;

		static KeySet getKeySetOfAction(Action action);
		static bool checkIfKeyBelongsToAction(sf::Keyboard::Key key, Action action);
		static bool checkIfSomeKeyOfActionIsPressed(Action action);


	}; //Class ControlSettings


} //Namespace Settings


#endif //CONTROLSETTINGS_HPP
