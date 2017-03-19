#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Source\Animation\Animation.hpp"
#include "Source\Collision\CollisionArea.hpp"
#include "Source\Tile\TileMap.hpp"
#include "Source\Game\Magic\FireBall.hpp"

#include "Source\Framework\SoundManager.hpp"

#include "Source\Settings\ControlSettings.hpp"

#include "SFML\Graphics.hpp"

#include "myUsefulMath.hpp"
#include "mySFMLVectorFunctions.hpp"


enum class PlayerState
{
	STANDING,
	WALKING,
	SHOOT_FIRE_BALL
};

enum class PlayerDirection
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

enum class PlayerAnimationName
{
	STANDING_RIGHT,
	STANDING_UP,
	STANDING_LEFT,
	STANDING_DOWN,
	WALKING_RIGHT,
	WALKING_UP,
	WALKING_LEFT,
	WALKING_DOWN,

	SHOOT_FIRE_BALL_RIGHT,
	SHOOT_FIRE_BALL_UP,
	SHOOT_FIRE_BALL_LEFT,
	SHOOT_FIRE_BALL_DOWN
};


class Player
{
private:
	float const mVelocity = 150.f;
	float const mPixelPerStep = 20.f;

	sf::Vector2f const mSizeOfPlayerTextRect = sf::Vector2f(32.f, 64.f);
	Animation::TextRectPositions const mPlayerAnimTextRectPositions = { 
		{ 0.f, 0.f },		{ 32.f, 0.f },		{ 64.f, 0.f },		{ 96.f, 0.f },		//Right
		{ 0.f, 64.f },		{ 32.f, 64.f },		{ 64.f, 64.f },		{ 96.f, 64.f },		//Up
		{ 0.f, 128.f },		{ 32.f, 128.f },	{ 64.f, 128.f },	{ 96.f, 128.f },	//Left
		{ 0.f, 192.f },		{ 32.f, 192.f },	{ 64.f, 192.f },	{ 96.f, 192.f }		//Down
	};
	Animation::AnimProgram const mAnimProgramOfStandingRight	=	{ 0u };
	Animation::AnimProgram const mAnimProgramOfStandingUp		=	{ 4u };
	Animation::AnimProgram const mAnimProgramOfStandingLeft		=	{ 8u };
	Animation::AnimProgram const mAnimProgramOfStandingDown		=	{ 12u };
	Animation::AnimProgram const mAnimProgramOfWalkingRight		=	{ 1u, 0u, 2u, 0u };
	Animation::AnimProgram const mAnimProgramOfWalkingUp		=	{ 5u, 4u, 6u, 4u };
	Animation::AnimProgram const mAnimProgramOfWalkingLeft		=	{ 9u, 8u, 10u, 8u };
	Animation::AnimProgram const mAnimProgramOfWalkingDown		=	{ 13u, 12u, 14u, 12u };
	Animation::AnimProgram const mAnimProgramOfShootingFireBallRight = { 3u };
	Animation::AnimProgram const mAnimProgramOfShootingFireBallUp = { 7u };
	Animation::AnimProgram const mAnimProgramOfShootingFireBallLeft = { 11u };
	Animation::AnimProgram const mAnimProgramOfShootingFireBallDown = { 15u };


	PlayerState mPlayerState = PlayerState::STANDING;
	PlayerDirection mPlayerDirection = PlayerDirection::RIGHT;
	PlayerAnimationName mPlayerAnimationName;
	Animation mPlayerAnimation;
	sf::CircleShape mPlayerShadow;

	CollisionArea mPlayerCollisionArea;

	sf::Clock mHitBorderSoundClock;
	sf::Time const mHitBorderSoundTime = sf::seconds(0.4f);

	sf::Clock mActualStateClock;
	sf::Time const mTimeToShootFireBall = sf::seconds(0.15f);
	sf::Time const mFireBallCoolDown = sf::seconds(0.5f);
	sf::Clock mFireBallCoolDownClock;
	std::list<Magic::FireBall*> mListOfFireBalls;
	

public:
	Player(sf::Vector2f const & position);
	~Player();

	void update(sf::Time const & frametime, sf::RenderWindow const * renderWindow, TileMap const & tileMap);
	void render(sf::RenderWindow* renderWindow);

	void moveObjects(sf::Vector2f const & movement);
	void tryToMove(sf::Vector2f const & movement, TileMap const & tileMap);

	sf::Vector2f getPosition() const;

	std::list<Magic::FireBall*>& getAccessToListOfFireBalls();


private:
	void handleMovement(sf::Time const & frametime, TileMap const & tileMap);
	void handleFireBallCreation();
	void setPlayerStateAndDirection(PlayerState playerState, PlayerDirection playerDirection);
	void changeAnimation();
	bool checkIfCollisionOccured(TileMap const & tileMap) const;
	void undoLastMovement(sf::Vector2f const & lastMovement);

	sf::Vector2f calculateFireBallPosition() const;
	sf::Vector2f calculateFireBallVelocity() const;
	float calculateFireBallDamage() const;


private:
	static PlayerAnimationName getPlayerAnimationName(PlayerState playerState, PlayerDirection playerDirection);
	static sf::Vector2f getUnitVectorInDirection(PlayerDirection direction);

};





#endif //PLAYER_HPP

