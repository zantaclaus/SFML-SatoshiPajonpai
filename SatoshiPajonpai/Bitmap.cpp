#include "Bitmap.h"

Bitmap::Bitmap(sf::Texture* texture, sf::Vector2f position, sf::Vector2f size)
{
	body.setSize(size);
	body.setOrigin(size / 2.0f);
	body.setTexture(texture);
	body.setPosition(position);
}

Bitmap::~Bitmap()
{
}

void Bitmap::draw(sf::RenderWindow& window)
{
	window.draw(body);
}