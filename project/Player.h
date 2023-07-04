#pragma once
class Player
{
public:
	Player();
	virtual ~Player();

	// Functions

	void update();
	void render(sf::RenderTarget& target);

private:
	sf::Sprite sprite;
	sf::Texture textureSheet;

	void initSprite();
	void initTExture();
};

