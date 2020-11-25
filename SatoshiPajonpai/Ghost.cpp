#include "Ghost.h"


Ghost::Ghost(sf::Texture* texture, int randomData,float sizeX, float sizeY)
{
	body.setSize(sf::Vector2f(sizeX, sizeY));
	body.setOrigin(body.getSize() / 2.0f);
	body.setTexture(texture);
	
	spriteSizeX = texture->getSize().x / 4;
	spriteSizeY = texture->getSize().y / 4;
	body.setTextureRect(sf::IntRect(0, 0, sizeX, sizeY));
	
	direction = randomData;
}

Ghost::~Ghost()
{
}

void Ghost::Update()
{
	if (direction % 4 == 0)
	{
		body.setTextureRect(sf::IntRect(spriteSizeX , spriteSizeY * 0, spriteSizeX, spriteSizeY));
	}
	if (direction % 4 == 1)
	{
		body.setTextureRect(sf::IntRect(spriteSizeX , spriteSizeY * 1, spriteSizeX, spriteSizeY));
	}
	if (direction % 4 == 2)
	{
		body.setTextureRect(sf::IntRect(spriteSizeX , spriteSizeY * 2, spriteSizeX, spriteSizeY));
	}
	if (direction % 4 == 3)
	{
		body.setTextureRect(sf::IntRect(spriteSizeX , spriteSizeY * 3, spriteSizeX, spriteSizeY));
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
