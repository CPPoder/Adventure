#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Source\Animation\Animation.hpp"

#include "SFML\Graphics.hpp"


class Player
{
private:
	Animation mPlayerAnimation;

public:
	Player();
	~Player();

	void update(sf::Time const & frametime, sf::RenderWindow const * renderWindow);
	void render(sf::RenderWindow* renderWindow);




};





#endif //PLAYER_HPP

