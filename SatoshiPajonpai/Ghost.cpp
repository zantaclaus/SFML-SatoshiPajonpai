#include "Ghost.h"

Ghost::Ghost(sf::Texture * texture, int randomData, Platform * platform, float sizeX, float sizeY)
{
	body.setSize(sf::Vector2f(sizeX, sizeY));
	body.setOrigin(body.getSize() / 2.0f);
	body.setTexture(texture);

	spriteSizeX = texture->getSize().x / 4;
	spriteSizeY = texture->getSize().y / 4;
	body.setTextureRect(sf::IntRect(0, 0, sizeX, sizeY));

	this->direction = randomData;
	this->direction = direction % 4;

	mapSize_X = platform->getSize().x;
	mapSize_Y = platform->getSize().y;

	if (direction == 0) // Top
	{
		float x = rand() % (int(mapSize_X) - 10) + 10;
		body.setPosition(x, 0);
	}
	if (direction == 1) // Right
	{
		int y = rand() % (int(mapSize_Y) - 10) + 10;
		body.setPosition(mapSize_X, y);
	}
	if (direction == 2) // Left
	{
		int y = rand() % (int(mapSize_Y) - 10) + 10;
		body.setPosition(0, y);
	}
	if (direction == 3) // Bottom
	{
		int x = rand() % (int(mapSize_X) - 10) + 10;
		body.setPosition(x, mapSize_Y);
	}
}

Ghost::~Ghost()
{
}

int Ghost::getDirection()
{
	return this->direction;
}

int Ghost::getMapsizeX()
{
	return mapSize_X;
}

int Ghost::getMapsizeY()
{
	return mapSize_Y;
}



void Ghost::Update()
{
	if (direction == 0) // Top
	{	
		body.move(0.f, 5.f);
		body.setTextureRect(sf::IntRect(spriteSizeX * animationFrame, spriteSizeY * 0, spriteSizeX, spriteSizeY));
	}
	if (direction== 1) // Right
	{
		body.move(-5.f, 0.f);
		body.setTextureRect(sf::IntRect(spriteSizeX * animationFrame, spriteSizeY * 1, spriteSizeX, spriteSizeY));
	}
	if (direction == 2) // Left
	{
		body.move(5.f, 0.f);
		body.setTextureRect(sf::IntRect(spriteSizeX * animationFrame, spriteSizeY * 2, spriteSizeX, spriteSizeY));
	}
	if (direction == 3) // Bottom
	{
		body.move(0.f, -5.f);
		body.setTextureRect(sf::IntRect(spriteSizeX * animationFrame, spriteSizeY * 3, spriteSizeX, spriteSizeY));
	}
	animationFrame++;

	if (animationFrame >= 3)
		animationFrame = 0;


}

void Ghost::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Ghost::SetPosition(float x, float y)
{
	body.setPosition(x, y);
}
