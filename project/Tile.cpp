#include "includes.h"
#include "Tile.h"

Tile::Tile(sf::Texture& texture, sf::IntRect rect, bool damaging)
	:damaging(damaging)
{
	sprite.setTexture(texture);
	sprite.setTextureRect(rect);
}

Tile::~Tile()
{
}

const sf::FloatRect Tile::getGlobalBounds()
{
	return sprite.getGlobalBounds();
}

void Tile::update()
{
}

void Tile::render(sf::RenderTarget& target)
{
	target.draw(sprite);
}
