#pragma once
#include <SFML\Graphics.hpp>
#define MAX_ITEM 2

class Restart
{
public:
	Restart(float width, float height);
	~Restart();

	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItem; }

	sf::Texture restartWindow;

private:
	int selectedItem = 0;
	sf::Font font;
	sf::Text restart[MAX_ITEM];
};

