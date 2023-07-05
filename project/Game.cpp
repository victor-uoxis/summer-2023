#include "includes.h"
#include "Game.h"

Game::Game()
{
	initWindow();
	initPlayer();
}

Game::~Game()
{
	delete player;
}

void Game::updateCollisions()
{
	if (player->getPosition().y + player->getBounds().height >= window.getSize().y) {
		player->resetGravity();
		player->setPosition(player->getPosition().x,
			window.getSize().y - player->getBounds().height / 2);
	}
}

void Game::update()
{
	while (window.isOpen()) {
		while (this->window.pollEvent(this->event)) {
			if (this->event.type == sf::Event::Closed)
				this->window.close();
			if (event.type == sf::Event::KeyReleased &&
				(event.key.code == sf::Keyboard::Up ||
					event.key.code == sf::Keyboard::Down ||
					event.key.code == sf::Keyboard::Left ||
					event.key.code == sf::Keyboard::Right))
				player->resetAnimTimer();
			updatePlayer();
		}
		updatePlayer();
		updateCollisions();
		render();
	}
}

void Game::render()
{
	window.clear();

	// Render game and shit
	renderPlayer();

	window.display();
}

void Game::renderPlayer()
{
	player->render(window);
}

const sf::RenderWindow& Game::getWindow() const
{
	return this->window;
}

void Game::updatePlayer()
{
	player->update();
}

void Game::initWindow()
{
	this->window.create(sf::VideoMode(800, 600), "It's aliiiive", sf::Style::Close | sf::Style::Titlebar);
	window.setFramerateLimit(60);
}

void Game::initPlayer()
{
	this->player = new Player();
}
