#pragma once
#include <SFML\Graphics.hpp>
#include "Collider.h"
class Platform
{
public:
	Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);
	~Platform();
	sf::RectangleShape body;
	sf::Vector2f getSize();
	void Draw(sf::RenderWindow& window);
	Collider GetCollider() { return Collider(body); }
	sf::FloatRect GetGlobalBounds() { return body.getGlobalBounds(); }
private:
	sf::Vector2f size;
};

