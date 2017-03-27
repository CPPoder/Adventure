#ifndef WOLFSTATES_HPP
#define WOLFSTATES_HPP


namespace Enemy
{

	enum class WolfState
	{
		STANDING,
		WALKING
	};


	enum class WolfDirection
	{
		RIGHT,
		RIGHT_UP,
		UP,
		UP_LEFT,
		LEFT,
		LEFT_DOWN,
		DOWN,
		DOWN_RIGHT
	};


	enum class WolfAnimationName
	{
		STANDING_RIGHT,
		STANDING_UP,
		STANDING_LEFT,
		STANDING_DOWN,
		WALKING_RIGHT,
		WALKING_UP,
		WALKING_LEFT,
		WALKING_DOWN
	};


	struct WolfMovement
	{
	public:
		WolfState wolfState;
		WolfDirection wolfDirection;

	public:
		WolfMovement() = delete;
		WolfMovement(WolfMovement const &) = default;
		WolfMovement& operator=(WolfMovement const &) = default;
		WolfMovement(WolfState _wolfState, WolfDirection _wolfDirection) : wolfState(_wolfState), wolfDirection(_wolfDirection) {};
		~WolfMovement() = default;

	};


} //Namespace Enemy




#endif //WOLFSTATES_HPP

