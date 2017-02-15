#include "stdafx.h"
#include "Source\ControlElements\DropDownMenuSettings.hpp"

const DropDownMenuSettings::ColorSettings DropDownMenuSettings::ColorSettings::standardColorSettings = DropDownMenuSettings::ColorSettings
(
	//Normal of ActualChoice
	sf::Color(100, 100, 100),	//Background
	sf::Color(0, 0, 0),			//Outline
	sf::Color(20, 20, 20),		//Text

	//Inactive of ActualChoice
	sf::Color(50, 50, 50),
	sf::Color(0, 0, 0),
	sf::Color(20, 20, 20),

	//Normal of DropDown
	sf::Color(100, 100, 100),
	sf::Color(0, 0, 0),
	sf::Color(20, 20, 20),

	//Touched of DropDown
	sf::Color(130, 130, 130),
	sf::Color(30, 30, 30),
	sf::Color(50, 50, 50)
);

const DropDownMenuSettings DropDownMenuSettings::standardDropDownMenuSettings = DropDownMenuSettings(DropDownMenuSettings::ColorSettings::standardColorSettings);

