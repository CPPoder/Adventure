#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Source\Animation\Animation.hpp"
#include "Source\Collision\CollisionArea.hpp"
#include "Source\Tile\TileMap.hpp"

#include "SFML\Graphics.hpp"

#include "myUsefulMath.hpp"
#include "mySFMLVectorFunctions.hpp"


enum class PlayerState
{
	STANDING,
	WALKING
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
	WALKING_DOWN
};


class Player
{
private:
	float const mVelocity = 150.f;
	float const mPixelPerStep = 20.f;

	sf::Vector2f const mSizeOfPlayerTextRect = sf::Vector2f(32.f, 64.f);
	Animation::TextRectPositions const mPlayerAnimTextRectPositions = { 
		{ 0.f, 0.f },		{ 32.f, 0.f },		{ 64.f, 0.f },		//Right
		{ 0.f, 64.f },		{ 32.f, 64.f },		{ 64.f, 64.f },		//Up
		{ 0.f, 128.f },		{ 32.f, 128.f },	{ 64.f, 128.f },	//Left
		{ 0.f, 192.f },		{ 32.f, 192.f },	{ 64.f, 192.f }		//Down
	};
	Animation::AnimProgram const mAnimProgramOfStandingRight	=	{ 0u };
	Animation::AnimProgram const mAnimProgramOfStandingUp		=	{ 3u };
	Animation::AnimProgram const mAnimProgramOfStandingLeft		=	{ 6u };
	Animation::AnimProgram const mAnimProgramOfStandingDown		=	{ 9u };
	Animation::AnimProgram const mAnimProgramOfWalkingRight		=	{ 1u, 0u, 2u, 0u };
	Animation::AnimProgram const mAnimProgramOfWalkingUp		=	{ 4u, 3u, 5u, 3u };
	Animation::AnimProgram const mAnimProgramOfWalkingLeft		=	{ 7u, 6u, 8u, 6u };
	Animation::AnimProgram const mAnimProgramOfWalkingDown		=	{ 10u, 9u, 11u, 9u };

	PlayerState mPlayerState = PlayerState::STANDING;
	PlayerDirection mPlayerDirection = PlayerDirection::RIGHT;
	PlayerAnimationName mPlayerAnimationName;
	Animation mPlayerAnimation;
	sf::CircleShape mPlayerShadow;

	CollisionArea mPlayerCollisionArea;
	

public:
	Player(sf::Vector2f const & position);
	~Player();

	void update(sf::Time const & frametime, sf::RenderWindow const * renderWindow, TileMap const & tileMap);
	void render(sf::RenderWindow* renderWindow);

	void move(sf::Vector2f const & movement);

	sf::Vector2f getPosition() const;


private:
	void handleMovement(sf::Time const & frametime);
	void setPlayerStateAndDirection(PlayerState playerState, PlayerDirection playerDirection);
	void changeAnimation();

private:
	static PlayerAnimationName getPlayerAnimationName(PlayerState playerState, PlayerDirection playerDirection);
	static sf::Vector2f getUnitVectorInDirection(PlayerDirection direction);

};





#endif //PLAYER_HPP

