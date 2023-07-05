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

void Game::update()
{
	while (this->window.pollEvent(this->event)) {
		if (this->event.type == sf::Event::Closed)
			this->window.close();
		updatePlayer();
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
