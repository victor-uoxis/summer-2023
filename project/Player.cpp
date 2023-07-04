#include "includes.h"
#include "Player.h"

Player::Player()
{
	this->initTExture();
	this->initSprite();
}

Player::~Player()
{
}

void Player::update()
{
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}

void Player::initSprite()
{
}

void Player::initTExture()
{
}
