#include "stdafx.h"
#include "Source\Framework\Framework.hpp"

//Constructor
Framework::Framework()
	: mFonts(),
	  mFPSText(*mFonts.getFont(mySFML::Class::FontName::ARIAL), sf::Vector2f(2.f, 0.f), "FPS: ", 12u, sf::Color::White),
	  mUtilizationText(*mFonts.getFont(mySFML::Class::FontName::ARIAL), sf::Vector2f(2.f, 10.f), "Util: ", 12u, sf::Color::White)
{
	srand(time(0));

	pRenderWindow = new sf::RenderWindow(sf::VideoMode(1440, 900), "Adventure");
	pRenderWindow->setFramerateLimit(60);

	mFPSClock.restart();
}

//Destructor
Framework::~Framework()
{
	delete pRenderWindow;
	pRenderWindow = nullptr;
}


//HandleEvents, Update, Render
void Framework::handleEvents()
{
	sf::Event mEvent;
	while (pRenderWindow->pollEvent(mEvent))
	{
		if (mEvent.type == sf::Event::EventType::Closed)
		{
			pRenderWindow->close();
		}
		if (mEvent.type == sf::Event::EventType::KeyReleased)
		{
			if (mEvent.key.code == sf::Keyboard::Key::Escape)
			{
				pRenderWindow->close();
			}
		}
	}
}

void Framework::update()
{

}

void Framework::render()
{
	pRenderWindow->clear(mySFML::Color::randColor());
	
	pRenderWindow->draw(*mFPSText.pointer);
	pRenderWindow->draw(*mUtilizationText.pointer);

	sf::Time timeBeforeRendering = mFPSClock.getElapsedTime();
	pRenderWindow->display();
	mRenderTimePerFrame = mFPSClock.getElapsedTime() - timeBeforeRendering;
}

//Determine FPS
void Framework::determineFrametime()
{
	static sf::Time timeSinceLastSecond(sf::seconds(0.f));
	static unsigned int framesSinceLastSecond(0u);
	static sf::Time renderTimeSinceLastSecond(sf::seconds(0.f));

	mFrametime = mFPSClock.restart();
	timeSinceLastSecond += mFrametime;
	renderTimeSinceLastSecond += mRenderTimePerFrame;
	++framesSinceLastSecond;

	if (timeSinceLastSecond > sf::seconds(1.f))
	{
		mFPS = framesSinceLastSecond;
		mFPSText.setString("FPS: " + std::to_string(mFPS));

		mUtilization = (timeSinceLastSecond - renderTimeSinceLastSecond).asSeconds();
		mUtilizationText.setString("Util: " + std::to_string(static_cast<int>(mUtilization * 100.f)) + "%");

		framesSinceLastSecond = 0u;
		timeSinceLastSecond = sf::seconds(0.f);
		renderTimeSinceLastSecond = sf::seconds(0.f);
	}
}


//Run
void Framework::run()
{
	while (pRenderWindow->isOpen())
	{
		determineFrametime();
		handleEvents();
		update();
		render();
	}
}

