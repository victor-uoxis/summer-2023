#include "includes.h"
#include "Player.h"

enum ANIM_STATE {
	idle = 0,
	left,
	right,
	jump,
	air,
	ground_attack,
	air_attack
};

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

void Player::update()
{
	move();
	updateAnimations();
	updatePhysics();
}

void Player::move()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
		moveVector(-5.f, 0.f);
		sprite.setScale(-4.f, 4.f);
		animState = ANIM_STATE::left;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
		moveVector(5.f, 0.f);
		sprite.setScale(4.f, 4.f);
		animState = ANIM_STATE::right;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
		moveVector(0.f, 5.f);
		animState = ANIM_STATE::air;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
		moveVector(0.f, -5.f);
	}
	else
		animState = ANIM_STATE::idle;
}

void Player::updateAnimations()
{
	if (animState == ANIM_STATE::idle) {
		frame.top = 0;
		if (animationTimer.getElapsedTime().asSeconds() >= .5f) {
			frame.left += 60;
			if (frame.left > 60)
				frame.left = 0;

			animationTimer.restart();
			sprite.setTextureRect(frame);
		}
	}
	else if (animState == ANIM_STATE::right) {
		frame.top = 105;
		if (animationTimer.getElapsedTime().asSeconds() >= .2f) {
			frame.left += 60;
			if (frame.left > 300)
				frame.left = 0;

			animationTimer.restart();
			sprite.setTextureRect(frame);
		}
	}
	else if (animState == ANIM_STATE::left) {
		frame.top = 105;
		if (animationTimer.getElapsedTime().asSeconds() >= .2f) {
			frame.left += 60;
			if (frame.left > 300)
				frame.left = 0;

			animationTimer.restart();
			sprite.setTextureRect(frame);
		}
	}
	else
		animationTimer.restart();
}

void Player::moveVector(const float x, const float y)
{
	velocity.x += x * accel;
	velocity.y += y * accel;

	if (std::abs(velocity.x) > maxVelocity) {
		velocity.x = velocity.x < 0 ? -maxVelocity : maxVelocity;
	}
	if (std::abs(velocity.y) > maxVelocity) {
		velocity.y = velocity.y < 0 ? -maxVelocity : maxVelocity;
	}
}

void Player::updatePhysics()
{
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
}

void Player::initPhysics()
{
	maxVelocity = 10.f;
	minVelocity = 1.f;
	accel = 3.f;
	drag = .98f;
}