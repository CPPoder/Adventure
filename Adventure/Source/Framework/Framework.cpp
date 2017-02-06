#include "stdafx.h"
#include "Source\Framework\Framework.hpp"

//Constructor
Framework::Framework()
	: mFonts(),
	  mFPSText(*mFonts.getFont(mySFML::Class::FontName::ARIAL), sf::Vector2f(2.f, 0.f), "FPS: ", 12u, sf::Color::White),
	  mUtilizationText(*mFonts.getFont(mySFML::Class::FontName::ARIAL), sf::Vector2f(2.f, 10.f), "Util: ", 12u, sf::Color::White)
{
	srand(static_cast<unsigned int>(time(0)));

	pRenderWindow = new sf::RenderWindow(sf::VideoMode(1440, 900), "Adventure");
	pRenderWindow->setFramerateLimit(60);

	mFPSClock.restart();

	mStackOfGameStates.push(new GameState::MainMenuState);
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
	EventManager::reset();
	while (pRenderWindow->pollEvent(mEvent))
	{
		//Handle immediately
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
		
		//Pass the Events through to the EventManager
		if (mEvent.type == sf::Event::EventType::MouseButtonPressed)
		{
			EventManager::setPressedMouseEvent(EventManager::MouseInfo(mEvent.mouseButton.button, sf::Vector2i(mEvent.mouseButton.x, mEvent.mouseButton.y)));
		}
		if (mEvent.type == sf::Event::EventType::MouseButtonReleased)
		{
			EventManager::setReleasedMouseEvent(EventManager::MouseInfo(mEvent.mouseButton.button, sf::Vector2i(mEvent.mouseButton.x, mEvent.mouseButton.y)));
		}
		if (mEvent.type == sf::Event::EventType::KeyPressed)
		{
			EventManager::setPressedKeyEvent(EventManager::KeyInfo(mEvent.key.code, mEvent.key.control, mEvent.key.alt, mEvent.key.shift, mEvent.key.system));
		}
		if (mEvent.type == sf::Event::EventType::KeyReleased)
		{
			EventManager::setReleasedKeyEvent(EventManager::KeyInfo(mEvent.key.code, mEvent.key.control, mEvent.key.alt, mEvent.key.shift, mEvent.key.system));
		}

	}
}

void Framework::update()
{
	GameState::GameStateChange gameStateChange = mStackOfGameStates.top()->getGameStateChange();
	switch (gameStateChange)
	{
	case GameState::GameStateChange::POP:
		delete mStackOfGameStates.top();
		mStackOfGameStates.pop();
		break;

	case GameState::GameStateChange::PUSH_MAIN_MENU_STATE:
		mStackOfGameStates.push(new GameState::MainMenuState);
		break;

	case GameState::GameStateChange::PUSH_PLAYING_STATE:
		mStackOfGameStates.push(new GameState::PlayingState);
		break;

	case GameState::GameStateChange::REPLACE_MAIN_MENU_STATE:
		delete mStackOfGameStates.top();
		mStackOfGameStates.pop();
		mStackOfGameStates.push(new GameState::MainMenuState);
		break;

	case GameState::GameStateChange::REPLACE_PLAYING_STATE:
		delete mStackOfGameStates.top();
		mStackOfGameStates.pop();
		mStackOfGameStates.push(new GameState::PlayingState);
		break;
	}
	if (mStackOfGameStates.empty())
	{
		throw "Stack of GameStates is empty!";
	}

	mStackOfGameStates.top()->update(mFrametime, pRenderWindow);
}

void Framework::render()
{
	pRenderWindow->clear(sf::Color::Black);
	
	mStackOfGameStates.top()->render(pRenderWindow);
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
	try
	{
		while (pRenderWindow->isOpen())
		{
			determineFrametime();
			handleEvents();
			update();
			render();
		}
	}
	catch (char* text) //Breaks the While-Loop, if the Stack of GameStates is empty!
	{
		pRenderWindow->close();
		std::cout << text << std::endl;
	}
}

