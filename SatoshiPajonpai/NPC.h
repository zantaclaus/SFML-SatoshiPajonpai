#pragma once
#include<SFML/Graphics.hpp>
#include<time.h>
#include "Collider.h"

class NPC
{
public:
	NPC(sf::Texture* texture);
	~NPC();

	void Update(int randomData);
	void Draw(sf::RenderWindow& window);
	void SetPosition(float x, float y);

	sf::FloatRect GetGlobalBounds() { return body.getGlobalBounds(); }
	sf::Vector2f GetPosition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(body); }
	
	sf::Clock NPCClock;

private:
	int spriteSizeX;
	int spriteSizeY;
	int animationFrame = 0;
	sf::RectangleShape body;
};