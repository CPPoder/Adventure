#ifndef BALL_HPP
#define BALL_HPP

#include "SFML\Graphics.hpp"

#include "Source\Collision\CollisionArea.hpp"


namespace Magic
{
	enum class Type
	{
		FIRE,


		NUM_OF_TYPES
	};



	class Ball
	{
	private:
		Type mType;
		sf::Vector2f mVelocity;
		float mDamage;

		CollisionArea mCollisionArea;


	public:
		Ball(sf::Vector2f const & velocity, float damage, Type type);
		virtual ~Ball();

		virtual void render(sf::RenderWindow* renderWindow) = 0;
		virtual void update(sf::Time const & frametime, sf::RenderWindow const * renderWindow) = 0;

		Type getType() const;
		sf::Vector2f getVelocity() const;
		float getDamage() const;



	};



} //Namespace Magic



#endif //BALL_HPP

