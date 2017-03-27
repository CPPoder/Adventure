#ifndef WOLFBRAIN_HPP
#define WOLFBRAIN_HPP

#include "Source\Game\Enemies\WolfStates.hpp"


namespace Enemy
{

	enum class WolfMovementBehaviour
	{
		STATIC,
		RANDOM,
		PATH_FOLLOWING,
		ATTACKING
	};

	struct WolfMovementInput
	{

	};


	class WolfBrain
	{
	private:
		WolfMovementBehaviour mMovementBehaviour;
		WolfMovementInput mWolfMovementInput;


	public:
		WolfBrain() = delete;
		WolfBrain(WolfBrain const &) = delete;
		WolfBrain& operator=(WolfBrain const &) = delete;
		WolfBrain(WolfMovementBehaviour movementBehaviour);
		~WolfBrain() = default;

		WolfMovementBehaviour getMovementBehaviour() const;

		void setMovementBehaviour(WolfMovementBehaviour movementBehaviour);

		WolfMovement getNextWolfMovement(WolfMovementInput const & wolfMovementInput) const;



	};





} //Namespace Enemy





#endif //BRAIN_HPP

