#include "Platform.h"

Platform::Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position)
{
	body.setSize(size);
	body.setOrigin(size / 2.0f);
	body.setTexture(texture);
	body.setPosition(position);

	this->size = size;
}

Platform::~Platform()
{

}

sf::Vector2f Platform::getSize()
{
	return this->size;
}

void Platform::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
