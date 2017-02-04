#ifndef FRAMEWORK_HPP
#define FRAMEWORK_HPP

#include <iostream>
#include "SFML\Graphics.hpp"

#include "mySFMLVectorFunctions.hpp"


class Framework
{
private:
	//RenderWindow
	sf::RenderWindow *pRenderWindow;

	//Fonts
	mySFML::Class::Fonts mFonts;

	//Frametime & Utilization
	sf::Clock mFPSClock;
	sf::Time mFrametime = sf::seconds(0.f);
	sf::Time mRenderTimePerFrame = sf::seconds(0.f);
	unsigned int mFPS = 0;
	float mUtilization = 0.f;
	mySFML::Class::Text mFPSText;
	mySFML::Class::Text mUtilizationText;

private:
	void determineFrametime();
	void handleEvents();
	void update();
	void render();


public:
	Framework();
	~Framework();

	void run();

};



#endif