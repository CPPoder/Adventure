#ifndef FIREBALL_HPP
#define FIREBALL_HPP


#include "Source\Game\Magic\Ball.hpp"

#include "Source\Animation\Animation.hpp"


namespace Magic
{

	class FireBall : public Ball
	{
	private:
		sf::Vector2f const mSizeOfFireBallTextRect = sf::Vector2f(8.f, 7.f);
		Animation::TextRectPositions const mFireBallAnimTextRectPositions = { { 131.f, 33.f },{ 140.f, 33.f },{ 149.f, 33.f },{ 158.f, 33.f } };
		Animation::AnimProgram const mAnimProgramOfFlyingFireBall = { 0u, 1u, 2u, 3u };
		sf::Time const mAnimationTime = sf::seconds(0.04f);

		Animation mAnimation;

		sf::Time const mDuration = sf::seconds(2.f);
		sf::Time mTimeSinceCreation = sf::Time::Zero;

	public:
		FireBall(sf::Vector2f const & position, sf::Vector2f const & velocity, float damage);
		virtual ~FireBall() override;

		virtual void render(sf::RenderWindow* renderWindow) override;
		virtual void update(sf::Time const & frametime, sf::RenderWindow const * renderWindow) override;

		bool getDurationExceeded() const;


	};


} //Namespace Magic






#endif //FIREBALL_HPP

