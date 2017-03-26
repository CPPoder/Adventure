#ifndef STATUSVALUES_HPP
#define STATUSVALUES_HPP


typedef unsigned short StatValType;


class StatusValues
{
public:
	StatValType maxLife;

	StatValType defense;

	StatValType resistanceAgainstFire;
	StatValType resistanceAgainstIce;
	StatValType resistanceAgainstElectricity;
	StatValType resistanceAgainstEarth;
	StatValType resistanceAgainstAir;

	StatValType speed;

public:
	StatusValues() = delete;
	StatusValues(StatusValues const & statusValues) = default;
	StatusValues& operator=(StatusValues const &) = default;
	StatusValues(StatValType _maxLife, StatValType _defense, StatValType _resistanceAgainstFire, StatValType _resistanceAgainstIce, StatValType _resistanceAgainstElectricity, StatValType _resistanceAgainstEarth, StatValType _resistanceAgainstAir, StatValType _speed);
	~StatusValues() = default;


public:
	static float convertSpeedIntoPixelPerSecond(StatValType speed);


};



#endif //STATUSVALUES_HPP

