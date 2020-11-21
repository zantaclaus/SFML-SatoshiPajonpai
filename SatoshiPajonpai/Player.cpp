#include "Player.h"
#include "Animation.h"
#include <iostream>
Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	row = 4;
	stop = 4;

	body.setSize(sf::Vector2f(56.0f, 82.0f)); // 34:52
	body.setOrigin(body.getSize() / 2.0f);
	//body.setPosition(667.f, 460.f);
	body.setTexture(texture);
}

Player::~Player()
{

}

void Player::Update(float deltaTime)
{
	row = stop;
	sf::Vector2f movement(0.0f, 0.0f);
	deltaTime += 0.05;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		deltaTime -= 0.03;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		movement.y -= speed * deltaTime;
		row = 3;
		stop = row + 4;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		movement.y += speed * deltaTime;
		row = 0;
		stop = row + 4;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		movement.x -= speed * deltaTime;
		row = 1;
		stop = row + 4;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		movement.x += speed * deltaTime;
		row = 2;
		stop = row + 4;
	}


	animation.Update(row, deltaTime);
	body.setTextureRect(animation.uvRect);

	body.move(movement);
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Player::SetPosition(float x, float y)
{
	body.setPosition(x, y);
}

