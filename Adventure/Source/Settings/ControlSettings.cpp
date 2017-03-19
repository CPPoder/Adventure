#include "stdafx.h"
#include "Source\Settings\ControlSettings.hpp"


namespace Settings
{

	ControlSettings::KeySet ControlSettings::getKeySetOfAction(Action action)
	{
		return sMapOfKeySets.at(action);
	}
	bool ControlSettings::checkIfKeyBelongsToAction(sf::Keyboard::Key key, Action action)
	{
		return (getKeySetOfAction(action).count(key) != 0);
	}
	bool ControlSettings::checkIfSomeKeyOfActionIsPressed(Action action)
	{
		ControlSettings::KeySet keySet(getKeySetOfAction(action));
		for (auto key : keySet)
		{
			if (sf::Keyboard::isKeyPressed(key))
			{
				return true;
			}
		}
		return false;
	}


	std::map<ControlSettings::Action, ControlSettings::KeySet> ControlSettings::sMapOfKeySets = std::map<ControlSettings::Action, ControlSettings::KeySet>
		{
			std::make_pair(ControlSettings::Action::CHANGE_FPS_VISIBILITY,	ControlSettings::KeySet({ sf::Keyboard::Key::Tab })),
			std::make_pair(ControlSettings::Action::WALK_UP,				ControlSettings::KeySet({ sf::Keyboard::Key::Up, sf::Keyboard::Key::W })),
			std::make_pair(ControlSettings::Action::WALK_LEFT,				ControlSettings::KeySet({ sf::Keyboard::Key::Left, sf::Keyboard::Key::A })),
			std::make_pair(ControlSettings::Action::WALK_DOWN,				ControlSettings::KeySet({ sf::Keyboard::Key::Down, sf::Keyboard::Key::S })),
			std::make_pair(ControlSettings::Action::WALK_RIGHT,				ControlSettings::KeySet({ sf::Keyboard::Key::Right, sf::Keyboard::Key::D })),
			std::make_pair(ControlSettings::Action::ATTACK,					ControlSettings::KeySet({ sf::Keyboard::Key::Space }))
		};

}

