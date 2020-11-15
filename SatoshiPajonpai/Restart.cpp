#include "Restart.h"

Restart::Restart(float width, float height)
{
	font.loadFromFile("assets/fonts/Pixeboy-z8XGD.ttf");
	//restartWindow.loadFromFile("GameOverTroll.png");

	restart[0].setFont(font);
	restart[0].setCharacterSize(60);
	restart[0].setFillColor(sf::Color::Red);
	restart[0].setString("Restart");
	restart[0].setOrigin(restart[0].getLocalBounds().width / 2, restart[0].getLocalBounds().height / 2);
	restart[0].setPosition(sf::Vector2f(width / 1.5, height / (MAX_ITEM + 1) * 1 + 350));

	restart[1].setFont(font);
	restart[1].setCharacterSize(60);
	restart[1].setFillColor(sf::Color::White);
	restart[1].setString("Menu");
	restart[1].setOrigin(restart[1].getLocalBounds().width / 2, restart[1].getLocalBounds().height / 2);
	restart[1].setPosition(sf::Vector2f(width / 1.5, height / (MAX_ITEM + 1) * 2 + 150));
}

Restart::~Restart()
{
}

void Restart::draw(sf::RenderWindow& window)
{
	//window.draw();
	for (int i = 0; i < MAX_ITEM; i++)
	{
		window.draw(restart[i]);
	}
}

void Restart::MoveUp()
{
	if (selectedItem - 1 >= 0)
	{
		restart[selectedItem].setFillColor(sf::Color::White);
		selectedItem--;
		restart[selectedItem].setFillColor(sf::Color::Red);
	}
}

void Restart::MoveDown()
{
	if (selectedItem + 1 < MAX_ITEM)
	{
		restart[selectedItem].setFillColor(sf::Color::White);
		selectedItem++;
		restart[selectedItem].setFillColor(sf::Color::Red);
	}
}
