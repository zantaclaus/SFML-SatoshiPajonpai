#pragma once
#include<SFML/Graphics.hpp>
#include "Collider.h"

class Bitmap
{
public:
	Bitmap(sf::Texture* texture, sf::Vector2f position, sf::Vector2f size);
	~Bitmap();

	void draw(sf::RenderWindow& window);
	Collider getCollider() { return Collider(body); }

private:
	sf::RectangleShape body;
};