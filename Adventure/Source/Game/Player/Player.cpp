#include "stdafx.h"
#include "Source\Game\Player\Player.hpp"



Player::Player()
	: mPlayerAnimation(TextureManager::TextureName::PLAYER_TEXTURE_ATLAS, { {0.f, 0.f} , { 32.f, 0.f } , { 64.f, 0.f } , {96.f, 0.f} }, sf::Vector2f(32.f, 64.f), {0u, 1u, 2u, 3u}, 0u, sf::seconds(0.1f), sf::Vector2f(200.f, 200.f))
{

}
Player::~Player()
{

}

void Player::update(sf::Time const & frametime, sf::RenderWindow const * renderWindow)
{
	mPlayerAnimation.update(frametime, renderWindow);
}
void Player::render(sf::RenderWindow* renderWindow)
{
	mPlayerAnimation.render(renderWindow);
}

