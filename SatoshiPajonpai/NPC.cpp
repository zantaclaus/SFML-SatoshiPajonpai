#include "NPC.h"
#include <iostream>


NPC::NPC(sf::Texture* texture)
{
	body.setSize(sf::Vector2f(64.0f, 80.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setTexture(texture);

	spriteSizeX = texture->getSize().x / 4;
	spriteSizeY = texture->getSize().y / 1;
	body.setTextureRect(sf::IntRect(0, 0, 64, 80));
	animationFrame = 0;
}

NPC::~NPC()
{
}

void NPC::Update(int randomData)
{
	
	if (NPCClock.getElapsedTime().asSeconds() > 2)
	{
		if (randomData % 4 == 0)
		{
			body.setTextureRect(sf::IntRect(spriteSizeX * 0, 0, spriteSizeX, spriteSizeY));
		}
		if (randomData % 4 == 1)
		{
			body.setTextureRect(sf::IntRect(spriteSizeX * 1, 0, spriteSizeX, spriteSizeY));
		}
		if (randomData % 4 == 2)
		{
			body.setTextureRect(sf::IntRect(spriteSizeX * 2, 0, spriteSizeX, spriteSizeY));
		}
		if (randomData % 4 == 3)
		{
			body.setTextureRect(sf::IntRect(spriteSizeX * 3, 0, spriteSizeX, spriteSizeY));
		}

		NPCClock.restart();
	}
}

void NPC::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void NPC::SetPosition(float x, float y)
{
	body.setPosition(x, y);
}
