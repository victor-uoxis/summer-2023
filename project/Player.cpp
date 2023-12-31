#include "includes.h"
#include "Player.h"

Player::Player()
{
	initVar();
	initTexture();
	initSprite();
	initAnimations();
	initPhysics();
}

Player::~Player()
{
}

const bool& Player::getAnimSwitch()
{
	bool tmp = animSwitch;

	if (tmp)
		animSwitch = false;

	return tmp;
}

const sf::Vector2f Player::getPosition() const
{
	return sprite.getPosition();
}

const sf::FloatRect Player::getBounds() const
{
	return sprite.getGlobalBounds();
}

void Player::resetGravity()
{
	velocity.y = 0.f;
}

void Player::setPosition(const float x, const float y)
{
	sprite.setPosition(x, y);
}

void Player::update()
{
	move();
	updateAnimations();
	updatePhysics();
}

void Player::move()
{
	if (animState != ANIM_STATE::air && animState != ANIM_STATE::air_attack)
		animState = ANIM_STATE::idle;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
		moveVector(-1.f, 0.f);
		sprite.setScale(-4.f, 4.f);
		if (animState != ANIM_STATE::air && animState != ANIM_STATE::air_attack)
			animState = ANIM_STATE::left;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
		moveVector(1.f, 0.f);
		sprite.setScale(4.f, 4.f);
		if (animState != ANIM_STATE::air && animState != ANIM_STATE::air_attack)
			animState = ANIM_STATE::right;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		if (jumpDelay.getElapsedTime().asSeconds() >= 0.5f && !jumped)
		{
			jumped = true;
			moveVector(0.f, -15.f);
			animState = ANIM_STATE::air;
			jumpDelay.restart();
		}
	}
}

void Player::setGrounded()
{
	animState = ANIM_STATE::idle;
	jumped = false;
}

void Player::resetAnimTimer()
{
	animationTimer.restart();
	animSwitch = true;
}

void Player::updateAnimations()
{
	if (animState == ANIM_STATE::idle) {
		frame.top = 0;
		if (animationTimer.getElapsedTime().asSeconds() >= .5f || getAnimSwitch()) {
			frame.left += 60;
			if (frame.left > 60)
				frame.left = 0;

			animationTimer.restart();
			sprite.setTextureRect(frame);
		}
	}
	else if (animState == ANIM_STATE::right) {
		frame.top = 105;
		if (animationTimer.getElapsedTime().asSeconds() >= .2f || getAnimSwitch()) {
			frame.left += 60;
			if (frame.left > 300)
				frame.left = 0;

			animationTimer.restart();
			sprite.setTextureRect(frame);
		}
	}
	else if (animState == ANIM_STATE::left) {
		frame.top = 105;
		if (animationTimer.getElapsedTime().asSeconds() >= .2f || getAnimSwitch()) {
			frame.left += 60;
			if (frame.left > 300)
				frame.left = 0;

			animationTimer.restart();
			sprite.setTextureRect(frame);
		}
	}
	else if (animState == ANIM_STATE::air) {
		frame.top = 35;
		if (velocity.y >= 0)
			frame.left = 60;
		else
			frame.left = 0;
		sprite.setTextureRect(frame);
	}
	else
		animationTimer.restart();
}

void Player::moveVector(const float x, const float y)
{
	velocity.x += x * accel;
	velocity.y += y * accel;

	if (std::abs(velocity.x) >= maxVelocity) {
		velocity.x = velocity.x < 0 ? -maxVelocity : maxVelocity;
	}
}

void Player::updatePhysics()
{
	velocity.y += 1.0 * gravity;
	if (animState != ANIM_STATE::air && animState != ANIM_STATE::air_attack) {
		if (std::abs(velocity.y) >= gravityMax) {
			velocity.y = velocity.y < 0 ? -gravityMax : gravityMax;
		}
	}
	velocity *= drag;
	if (std::abs(velocity.x) <= minVelocity) {
		velocity.x = 0.f;
	}
	if (std::abs(velocity.y) <= minVelocity) {
		velocity.y = 0.f;
	}

	sprite.move(velocity);
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(sprite);
}

void Player::initVar()
{
	animState = ANIM_STATE::idle;
}

void Player::initSprite()
{
	sprite.setTexture(texture);
	frame = sf::IntRect(0, 0, 40, 35);
	sprite.setTextureRect(frame);
	sprite.setScale(4.f, 4.f);
	sprite.setOrigin(frame.width / 2, frame.height / 2);
	sprite.setPosition(400, 300);
}

void Player::initTexture()
{
	if (!texture.loadFromFile("Images/PlayerSheet.png")) {
		std::cerr << "ERROR::Player.cpp::Could not load player texture" << "\n";
		exit(1);
	}
}

void Player::initAnimations()
{
	animationTimer.restart();
	animSwitch = true;
}

void Player::initPhysics()
{
	maxVelocity = 10.f;
	minVelocity = 1.f;
	accel = 2.f;
	drag = .9f;
	gravity = 1.2f;
	gravityMax = 15.f;
	jumpDelay.restart();
}