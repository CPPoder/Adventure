#ifndef DROPDOWNMENUSETTINGS_HPP
#define DROPDOWNMENUSETTINGS_HPP


#include "SFML\Graphics.hpp"


struct DropDownMenuSettings
{
	struct ColorSettings
	{
		//Normal Color of ActualChoiceRectangle
		sf::Color normalActualChoiceBackgroundColor;
		sf::Color normalActualChoiceOutlineColor;
		sf::Color normalActualChoiceTextColor;

		//Inactive Color of ActualChoiceRectangle
		sf::Color inactiveActualChoiceBackgroundColor;
		sf::Color inactiveActualChoiceOutlineColor;
		sf::Color inactiveActualChoiceTextColor;

		//Normal Color of DropDownRectangles
		sf::Color normalDropDownBackgroundColor;
		sf::Color normalDropDownOutlineColor;
		sf::Color normalDropDownTextColor;

		//Touched Color of DropDownRectangles
		sf::Color touchedDropDownBackgroundColor;
		sf::Color touchedDropDownOutlineColor;
		sf::Color touchedDropDownTextColor;

		ColorSettings(
			sf::Color const & _normalActualChoiceBackgroundColor,
			sf::Color const & _normalActualChoiceOutlineColor,
			sf::Color const & _normalActualChoiceTextColor,
			sf::Color const & _inactiveActualChoiceBackgroundColor,
			sf::Color const & _inactiveActualChoiceOutlineColor,
			sf::Color const & _inactiveActualChoiceTextColor,
			sf::Color const & _normalDropDownBackgroundColor,
			sf::Color const & _normalDropDownOutlineColor,
			sf::Color const & _normalDropDownTextColor,
			sf::Color const & _touchedDropDownBackgroundColor,
			sf::Color const & _touchedDropDownOutlineColor,
			sf::Color const & _touchedDropDownTextColor
		)
			: normalActualChoiceBackgroundColor(_normalActualChoiceBackgroundColor),
			normalActualChoiceOutlineColor(_normalActualChoiceOutlineColor),
			normalActualChoiceTextColor(_normalActualChoiceTextColor),
			inactiveActualChoiceBackgroundColor(_inactiveActualChoiceBackgroundColor),
			inactiveActualChoiceOutlineColor(_inactiveActualChoiceOutlineColor),
			inactiveActualChoiceTextColor(_inactiveActualChoiceTextColor),
			normalDropDownBackgroundColor(_normalDropDownBackgroundColor),
			normalDropDownOutlineColor(_normalDropDownOutlineColor),
			normalDropDownTextColor(_normalDropDownTextColor),
			touchedDropDownBackgroundColor(_touchedDropDownBackgroundColor),
			touchedDropDownOutlineColor(_touchedDropDownOutlineColor),
			touchedDropDownTextColor(_touchedDropDownTextColor)
		{}

		static const ColorSettings standardColorSettings;

	}; //Class ColorSettings

	ColorSettings colorSettings;

	DropDownMenuSettings(ColorSettings const & _colorSettings)
		: colorSettings(_colorSettings)
	{}

	static const DropDownMenuSettings standardDropDownMenuSettings;



}; //Class ButtonSettings







#endif //DROPDOWNMENUSETTINGS_HPP

