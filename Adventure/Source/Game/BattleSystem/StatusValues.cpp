#include "stdafx.h"
#include "Source\Game\BattleSystem\StatusValues.hpp"


StatusValues::StatusValues(StatValType _maxLife, StatValType _defense, StatValType _resistanceAgainstFire, StatValType _resistanceAgainstIce, StatValType _resistanceAgainstElectricity, StatValType _resistanceAgainstEarth, StatValType _resistanceAgainstAir, StatValType _speed)
	: maxLife(_maxLife),
	  defense(_defense),
	  resistanceAgainstFire(_resistanceAgainstFire),
	  resistanceAgainstIce(_resistanceAgainstIce),
	  resistanceAgainstElectricity(_resistanceAgainstElectricity),
	  resistanceAgainstEarth(_resistanceAgainstEarth),
	  resistanceAgainstAir(_resistanceAgainstAir),
	  speed(_speed)
{
}



//Static Functions
float StatusValues::convertSpeedIntoPixelPerSecond(StatValType speed)
{
	return (4.f * static_cast<float>(speed));
}
