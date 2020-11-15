#pragma once
#include<SFML/Graphics.hpp>
#include "Animation.h"
#include "Collider.h"

class Player
{
public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
	~Player();

	void Update(float deltatime);
	void Draw(sf::RenderWindow& window);
	void SetPosition(float x, float y);

	sf::FloatRect GetGlobalBounds() { return body.getGlobalBounds(); }
	sf::Vector2f GetPosition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(body); }
	sf::RectangleShape body;


private:

	Animation animation;
	unsigned int row;
	unsigned int stop;
	float speed;

};
