#pragma once
#include<SFML/Graphics.hpp>
#include<time.h>
#include "Collider.h"
#include "Platform.h"

class Insect
{

public:
	Insect(sf::Texture* texture, float sizeX, float sizeY, sf::Vector2f position, int direction);
	~Insect();

	void Update();
	void Draw(sf::RenderWindow& window);
	void SetPosition(float x, float y);

	sf::FloatRect GetGlobalBounds() { return body.getGlobalBounds(); }
	sf::Vector2f GetPosition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(body); }
;

private:
	int spriteSizeX;
	int spriteSizeY;
	int direction;
	int animationFrame = 0;
	sf::RectangleShape body;
};

