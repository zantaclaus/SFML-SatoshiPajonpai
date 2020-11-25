#pragma once
#include<SFML/Graphics.hpp>
#include<time.h>
#include "Collider.h"
#include "Platform.h"

class Ghost
{
public:
	Ghost(sf::Texture* texture, int randomData, Platform* platform,float sizeX, float sizeY);
	~Ghost();

	int getDirection();
	int getMapsizeX();
	int getMapsizeY();

	void Update();
	void Draw(sf::RenderWindow& window);
	void SetPosition(float x, float y);

	sf::FloatRect GetGlobalBounds() { return body.getGlobalBounds(); }
	sf::Vector2f GetPosition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(body); }

	sf::Clock NPCClock;

private:
	int spriteSizeX;
	int spriteSizeY;
	int mapSize_X;
	int mapSize_Y;
	int direction;
	int animationFrame = 0;
	sf::RectangleShape body;
};