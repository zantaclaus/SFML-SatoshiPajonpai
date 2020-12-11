#include "Insect.h"

Insect::Insect(sf::Texture* texture, float sizeX, float sizeY, sf::Vector2f position, int direction)
{
	body.setSize(sf::Vector2f(sizeX, sizeY));
	body.setOrigin(body.getSize() / 2.0f);
	body.setTexture(texture);
	body.setPosition(position);

	spriteSizeX = texture->getSize().x / 4;
	spriteSizeY = texture->getSize().y / 4;
	body.setTextureRect(sf::IntRect(0, 0, sizeX, sizeY));

	this->direction = direction;
}

Insect::~Insect()
{
}

void Insect::Update()
{
	if (direction == 0)// Go Bottom
	{
		body.move(0.f, -10.f);
		body.setTextureRect(sf::IntRect(spriteSizeX , spriteSizeY * 0, spriteSizeX, spriteSizeY));
	}
	if (direction == 1) // Go Left
	{
		body.move(-10.f, 0.f);
		body.setTextureRect(sf::IntRect(spriteSizeX , spriteSizeY * 1, spriteSizeX, spriteSizeY));
	}
	if (direction == 2) // Go Right
	{
		body.move(10.f, 0.f);
		body.setTextureRect(sf::IntRect(spriteSizeX , spriteSizeY * 2, spriteSizeX, spriteSizeY));
	}
	if (direction == 3) // Go Top
	{
		body.move(0.f, -10.f);
		body.setTextureRect(sf::IntRect(spriteSizeX * animationFrame, spriteSizeY * 3, spriteSizeX, spriteSizeY));
	}
	animationFrame++;

	if (animationFrame >= 3)
		animationFrame = 0;
}

void Insect::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Insect::SetPosition(float x, float y)
{
	body.setPosition(x, y);
}
