#ifndef WOLF_HPP
#define WOLF_HPP

#include "Source\Game\Enemies\Enemy.hpp"
#include "Source\Animation\Animation.hpp"
#include "Source\Collision\CollisionArea.hpp"
#include "Source\Game\Enemies\WolfStates.hpp"
#include "Source\Game\Enemies\WolfBrain.hpp"


namespace Enemy
{

	class Wolf : public Enemy
	{
	private:
		static const float sPixelPerJumpStep;

		static const sf::Vector2f sSizeOfWolfTextRect;
		static const Animation::TextRectPositions sWolfAnimTextRectPositions;

		static const Animation::AnimProgram sAnimProgramOfStandingRight;
		static const Animation::AnimProgram sAnimProgramOfStandingUp;
		static const Animation::AnimProgram sAnimProgramOfStandingLeft;
		static const Animation::AnimProgram sAnimProgramOfStandingDown;
		static const Animation::AnimProgram sAnimProgramOfWalkingRight;
		static const Animation::AnimProgram sAnimProgramOfWalkingUp;
		static const Animation::AnimProgram sAnimProgramOfWalkingLeft;
		static const Animation::AnimProgram sAnimProgramOfWalkingDown;


		WolfState mWolfState = WolfState::STANDING;
		WolfDirection mWolfDirection = WolfDirection::DOWN;
		WolfAnimationName mWolfAnimationName;
		Animation mWolfAnimation;

		CollisionArea mWolfCollisionArea;

		WolfBrain mWolfBrain;




	public:
		Wolf() = delete;
		Wolf(sf::Vector2f const & position);
		Wolf(Wolf const &) = delete;
		Wolf& operator=(Wolf const &) = delete;

		virtual ~Wolf() override = default;

		virtual void update(sf::Time const & frametime, sf::RenderWindow const * renderWindow, TileMap const & tileMap) override;
		virtual void render(sf::RenderWindow* renderWindow) override;

		virtual void moveObjects(sf::Vector2f const & movement) override;
		virtual void tryToMove(sf::Vector2f const & movement, TileMap const & tileMap) override;

		sf::Vector2f getPosition() const;


	private:
		void handleMovement(sf::Time const & frametime, TileMap const & tileMap);
		void setWolfStateAndDirection(WolfState wolfState, WolfDirection wolfDirection);
		void changeAnimation();
		bool checkIfCollisionOccured(TileMap const & tileMap) const;
		void undoLastMovement(sf::Vector2f const & lastMovement);


	private:
		static WolfAnimationName getWolfAnimationName(WolfState wolfState, WolfDirection wolfDirection);
		static sf::Vector2f getUnitVectorInDirection(WolfDirection direction);



	}; //Class Wolf


} //Namespace Enemy


#endif //WOLF_HPP

