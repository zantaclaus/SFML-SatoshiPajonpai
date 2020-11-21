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

int long main()
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

	sf::Texture dieUpTexture;
	dieUpTexture.loadFromFile("assets/textures/dieUp.png");

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

	sf::Texture foundMedicine;
	foundMedicine.loadFromFile("assets/textImages/TextMedicine.png");

	sf::Texture TextDieFloor;
	TextDieFloor.loadFromFile("assets/textImages/TextDieFloor.png");

	sf::Texture TextDieMedicine;
	TextDieMedicine.loadFromFile("assets/textImages/TextDieMedicine.png");

	sf::Texture TextDieMushroom;
	TextDieMushroom.loadFromFile("assets/textImages/TextDieMushroom.png");

	sf::Texture TextFIndKey;
	TextFIndKey.loadFromFile("assets/textImages/TextFindKey.png");

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

	int state = 1;
	int pexel = 16;
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
		bool checkTrap3 = false;
		bool checkTrap3Pokeball = false;
		bool checkTrap5 = false;
		bool checkTrap5Pokeball = false;
		bool checkTrap5ShowText = false;
		bool checkKey = false;
		bool trap6_1 = false;
		bool trap6_2 = false;
		bool trap6_3 = false;
		bool trap6_4 = false;
		
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
						Bitmap outdoor(nullptr, sf::Vector2f(((mapX) * 64.f) + 32.f, ((mapY) * 64.f) + 32.f), sf::Vector2f(64.f, 64.f));
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
						Platform TextDieFloorState1(&TextDieFloor, sf::Vector2f(1000, 120), sf::Vector2f(player.GetPosition().x, (16 * 11) * 4 + 325));
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
							TextDieFloorState1.Draw(window);
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

			Platform trap3Die(&dieUpTexture, sf::Vector2f(58.f * 2, 94.f * 1.5), sf::Vector2f((208 - 8) * 4, (464 - 8) * 4));
			Platform trap4Die(&dieTexture, sf::Vector2f(58.f * 2, 94.f * 1.5), sf::Vector2f((496 - 8) * 4, (496 - 8) * 4));
			Platform trap5Die(&dieTexture, sf::Vector2f(58.f * 2, 94.f * 1.5), sf::Vector2f((512 - 8) * 4, (448 - 8) * 4));
			Platform trap6Die(&dieTexture, sf::Vector2f(58.f * 2, 94.f * 1.5), sf::Vector2f((496 - 8) * 4, (400 - 8) * 4));

			Platform door1(nullptr, sf::Vector2f(64, 64), sf::Vector2f(576, 751 - 70));
			Platform door2(nullptr, sf::Vector2f(15*4, 15*4), sf::Vector2f(500.5*4, 320*4));
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

			Platform trap3stone1(&stoneTexture, sf::Vector2f(64, 64), sf::Vector2f((128 - 8) * 4, (448 - 8) * 4));
			Platform trap3stone2(&stoneTexture, sf::Vector2f(64, 64), sf::Vector2f((128 - 8) * 4, (464 - 8) * 4));
			Platform trap3Pokeball(&pokeballTexture, sf::Vector2f(64, 64), sf::Vector2f((64 - 8) * 4, (432 - 8) * 4));
		
			Platform trap4stone1(&stoneTexture, sf::Vector2f(64, 64), sf::Vector2f((480 - 8) * 4, (432 - 8) * 4));
			Platform trap4stone2(&stoneTexture, sf::Vector2f(64, 64), sf::Vector2f((480 - 8) * 4, (448 - 8) * 4));
			
			Platform trap5Pokeball(&pokeballTexture, sf::Vector2f(64, 64), sf::Vector2f((64 - 8) * 4, (528 - 8) * 4));
			
			Platform trap6Mushroom1(&mushroomTexture, sf::Vector2f(64, 64), sf::Vector2f((208 - 8) * 4, (464 - 8) * 4));
			Platform trap6Mushroom2(&mushroomTexture, sf::Vector2f(64, 64), sf::Vector2f((496 - 8) * 4, (496 - 8) * 4));
			Platform trap6Mushroom3(&mushroomTexture, sf::Vector2f(64, 64), sf::Vector2f((512 - 8) * 4, (448 - 8) * 4));
			Platform trap6Mushroom4(&mushroomTexture, sf::Vector2f(64, 64), sf::Vector2f((496 - 8) * 4, (400 - 8) * 4));

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
						Bitmap outdoor(nullptr, sf::Vector2f(((mapX) * 64.f) + 32.f, ((mapY) * 64.f) + 32.f), sf::Vector2f(64.f, 64.f));
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

				// Trap 1 Mushroom
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
						Platform TextDieMushroomTrap1(&TextDieMushroom, sf::Vector2f(1000, 120), sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 400));
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
							trap3Pokeball.Draw(window);
							stone2.Draw(window);
							trap1Die.Draw(window);
							TextDieMushroomTrap1.Draw(window);
							window.setView(view);
							window.display();
						}
					}
				}
				else
				{
					trap1Pokeball.Draw(window);
				}
				 
				// Trap 2 Stone Mushroom
				if (!checkTrap2 && player.GetPosition().x > 432 * 4 && player.GetPosition().x < 448 * 4 && player.GetPosition().y > 368 * 4 && player.GetPosition().y < 400 * 4)
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
						Platform TextDieMushroomTrap2(&TextDieMushroom, sf::Vector2f(1000, 120), sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 400));
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
							TextDieMushroomTrap2.Draw(window);
							window.setView(view);
							window.display();
						}
					}
				}

				// Trap 3 Medicine
				if (player.GetPosition().x > 48 * 4 && player.GetPosition().x < 100 * 4 && player.GetPosition().y > 416 * 4 && player.GetPosition().y < 480 * 4)
				{
					checkTrap3 = true;
				}
				if (checkTrap3)
				{
					trap3stone1.Draw(window);
					trap3stone2.Draw(window);
					trap3stone1.GetCollider().CheckCollision(playerCollision, 1.0f);
					trap3stone2.GetCollider().CheckCollision(playerCollision, 1.0f);
				
					if (!checkTrap3Pokeball && player.GetGlobalBounds().intersects(trap3Pokeball.GetGlobalBounds()))
					{
						Platform trap3TextMedicine(&foundMedicine, sf::Vector2f(1000, 120), sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 400));
						checkTrap3Pokeball = true;
						//Text Get Drug
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
							stone1.Draw(window);
							stone2.Draw(window);
							trap3stone1.Draw(window);
							trap3stone2.Draw(window);
							trap1Pokeball.Draw(window);
							trap3TextMedicine.Draw(window);
							window.display();
						}
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
					{
						Platform TextDieMedicineTrap3(&TextDieMedicine, sf::Vector2f(1000, 120), sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 400));
						Platform trap3Die(&dieTexture, sf::Vector2f(58.f * 2, 94.f * 1.5), sf::Vector2f(player.GetPosition().x, player.GetPosition().y));
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
							trap3Die.Draw(window);
							
							stone1.Draw(window);
							stone2.Draw(window);
							trap3stone1.Draw(window);
							trap3stone2.Draw(window);
							trap1Pokeball.Draw(window);
							TextDieMedicineTrap3.Draw(window);
							window.setView(view);
							window.display();
						}
						
					}
				}
				if (!checkTrap3Pokeball)
				{
					trap3Pokeball.Draw(window);
				}

				// Trap 4 stone
				if (player.GetPosition().x > 432 * 4 && player.GetPosition().y > 416 * 4 && player.GetPosition().y < 448 * 4)
				{
					trap4stone1.GetCollider().CheckCollision(playerCollision, 1.0f);
					trap4stone2.GetCollider().CheckCollision(playerCollision, 1.0f);
					trap4stone1.Draw(window);
					trap4stone2.Draw(window);
				}

				// Trap 5 Key
				if (player.GetPosition().x > 48 * 4 && player.GetPosition().x < 112 * 4 && player.GetPosition().y > 496 * 4)
				{
					
					std::cout << "Trap5";
					checkTrap5 = true;
				}
				if (checkTrap5)
				{
					if (!checkTrap5Pokeball)
						trap5Pokeball.Draw(window);
						
					if (player.GetGlobalBounds().intersects(trap5Pokeball.GetGlobalBounds()))
					{
						checkTrap5Pokeball = true;
						checkKey = true;
					}
				}
				if (!checkTrap5ShowText && checkTrap5Pokeball)
				{
					checkTrap5ShowText = true;
					Platform trap5TextKey(&foundKey, sf::Vector2f(1000, 120), sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 400));
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
						stone1.Draw(window);
						stone2.Draw(window);
						trap1Pokeball.Draw(window);
						trap3Pokeball.Draw(window);
						window.setView(view);
						trap5TextKey.Draw(window);
						window.display();
					}
				}
				
				// Trap 6 checkKey
				if (checkKey)
				{
					std::cout << "checkKey\n";
					if (player.GetPosition().x > 176 * 4 && player.GetPosition().y < 496 * 4)
					{
						trap6_1 = true;
					}			
					if (player.GetPosition().x > 480 * 4)
					{
						if (player.GetPosition().y < 529 * 4)
							trap6_2 = true;
						if (player.GetPosition().y < 480 * 4)
							trap6_3 = true;
						if (player.GetPosition().y < 432 * 4)
							trap6_4 = true;
					}

					// Die
					if (player.GetGlobalBounds().intersects(trap6Mushroom1.GetGlobalBounds()))
					{
						Platform TextDieMushroomTrap1(&TextDieMushroom, sf::Vector2f(1000, 120), sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 400));
						//Die
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
							//Goto Restart//
							if (restartGame)
							{
								std::cout << "xxxx\n\n";
								break;
							}
							//Render Window//
							window.clear();
							Background2.Draw(window);
							stone1.Draw(window);
							stone2.Draw(window);
							trap1Pokeball.Draw(window);
							trap3Pokeball.Draw(window);
							trap3Die.Draw(window);
							TextDieMushroomTrap1.Draw(window);
							window.setView(view);
							window.display();
						}
					}
					if (player.GetPosition().x > 480 * 4 && player.GetPosition().x < 496 * 4 && player.GetPosition().y > 480 * 4 && player.GetPosition().y < 496 * 4)
					{
						Platform TextDieMushroomTrap1(&TextDieMushroom, sf::Vector2f(1000, 120), sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 400));
						//Die
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
							//Goto Restart//
							if (restartGame)
							{
								std::cout << "xxxx\n\n";
								break;
							}
							//Render Window//
							window.clear();
							Background2.Draw(window);
							stone1.Draw(window);
							stone2.Draw(window);
							trap1Pokeball.Draw(window);
							trap3Pokeball.Draw(window);
							trap4Die.Draw(window);
							TextDieMushroomTrap1.Draw(window);

							window.setView(view);
							window.display();
						}
					}
					if (player.GetPosition().x > 496 * 4 && player.GetPosition().x < 512 * 4 && player.GetPosition().y > 432 * 4 && player.GetPosition().y < 448 * 4)
					{
						Platform TextDieMushroomTrap1(&TextDieMushroom, sf::Vector2f(1000, 120), sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 400));
						//Die
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
							//Goto Restart//
							if (restartGame)
							{
								std::cout << "xxxx\n\n";
								break;
							}
							//Render Window//
							window.clear();
							Background2.Draw(window);
							stone1.Draw(window);
							stone2.Draw(window);
							trap1Pokeball.Draw(window);
							trap3Pokeball.Draw(window);
							trap5Die.Draw(window);
							TextDieMushroomTrap1.Draw(window);
							trap6Mushroom2.Draw(window);
							window.setView(view);
							window.display();
						}
					}
					if (player.GetPosition().x > 480 * 4 && player.GetPosition().x < 496 * 4 && player.GetPosition().y > 384 * 4 && player.GetPosition().y < 400 * 4)
					{
						Platform TextDieMushroomTrap1(&TextDieMushroom, sf::Vector2f(1000, 120), sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 400));
						//Die
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
							//Goto Restart//
							if (restartGame)
							{
								std::cout << "xxxx\n\n";
								break;
							}
							//Render Window//
							window.clear();
							Background2.Draw(window);
							stone1.Draw(window);
							stone2.Draw(window);
							trap1Pokeball.Draw(window);
							trap3Pokeball.Draw(window);
							trap6Die.Draw(window);			
							trap6Mushroom2.Draw(window);
							trap6Mushroom3.Draw(window);
							TextDieMushroomTrap1.Draw(window);
							window.setView(view);
							window.display();
						}
					}
				}
				if (trap6_1)
				{
					trap6Mushroom1.Draw(window);
				}
				if (trap6_2)
				{
					trap6Mushroom2.Draw(window);
				}
				if (trap6_3)
				{
					trap6Mushroom3.Draw(window);
				}
				if (trap6_4)
				{
					trap6Mushroom4.Draw(window);
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

				//Goto State 3
				if (player.GetGlobalBounds().intersects(door2.GetGlobalBounds()))
				{
					Platform state3TextFindKey(&TextFIndKey, sf::Vector2f(1000, 120), sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 400));
					if (checkKey)
					{
						state = 3;
						break;
					}
					else
					{
						state3TextFindKey.Draw(window);
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
			// Set Position
			player.SetPosition((112-8) * 4, (144-8) * 4);

			// Background
			sf::Texture backgroundState5Texture;
			backgroundState5Texture.loadFromFile("assets/maps/Map3.png");
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
						Bitmap outdoor(nullptr, sf::Vector2f(((mapX) * 64.f) + 32.f, ((mapY) * 64.f) + 32.f), sf::Vector2f(64.f, 64.f));
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
			backgroundState5Texture.loadFromFile("assets/maps/Map5.png");
			Platform Box1(&backgroundState5Texture, sf::Vector2f(1200 * 90 / 16, 800 * 90 / 16), sf::Vector2f(1200 * 90 / 32, 800 * 90 / 32));

	

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
			view.setCenter(windowWidth / 1.5f, windowHight / 2.f);
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