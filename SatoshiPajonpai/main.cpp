#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Player.h"
#include <iostream>
#include "Platform.h"
#include <sstream>
#include <SFML/Audio.hpp>
#include <time.h>
#include <windows.h>
#include "Menu.h"
#include <vector>
#include "Bitmap.h"
#include "Restart.h"
#include <sstream>

static const float VIEW_HEIGHT = 1000.0f;

void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int main()
{
	//==========================================================================================================================================//
	// Window Screen View

	float  windowWidth = VIEW_HEIGHT, windowHight = VIEW_HEIGHT; // Window Height Weight 

	sf::RenderWindow window(sf::VideoMode(int(windowWidth), int(windowHight)), "Satoshi Pajonpai", sf::Style::Close | sf::Style::Resize); // Render Window 
	window.setFramerateLimit(120);

	sf::View view(sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT), sf::Vector2f(windowWidth, windowHight)); 	// View 

	//==========================================================================================================================================//
	// Player 

	sf::Texture playerTexture;
	playerTexture.loadFromFile("assets/textures/PerfectSprite.png");
	Player player(&playerTexture, sf::Vector2u(4, 8), 0.5f, 100.0f);

	//==========================================================================================================================================//
	// Texture

	sf::Texture docterTexture;
	docterTexture.loadFromFile("assets/textures/Docter.png");

	sf::Texture pokeballTexture;
	pokeballTexture.loadFromFile("assets/textures/pokeball.png");

	sf::Texture dieTexture;
	dieTexture.loadFromFile("assets/textures/die.png");

	sf::Texture BlackTexture;
	BlackTexture.loadFromFile("assets/textures/Black.jpg");

	sf::Texture chestTexture;
	chestTexture.loadFromFile("assets/textures/chest.png");

	sf::Texture stoneTexture;
	stoneTexture.loadFromFile("assets/textures/stone.png");

	sf::Texture mushroomTexture;
	mushroomTexture.loadFromFile("assets/textures/Mushroom.png");

	// TextImage
	sf::Texture foundKey;
	foundKey.loadFromFile("assets/textImages/TextKey.png");

	//==========================================================================================================================================//
	// Clock 

	float deltaTime = 0.0f;
	sf::Clock clock;

	//==========================================================================================================================================//
	// Font TextTexture

	sf::Font font;
	if (!font.loadFromFile("assets/fonts/Pixeboy-z8XGD.ttf"))
		std::cout << "ERROR FONT";

	sf::Text textGameOver;  // TEXT GameOver 
	textGameOver.setFont(font);
	textGameOver.setCharacterSize(180);
	textGameOver.setFillColor(sf::Color::White);
	textGameOver.setStyle(sf::Text::Style::Bold);
	textGameOver.setString("Game Over");
	textGameOver.setPosition(windowWidth / 2 - 190, windowHight / 2 - 500);

	sf::Text textCountDie; 	// TEXT Count Die
	textCountDie.setFont(font);
	textCountDie.setCharacterSize(120);
	textCountDie.setPosition(windowWidth / 2 - 190, windowHight / 2 - 300);

	std::ostringstream showtime; // OStringStream 

	//==========================================================================================================================================// 
	// Restart State   

	Restart restart(windowWidth, windowHight);
	sf::Texture pickachuMeme;
	pickachuMeme.loadFromFile("assets/textures/PickachuMeme.png");
	Platform pickachuBox(&pickachuMeme, sf::Vector2f(240, 240), sf::Vector2f(windowWidth / 2 + 150, windowHight / 2 - 50));

	//==========================================================================================================================================// 
	// Manu State 

	Menu menu(windowWidth, windowHight);
	bool checkGameOpen = false;
	while (window.isOpen())
	{
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::KeyReleased:
				switch (evnt.key.code) {
				case sf::Keyboard::W:
					menu.MoveUp();
					break;
				case sf::Keyboard::S:
					menu.MoveDown();
					break;
				case sf::Keyboard::Return:
					switch (menu.GetPressedItem()) {
					case 0:
						std::cout << "Play is Pressed";
						checkGameOpen = true;
						break;
					case 1:
						std::cout << "Leaderboard is Pressed";
						break;
					case 2:
						window.close();
						break;
					}
				}
				break;

			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::Resized:
				std::cout << "\Resized\n";
				ResizeView(window, view);
				break;
			}

		}
		window.clear();
		menu.draw(window);
		window.display();
		if (checkGameOpen == true)
			break;
	}

	//==========================================================================================================================================// 
	// State obj 

	int pexel = 16;
	int state = 1;
	int countDie = 0;
	bool checkGameRestart = false;
	bool restartGame = false;
	bool continueGame = false;
	bool checkstate1_out = false;

	//==========================================================================================================================================// 
	// Run Game

	while (true)
	{
		// status state //
		bool checkPokeballTrap1 = false;
		bool checkTrap2 = false;
		bool checkExitTrap2 = false;

		
		// state //
		if (state == 1)
		{
			//Player Position
			if (checkstate1_out)
				player.SetPosition(104 * 4, 216 * 4);
			else
				player.SetPosition(426, 427);

			//Background
			sf::Texture backgroundState5Texture;
			backgroundState5Texture.loadFromFile("assets/maps/Map1.png");
			Platform Background1(&backgroundState5Texture, sf::Vector2f(224 * 64 / 16, 256 * 64 / 16), sf::Vector2f(224 * 64 / 32, 256 * 64 / 32));

			//BitMap Init
			std::vector<Bitmap> block0;
			int outdoor[16][14] = {
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
									{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
									{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
									{0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
									{0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
									{0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
									{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0 },
									{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0 },
									{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0 },
									{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
									{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
									{1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1 },
									{1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1 },
			};

			//DrawBitMap
			for (int mapX = 0; mapX < 14; mapX++)
			{
				for (int mapY = 0; mapY < 16; mapY++)
				{
					if (outdoor[mapY][mapX] == 1)
					{
						Bitmap outdoor(nullptr, sf::Vector2f(((mapX) * 64) + 32, ((mapY) * 64) + 32), sf::Vector2f(64.f, 64.f));
						block0.push_back(outdoor);
					}
				}
			}

			//Platform Init
			Platform door(nullptr, sf::Vector2f(34.f, 2.f), sf::Vector2f(113.f * 64 / 16, 255.f * 64 / 16));
			Platform die(&dieTexture, sf::Vector2f(58.f * 2, 94.f * 1.5), sf::Vector2f((16 * 7) * 4 - 23, 16 * 11 * 4));

			//Run Game
			while (window.isOpen())
			{
				//deltaTime//
				deltaTime = clock.restart().asSeconds();

				//Close Window//
				sf::Event evnt;
				while (window.pollEvent(evnt))
				{
					switch (evnt.type)
					{
					case sf::Event::Closed:
						window.close();
						break;
					case sf::Event::Resized:
						std::cout << "\Resized\n";
						ResizeView(window, view);
						break;
					}
				}

				//Player Update
				player.Update(deltaTime);

				//BitMap Collision
				Collider playerCollision = player.GetCollider();
				for (int i = 0; i < block0.size(); i++)
					block0[i].getCollider().CheckCollision(playerCollision, 1.0f);

				//Window Collision
				if (player.GetPosition().x < 0 + 29)
				{
					player.SetPosition(29, player.GetPosition().y);
				}
				if (player.GetPosition().y < 0 + 47)
				{
					player.SetPosition(player.GetPosition().x, 47);
				}
				if (player.GetPosition().x + 29 > 224 * 64 / 16)
				{
					player.SetPosition(224 * 64 / 16 - 29, player.GetPosition().y);
				}
				if (player.GetPosition().y + 47 > 256 * 64 / 16)
				{
					player.SetPosition(player.GetPosition().x, 256 * 64 / 16 - 47);
				}

				//Draw
				view.setCenter(player.GetPosition());
				std::cout << "x = " << player.GetPosition().x << " y = " << player.GetPosition().y << std::endl;
				window.clear();
				Background1.Draw(window);
				player.Draw(window);
				window.setView(view);

				//Die
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				{
					if (player.GetPosition().x >= (16 * 6) * 4 && player.GetPosition().x <= (16 * 7) * 4 && player.GetPosition().y >= (16 * 10) * 4 && player.GetPosition().y <= (16 * 11) * 4)
					{
						std::cout << "\nDIE\n";
						while (window.isOpen())
						{

							//Close Window//
							sf::Event evnt;
							while (window.pollEvent(evnt))
							{
								switch (evnt.type)
								{
								case sf::Event::Closed:
									window.close();
									break;
								case sf::Event::Resized:
									std::cout << "\Resized\n";
									ResizeView(window, view);
									break;
								case sf::Event::KeyReleased:
									if (evnt.key.code == sf::Keyboard::Return)
										restartGame = true;
									break;
								}
							}
							
							if (restartGame)
							{
								std::cout << "xxxx\n\n";
								break;
							}
							
							window.clear();
							Background1.Draw(window);
							die.Draw(window);
							window.setView(view);

							window.display();
						}
					}
				}
				//Goto State 2
				if (player.GetGlobalBounds().intersects(door.GetGlobalBounds()))
				{
					std::cout << "Goto State 2";
					state = 2;
					break;
				}
				//Goto Restart
				if (restartGame)
				{
					std::cout << "\nRestart in State 1\n";
					break;
				}

				//Window Display
				window.display();
			}
		}
		else if (state == 2)
		{		
			// Set Position
			player.SetPosition(576, 751);

			// Background
			sf::Texture backgroundState5Texture;
			backgroundState5Texture.loadFromFile("assets/maps/Map2.png");
			Platform Background2(&backgroundState5Texture, sf::Vector2f(576 * 64 / 16, 529 * 64 / 16), sf::Vector2f(576 * 64 / 32, 529 * 64 / 32));

			// Platform init
			Platform trap1Die(&dieTexture, sf::Vector2f(58.f * 2, 94.f * 1.5), sf::Vector2f((16 - 8) * 4, (368 - 8) * 4));
			Platform trap2Die(&dieTexture, sf::Vector2f(58.f * 2, 94.f * 1.5), sf::Vector2f((368 - 8) * 4, (368 - 8) * 4));
			Platform door1(nullptr, sf::Vector2f(64, 64), sf::Vector2f(576, 751 - 70));
			Platform stone1(&stoneTexture, sf::Vector2f(64, 64), sf::Vector2f((16 - 8) * 4, (416 - 8) * 4));
			Platform stone2(&stoneTexture, sf::Vector2f(64, 64), sf::Vector2f((32 - 8) * 4, (416 - 8) * 4));
			Platform trap1Pokeball(&pokeballTexture, sf::Vector2f(64, 64), sf::Vector2f((96 - 8) * 4, (336 - 8) * 4));
			Platform trap1Mushroom(&mushroomTexture, sf::Vector2f(64, 64), sf::Vector2f((16 - 8) * 4, (368 - 8) * 4));
			Platform trap1Stone(&stoneTexture, sf::Vector2f(64, 64), sf::Vector2f((32 - 8) * 4, (368 - 8) * 4));
			Platform trap2Stone1(&stoneTexture, sf::Vector2f(64, 64), sf::Vector2f((480 - 8) * 4, (384 - 8) * 4));
			Platform trap2Stone2(&stoneTexture, sf::Vector2f(64, 64), sf::Vector2f((480 - 8) * 4, (400 - 8) * 4));
			Platform trap2Stone3(&stoneTexture, sf::Vector2f(64, 64), sf::Vector2f((192 - 8) * 4, (384 - 8) * 4));
			Platform trap2Stone4(&stoneTexture, sf::Vector2f(64, 64), sf::Vector2f((192 - 8) * 4, (400 - 8) * 4));
			Platform trap2Stone5(&stoneTexture, sf::Vector2f(64, 64), sf::Vector2f((352 - 8) * 4, (368 - 8) * 4));
			Platform trap2Mushroom(&mushroomTexture, sf::Vector2f(64, 64), sf::Vector2f((368 - 8) * 4, (368 - 8) * 4));

			// BitMap Init
			std::vector<Bitmap> block0;
			int outdoor[33][36] = {
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
									{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
									{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
									{1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
									{1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
									{1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
									{1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
									{1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
									{1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
									{1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
									{1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
									{1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
									{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
									{1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
									{1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
									{1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
									{1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
									{1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
									{1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
									{1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1},
									{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1},
									{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1},
									{0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0},
									{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
									{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
									{0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0},
									{0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
									{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
									{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0},
									{0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0},
									{0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0},
									{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
									{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
			};

			// DrawBitMap
			for (int mapX = 0; mapX < 36; mapX++)
			{
				for (int mapY = 0; mapY < 33; mapY++)
				{
					if (outdoor[mapY][mapX] == 1)
					{
						Bitmap outdoor(nullptr, sf::Vector2f(((mapX) * 64) + 32, ((mapY) * 64) + 32), sf::Vector2f(64.f, 64.f));
						block0.push_back(outdoor);
					}
				}
			}

			// Run Game
			while (window.isOpen())
			{
				// DeltaTime
				deltaTime = clock.restart().asSeconds();

				// Close Window
				sf::Event evnt;
				while (window.pollEvent(evnt))
				{
					switch (evnt.type)
					{
					case sf::Event::Closed:
						window.close();
						break;
					case sf::Event::Resized:
						std::cout << "\Resized\n";
						ResizeView(window, view);
						break;
					}
				}
				
				// Player Update
				player.Update(deltaTime);

				// Window Collision
				if (player.GetPosition().x < 0 + 29)
				{
					player.SetPosition(29, player.GetPosition().y);
				}
				if (player.GetPosition().y + 46 > 529 * 64 / 16)
				{
					player.SetPosition(player.GetPosition().x, 529 * 64 / 16 - 46);
				}

				// BitMap Collision
				Collider playerCollision = player.GetCollider();
				for (int i = 0; i < block0.size(); i++)
					block0[i].getCollider().CheckCollision(playerCollision, 1.0f);

				//Platform Collision  
				stone1.GetCollider().CheckCollision(playerCollision, 1.0f);
				stone2.GetCollider().CheckCollision(playerCollision, 1.0f);

				// DrawBackground
				view.setCenter(player.GetPosition());
				std::cout << "x = " << player.GetPosition().x << " y = " << player.GetPosition().y << std::endl;
				window.clear();
				Background2.Draw(window);
				stone1.Draw(window);
				stone2.Draw(window);

				// Trap 1
				if (!checkPokeballTrap1 && player.GetGlobalBounds().intersects(trap1Pokeball.GetGlobalBounds())) //Get Pokeball
				{
					Platform trap1TextKey(&foundKey, sf::Vector2f(1000, 120), sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 400));
					checkPokeballTrap1 = true;
					while (window.isOpen())
					{
						//Close Window//
						sf::Event evnt;
						while (window.pollEvent(evnt))
						{
							switch (evnt.type)
							{
							case sf::Event::Closed:
								window.close();
								break;
							case sf::Event::Resized:
								std::cout << "\Resized\n";
								ResizeView(window, view);
								break;
							case sf::Event::KeyReleased:
								if (evnt.key.code == sf::Keyboard::Return)
									continueGame = true;
								break;
							}
						}

						if (continueGame)
						{
							std::cout << "Enter Click\n\n";
							
							continueGame = false;
							break;
						}
						window.clear();
						Background2.Draw(window);
						player.Draw(window);
						window.setView(view);
						trap1TextKey.Draw(window);
						window.display();
					}
				}		
				if (checkPokeballTrap1)
				{
					trap1Mushroom.Draw(window);
					trap1Stone.Draw(window);
					trap1Stone.GetCollider().CheckCollision(playerCollision, 1.0f);
					if (player.GetGlobalBounds().intersects(trap1Mushroom.GetGlobalBounds()))
					{
						//Die
						std::cout << "\nDIE\n";
						while (window.isOpen())
						{
							stone1.Draw(window);
							stone2.Draw(window);
							//Close Window//
							sf::Event evnt;
							while (window.pollEvent(evnt))
							{
								switch (evnt.type)
								{
								case sf::Event::Closed:
									window.close();
									break;
								case sf::Event::Resized:
									std::cout << "\Resized\n";
									ResizeView(window, view);
									break;
								case sf::Event::KeyReleased:
									if (evnt.key.code == sf::Keyboard::Return)
										restartGame = true;
									break;
								}
							}

							if (restartGame)
							{
								std::cout << "xxxx\n\n";
								break;
							}
							window.clear();
							Background2.Draw(window);
							trap1Stone.Draw(window);
							stone1.Draw(window);
							stone2.Draw(window);
							trap1Die.Draw(window);
							window.setView(view);
							window.display();
						}
					}
				}
				else
				{
					trap1Pokeball.Draw(window);
				}
				 
				// Trap 2
				if (!checkTrap2 && player.GetPosition().x > 432 * 4 && player.GetPosition().y > 368 * 4 && player.GetPosition().y < 400 * 4)
				{
					checkTrap2 = true;
				}
				if (checkTrap2)
				{
					trap2Stone1.GetCollider().CheckCollision(playerCollision, 1.0f);
					trap2Stone2.GetCollider().CheckCollision(playerCollision, 1.0f);
					trap2Stone1.Draw(window);
					trap2Stone2.Draw(window);
				
					if (player.GetPosition().x < 224 * 4 && player.GetPosition().x > 192 * 4 && player.GetPosition().y > 368 * 4 && player.GetPosition().y < 400 * 4)
						checkExitTrap2 = true;
					
					
				}
				if (checkExitTrap2)
				{
					trap2Stone3.GetCollider().CheckCollision(playerCollision, 1.0f);
					trap2Stone4.GetCollider().CheckCollision(playerCollision, 1.0f);
					trap2Stone5.GetCollider().CheckCollision(playerCollision, 1.0f);
					trap2Stone3.Draw(window);
					trap2Stone4.Draw(window);
					trap2Stone5.Draw(window);
					trap2Mushroom.Draw(window);
					if (player.GetGlobalBounds().intersects(trap2Mushroom.GetGlobalBounds()))
					{
						//Die
						std::cout << "\nDIE\n";
						while (window.isOpen())
						{
							stone1.Draw(window);
							stone2.Draw(window);
							//Close Window//
							sf::Event evnt;
							while (window.pollEvent(evnt))
							{
								switch (evnt.type)
								{
								case sf::Event::Closed:
									window.close();
									break;
								case sf::Event::Resized:
									std::cout << "\Resized\n";
									ResizeView(window, view);
									break;
								case sf::Event::KeyReleased:
									if (evnt.key.code == sf::Keyboard::Return)
										restartGame = true;
									break;
								}
							}

							if (restartGame)
							{
								std::cout << "xxxx\n\n";
								break;
							}
							window.clear();
							Background2.Draw(window);
							trap2Stone1.Draw(window);
							trap2Stone2.Draw(window);
							trap2Stone3.Draw(window);
							trap2Stone4.Draw(window);
							trap2Stone5.Draw(window);
							trap2Die.Draw(window);
							window.setView(view);
							window.display();
						}
					}
				}

				// DrawPlayer
				player.Draw(window);
				window.setView(view);

				// Goto State 1
				if (player.GetGlobalBounds().intersects(door1.GetGlobalBounds()))
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
					{
						state = 1;
						checkstate1_out = true;
						break;
					}
				}

				//Goto Restart
				if (restartGame)
				{
					std::cout << "\nRestart in State 1\n";
					break;
				}

				// Display
				window.display();
			}
		}
		else if (state == 3)
		{
			// Background
			sf::Texture backgroundState5Texture;
			backgroundState5Texture.loadFromFile("Map3.png");
			Platform Background3(&backgroundState5Texture, sf::Vector2f(224 * 64 / 16, 160 * 64 / 16), sf::Vector2f(224 * 64 / 32, 160 * 64 / 32));

			// BitMap Init
			std::vector<Bitmap> block0;
			int outdoor[10][14] = {
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
									{1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1},
									{1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1},
									{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
									{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
									{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
									{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
									{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
									{1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
									{1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1}
			};

			// DrawBitMap
			for (int mapX = 0; mapX < 14; mapX++)
			{
				for (int mapY = 0; mapY < 10; mapY++)
				{
					if (outdoor[mapY][mapX] == 1)
					{
						Bitmap outdoor(nullptr, sf::Vector2f(((mapX) * 64) + 32, ((mapY) * 64) + 32), sf::Vector2f(64.f, 64.f));
						block0.push_back(outdoor);
					}
				}
			}

			// Run Game
			while (window.isOpen())
			{
				// DeltaTime
				deltaTime = clock.restart().asSeconds();

				// Close Window
				sf::Event evnt;
				while (window.pollEvent(evnt))
				{
					switch (evnt.type)
					{
					case sf::Event::Closed:
						window.close();
						break;
					case sf::Event::Resized:
						std::cout << "\Resized\n";
						ResizeView(window, view);
						break;
					}
				}
				
				// Player Update
				player.Update(deltaTime);

				// BitMap Collision
				Collider playerCollision = player.GetCollider();
				for (int i = 0; i < block0.size(); i++)
					block0[i].getCollider().CheckCollision(playerCollision, 1.0f);

				// Draw
				view.setCenter(player.GetPosition());
				std::cout << "x = " << player.GetPosition().x << " y = " << player.GetPosition().y << std::endl;
				window.clear();
				Background3.Draw(window);
				player.Draw(window);
				window.setView(view);

				window.display();
			}
		}
		else if (state == 5)
		{
			//Background
			sf::Texture backgroundState5Texture;
			backgroundState5Texture.loadFromFile("state5.png");
			Platform Box1(&backgroundState5Texture, sf::Vector2f(768 * 90 / 16, 704 * 90 / 16), sf::Vector2f(768 * 90 / 32, 704 * 90 / 32));
			std::vector<Bitmap> block0;
			int outdoor[44][48] = {
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1 },
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1 },
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1 },
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1 },
									{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1 },
									{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1 },
									{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
									{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
									{1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1 },
									{1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1 },
									{1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1 },
									{1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1 },
									{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1 },
									{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1 },
									{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1 },
									{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1 },
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1 },
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1 },
									{1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
									{1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
									{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
									{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
									{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1 },
									{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1 },
									{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
									{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
									{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
									{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
									{1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 },
									{1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 },
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 },
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 },
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
			};

			//DrawMap
			for (int mapX = 0; mapX < 48; mapX++)
			{
				for (int mapY = 0; mapY < 44; mapY++)
				{
					if (outdoor[mapY][mapX] == 1)
					{
						Bitmap outdoor(nullptr, sf::Vector2f(((mapX) * 90) + 45, ((mapY) * 90) + 45), sf::Vector2f(90.f, 90.f));
						block0.push_back(outdoor);
					}
				}
			}

			//Run Game
			player.SetPosition(1300, 3290);
			while (window.isOpen())
			{
				//deltaTime//
				deltaTime = clock.restart().asSeconds();

				//Close Window//
				sf::Event evnt;
				while (window.pollEvent(evnt))
				{
					switch (evnt.type)
					{
					case sf::Event::Closed:
						window.close();
						break;
					case sf::Event::Resized:
						std::cout << "\Resized\n";
						ResizeView(window, view);
						break;
					}
				}

				//Collider
				Collider playerCollision = player.GetCollider();
				for (int i = 0; i < block0.size(); i++)
					block0[i].getCollider().CheckCollision(playerCollision, 1.0f);

				//Draw
				player.Update(deltaTime);
				view.setCenter(player.GetPosition());
				std::cout << "x = " << player.GetPosition().x << " y = " << player.GetPosition().y << std::endl;

				window.clear();
				Box1.Draw(window);
				player.Draw(window);

				window.setView(view);
				window.display();
			}
		}

		// restart //
		if (restartGame)
		{
			// Count Die
			countDie += 1;

			// Text Count Die
			showtime << countDie;
			textCountDie.setString(showtime.str());
			showtime.str("");

			// Set View
			view.setCenter(windowWidth / 1.5, windowHight / 2);
			std::cout << "Restart";

			// Render
			while (window.isOpen())
			{
				//selected ITEM
				sf::Event evnt;
				while (window.pollEvent(evnt))
				{
					switch (evnt.type)
					{
					case sf::Event::KeyReleased:
						switch (evnt.key.code) {
						case sf::Keyboard::W:
							restart.MoveUp();
							break;
						case sf::Keyboard::S:
							restart.MoveDown();
							break;
						case sf::Keyboard::Return:
							switch (restart.GetPressedItem()) {
							case 0:
								std::cout << "Restart is Pressed" << std::endl;
								state = 1;
								checkGameRestart = true;
								break;
							case 1:
								std::cout << "manu is Pressed" << std::endl;
								break;
							}
						}
						break;

					case sf::Event::Closed:
						window.close();
						break;

					case sf::Event::Resized:
						std::cout << "\Resized\n";
						ResizeView(window, view);
						break;
					}

				}

				//Draw Restart Menu
				window.clear();
				restart.draw(window);
				pickachuBox.Draw(window);
				window.draw(textGameOver);
				window.draw(textCountDie);
				window.setView(view);
				window.display();

				//Reset Status
				if (checkGameRestart == true)
				{
					checkGameRestart = false;
					restartGame = false;
					checkstate1_out = false;
					break;
				}

			}
		}
	}

	//==========================================================================================================================================// 
	// EndGame
	return 0;
}