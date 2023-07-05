#pragma once

#include "includes.h"
#include "Player.h"

class Game
{
public:
	Game();
	virtual ~Game();

	// Functions

	void updateCollisions();
	void update();
	void render();
	void renderPlayer();
	const sf::RenderWindow& getWindow() const;

	void updatePlayer();

private:
	sf::RenderWindow window;
	sf::Event event;
	Player *player;

	void initWindow();
	void initPlayer();
};

