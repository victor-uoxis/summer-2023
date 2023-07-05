#pragma once
class Tile
{
private:
	sf::Sprite sprite;
	const bool damaging;

public:
	Tile(sf::Texture& texture, sf::IntRect rect, bool damaging = false);
	~Tile();

	const sf::FloatRect getGlobalBounds();

	void update();
	void render(sf::RenderTarget& target);
};

