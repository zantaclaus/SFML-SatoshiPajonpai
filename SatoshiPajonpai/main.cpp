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
#include "NPC.h"
#include "Ghost.h"
#include "Insect.h"

static const float VIEW_HEIGHT = 1000.0f;

void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int long main()
{
	srand(time(NULL ));

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

	//NPC
	sf::Texture docterTexture;
	docterTexture.loadFromFile("assets/textures/DocterSprite.png");
	NPC Docter1(&docterTexture);

	//Ghost 
	sf::Texture GengarTexture; 
	GengarTexture.loadFromFile("assets/textures/Gengar.png");
	std::vector <Ghost*> Gengar;
	std::vector <Ghost*> Ghosty;

	//==========================================================================================================================================//
	// Texture

	sf::Texture pokeballTexture;
	pokeballTexture.loadFromFile("assets/textures/pokeball.png");

	
	sf::Texture flowerItemTexture;
	flowerItemTexture.loadFromFile("assets/textures/FlowerItem.png");

	sf::Texture dieTexture;
	dieTexture.loadFromFile("assets/textures/die.png");

	sf::Texture dieUpTexture;
	dieUpTexture.loadFromFile("assets/textures/dieUp.png");

	sf::Texture dieLeftTexture;
	dieLeftTexture.loadFromFile("assets/textures/dieLeft.png");

	sf::Texture dieRightTexture;
	dieRightTexture.loadFromFile("assets/textures/dieRight.png");

	sf::Texture BlackTexture;
	BlackTexture.loadFromFile("assets/textures/Black.jpg");

	sf::Texture chestTexture;
	chestTexture.loadFromFile("assets/textures/chest.png");

	sf::Texture stoneTexture;
	stoneTexture.loadFromFile("assets/textures/stone.png");
	
	sf::Texture stoneDarkModeTexture;
	stoneDarkModeTexture.loadFromFile("assets/textures/stoneDarkMode.png");

	sf::Texture mushroomTexture;
	mushroomTexture.loadFromFile("assets/textures/Mushroom.png");

	sf::Texture DocterDown;
	DocterDown.loadFromFile("assets/textures/DocterDown.png");

	sf::Texture snakeSprite;
	snakeSprite.loadFromFile("assets/textures/Snake.png");

	sf::Texture snakeTexture;
	snakeTexture.loadFromFile("assets/textures/SnakeTexture.png");

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

	sf::Texture TextTalkToDocter;
	TextTalkToDocter.loadFromFile("assets/textImages/TextToTalkDocter.png");

	sf::Texture TalkWithDocter;
	TalkWithDocter.loadFromFile("assets/textImages/TextToWithDocter1.png");

	sf::Texture TextDoorLocked;
	TextDoorLocked.loadFromFile("assets/textImages/TextDoorLocked.png");

	sf::Texture TextDieGhost;
	TextDieGhost.loadFromFile("assets/textImages/TeztDieGhost.png");

	sf::Texture TextSadudKha;
	TextSadudKha.loadFromFile("assets/textImages/TextSadudKha.png");

	sf::Texture TextToWatchInsideJar;
	TextToWatchInsideJar.loadFromFile("assets/textImages/TextToWatchInsideJar.png");
	
	sf::Texture TextDieSnake;
	TextDieSnake.loadFromFile("assets/textImages/DeadBySnake.png");
	
	sf::Texture TextLabel;
	TextLabel.loadFromFile("assets/textImages/Label.png");

	sf::Texture TextFoundCheckPoint;
	TextFoundCheckPoint.loadFromFile("assets/textImages/TextFoundCheckPoint.png");

	sf::Texture HintCheckPoint;
	HintCheckPoint.loadFromFile("assets/textImages/TextHintMap5.jpg");

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

	int checkPoint = 5;
	int state = 1;
	int pixel = 16;
	int randData1;
	int countDie = 0;
	bool checkGameRestart = false;
	bool restartGame = false;
	bool continueGame = false;
	bool checkstate1_out = false;
	bool checkPointMap4 = false;

	//==========================================================================================================================================// 
	// Run Game

	while (true)
	{
		
		//========================== status state ===========================//
		bool checkPokeballTrap1 = false;   //-----> state 2
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

		bool state4_CheckTrap1 = false;    //-----> state 4
		bool state4_checkTrap2 = false;
		
		
		//============================ Maps State ============================//

		if (state == 1)
		{
			// Background
			sf::Texture backgroundState5Texture;
			backgroundState5Texture.loadFromFile("assets/maps/Map1.png");
			Platform Background1(&backgroundState5Texture, sf::Vector2f(224 * 64 / 16, 256 * 64 / 16), sf::Vector2f(224 * 64 / 32, 256 * 64 / 32));

			//Player Position
			if (checkstate1_out)
				player.SetPosition(104 * 4, 216 * 4);
			else
				player.SetPosition(426, 427);

			// BitMap Init
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

			// DrawBitMap
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
			 
			// Platform Init
			Platform door(nullptr, sf::Vector2f(34.f, 10.f), sf::Vector2f(113.f * 64 / 16, 255.f * 64 / 16));
			Platform die(&dieTexture, sf::Vector2f(56.f * 2, 82.f * 1.5), sf::Vector2f((16 * 7) * 4 - 23, 16 * 11 * 4));

			// Run Game
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
				window.setView(view);
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
			Platform trap1Die(&dieTexture, sf::Vector2f(56.f * 2, 82.f * 1.5), sf::Vector2f((16 - 8) * 4, (368 - 8) * 4));
			Platform trap2Die(&dieTexture, sf::Vector2f(56.f * 2, 82.f * 1.5), sf::Vector2f((368 - 8) * 4, (368 - 8) * 4));

			Platform trap3Die(&dieUpTexture, sf::Vector2f(56.f * 2, 82.f * 1.5), sf::Vector2f((208 - 8) * 4, (464 - 8) * 4));
			Platform trap4Die(&dieUpTexture, sf::Vector2f(56.f * 2, 82.f * 1.5), sf::Vector2f((496 - 8) * 4, (496 - 8) * 4));
			Platform trap5Die(&dieUpTexture, sf::Vector2f(56.f * 2, 82.f * 1.5), sf::Vector2f((512 - 8) * 4, (448 - 8) * 4));
			Platform trap6Die(&dieUpTexture, sf::Vector2f(56.f * 2, 82.f * 1.5), sf::Vector2f((496 - 8) * 4, (400 - 8) * 4));

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

				// Trap 1 Mushroom -----> Die
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
						Platform trap3Die(&dieTexture, sf::Vector2f(56.f * 2, 82.f * 1.5), sf::Vector2f(player.GetPosition().x, player.GetPosition().y));
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
			Docter1.SetPosition((128 - 8) * 4, (80 - 8) * 4 - 25);
			if (checkPoint == 3)
				player.SetPosition((128 - 8) * 4, (96 - 8) * 4);
			else
				player.SetPosition((128 - 8) * 4, 522);
			

			// Background
			sf::Texture backgroundState5Texture;
			backgroundState5Texture.loadFromFile("assets/maps/Map3.2.png");
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

			// Platform init
			Platform floorDocter(nullptr, sf::Vector2f(5.f, 80.f), sf::Vector2f((128 - 8) * 4, (80 - 8) * 4 - 20));
			Platform door(nullptr, sf::Vector2f(32.f * 4 - 20,  20.f), sf::Vector2f((112) * 4, (160) * 4));
			
			// Run Game
			while (window.isOpen())
			{
				// Random
				randData1 = rand();

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
				Docter1.Update(randData1);
				
				// BitMap Collision
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
				if (player.GetPosition().y + 47 > 160 * 64 / 16)
				{
					player.SetPosition(player.GetPosition().x, 160 * 64 / 16 - 47);
				}

				//NPC Collision
				Docter1.GetCollider().CheckCollision(playerCollision, 1.0f);
				
				//Goto State 4
				if (player.GetGlobalBounds().intersects(door.GetGlobalBounds()))
				{
					state = 4;
					break;
				}

				// Draw
				view.setCenter(player.GetPosition());
				std::cout << "x = " << player.GetPosition().x << " y = " << player.GetPosition().y << std::endl;
				window.clear();
				Background3.Draw(window);
				player.Draw(window);
				Docter1.Draw(window);
	
				//Docter Text to Talk
				if (floorDocter.GetGlobalBounds().intersects(player.GetGlobalBounds()))
				{
					Platform TalkToDocter(&TextTalkToDocter, sf::Vector2f(1000, 120), sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 400));
					Platform DocterAtHome(&DocterDown, sf::Vector2f(64, 80), sf::Vector2f((128 - 8) * 4, (80 - 8) * 4 - 25));
					TalkToDocter.Draw(window);
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
					{
						checkPoint = 3;
						Platform BoxTalkWithDocter1(&TalkWithDocter, sf::Vector2f(1000, 120), sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 400));
						while (1)
						{
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
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
							{
								break;
							}

							Background3.Draw(window);
							DocterAtHome.Draw(window);
							player.Draw(window);
							BoxTalkWithDocter1.Draw(window);

							window.setView(view);
							window.display();
						}
					}
				}

				window.setView(view);
				window.display();
			}
		}
		else if (state == 4)
		{
			// Set Position
			if (checkPointMap4 == true)
				player.SetPosition((416 - 8) * 4, (64 - 8) * 4);
			else
				player.SetPosition((512 - 8) * 4, (352 - 8) * 4);

			// Background
			sf::Texture backgroundState4;
			backgroundState4.loadFromFile("assets/maps/Map4.png");
			Platform Background4(&backgroundState4, sf::Vector2f(576 * 64 / 16, 529 * 64 / 16), sf::Vector2f(576 * 64 / 32, 529 * 64 / 32));

			// Ganger init
			Gengar.push_back(new Ghost(&GengarTexture, int(rand()), &Background4, 82.f, 80.f));
			Gengar.push_back(new Ghost(&GengarTexture, int(rand()), &Background4, 82.f, 80.f));
			Gengar.push_back(new Ghost(&GengarTexture, int(rand()), &Background4, 82.f, 80.f));
			Gengar.push_back(new Ghost(&GengarTexture, int(rand()), &Background4, 82.f, 80.f));

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

			// Platform init
			Platform door1(nullptr, sf::Vector2f(64, 64), sf::Vector2f(576, 751 - 70));
			Platform door2(nullptr, sf::Vector2f(15 * 4, 15 * 4), sf::Vector2f(500.5 * 4, 320 * 4));
			Platform door3(nullptr, sf::Vector2f(32 * 4, 2 * 4), sf::Vector2f(16 * 4, 528 * 4));

			Platform trap1Stone1(&stoneDarkModeTexture, sf::Vector2f(64, 64), sf::Vector2f((480 - 8) * 4, (512 - 8) * 4));
			Platform trap1Stone2(&stoneDarkModeTexture, sf::Vector2f(64, 64), sf::Vector2f((480 - 8) * 4, (528 - 8) * 4));
			Platform trap1Stone3(&stoneDarkModeTexture, sf::Vector2f(64, 64), sf::Vector2f((256 - 8) * 4, (464 - 8) * 4));
			Platform trap1Mushroom(&mushroomTexture, sf::Vector2f(64, 64), sf::Vector2f((240 - 8) * 4, (464 - 8) * 4));
			Platform trap1Mushroom2(&mushroomTexture, sf::Vector2f(64, 64), sf::Vector2f((304 - 8) * 4, (512 - 8) * 4));
			Platform trap1Mushroom3(&mushroomTexture, sf::Vector2f(64, 64), sf::Vector2f((304 - 8) * 4, (528 - 8) * 4));

			Platform trapLeft_Die(&dieTexture, sf::Vector2f(56.f * 2, 82.f * 1.5), sf::Vector2f((16 - 8) * 4, (368 - 8) * 4));
			Platform trapLeft_Pokeball(&pokeballTexture, sf::Vector2f(64, 64), sf::Vector2f((96 - 8) * 4, (336 - 8) * 4));
			Platform trapLeft_Mushroom(&mushroomTexture, sf::Vector2f(64, 64), sf::Vector2f((16 - 8) * 4, (368 - 8) * 4));
			Platform trapLeft_Stone(&stoneTexture, sf::Vector2f(64, 64), sf::Vector2f((32 - 8) * 4, (368 - 8) * 4));

			Platform trapMid_stone1(&stoneTexture, sf::Vector2f(64, 64), sf::Vector2f((128 - 8) * 4, (448 - 8) * 4));
			Platform trapMid_stone2(&stoneTexture, sf::Vector2f(64, 64), sf::Vector2f((128 - 8) * 4, (464 - 8) * 4));
			Platform trapMid_Pokeball(&pokeballTexture, sf::Vector2f(64, 64), sf::Vector2f((64 - 8) * 4, (432 - 8) * 4));
			

			Platform trap2_Mushroom1(&mushroomTexture, sf::Vector2f(64, 64), sf::Vector2f((352 - 8) * 4, (400 - 8) * 4));
			Platform trap2_Mushroom2(&mushroomTexture, sf::Vector2f(64, 64), sf::Vector2f((368 - 8) * 4, (352 - 8) * 4));
			Platform trap2_Mushroom3(&mushroomTexture, sf::Vector2f(64, 64), sf::Vector2f((304 - 8) * 4, (368 - 8) * 4));
			Platform trap2_Mushroom4(&mushroomTexture, sf::Vector2f(64, 64), sf::Vector2f((256 - 8) * 4, (368 - 8) * 4));
			Platform trap2_Mushroom5(&mushroomTexture, sf::Vector2f(64, 64), sf::Vector2f((224 - 8) * 4, (400 - 8) * 4));
			Platform trap2_Mushroom6(&mushroomTexture, sf::Vector2f(64, 64), sf::Vector2f((208 - 8) * 4, (352 - 8) * 4));
			

			Platform Flower_checkPoint(nullptr, sf::Vector2f(64, 64), sf::Vector2f((416 - 8) * 4, (64 - 8) * 4));
			
			
			//------------------- Run Game -------------------------
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

				/*...........................Update..........Collision.............................*/

				// Player Update
				player.Update(deltaTime);

				//Gengar Update
				int index = 0;
				for (auto* i : Gengar)
				{
					i->Update();
					if (i->getDirection() == 0) // Top
					{
						if (i->GetPosition().y > i->getMapsizeY())
						{
							delete Gengar.at(index);
							Gengar.erase(Gengar.begin() + index);
							index--;
						}
					}
					if (i->getDirection() == 1) // Right
					{
						if (i->GetPosition().x < 0)
						{
							delete Gengar.at(index);
							Gengar.erase(Gengar.begin() + index);
							index--;
						}
					}
					if (i->getDirection() == 2) // Left
					{
						if (i->GetPosition().x > i->getMapsizeX())
						{
							delete Gengar.at(index);
							Gengar.erase(Gengar.begin() + index);
							index--;
						}
					}
					if (i->getDirection() == 3) // Bottom
					{
						if (i->GetPosition().y < 0)
						{
							delete Gengar.at(index);
							Gengar.erase(Gengar.begin() + index);
							index--;
						}
					}
					index++;
				}

				// Gengar Limited
				if (Gengar.size() < 4)
				{
					Gengar.push_back(new Ghost(&GengarTexture, int(rand()), &Background4, 82.f, 80.f));
				}

				// Dead By Gengar
				for (auto* i : Gengar)
				{
					if (i->GetGlobalBounds().intersects(player.GetGlobalBounds()))
					{
						std::cout << "\nDIE\n";
						Platform player_Die(&dieTexture, sf::Vector2f(56.f * 2, 82.f * 1.5), sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 15));
						Platform DieBy_Ghost(&TextDieGhost, sf::Vector2f(1000, 120), sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 400));
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
							Background4.Draw(window);
							player_Die.Draw(window);
							DieBy_Ghost.Draw(window);
							
							//Trap 4 - 1
							if (state4_checkTrap2)
							{
								trap2_Mushroom1.Draw(window);
								trap2_Mushroom2.Draw(window);
								trap2_Mushroom3.Draw(window);
								trap2_Mushroom4.Draw(window);
								trap2_Mushroom5.Draw(window);
								trap2_Mushroom6.Draw(window);
							}
							// Trap 4 - 2
							if (state4_CheckTrap1)
							{
								trap1Stone1.Draw(window);
								trap1Stone2.Draw(window);
								trap1Stone3.Draw(window);
								trap1Mushroom.Draw(window);
							}

							//Gengar Update
							int index = 0;
							for (auto* i : Gengar)
							{
								i->Update();
								if (i->getDirection() == 0) // Top
								{
									if (i->GetPosition().y > i->getMapsizeY())
									{
										delete Gengar.at(index);
										Gengar.erase(Gengar.begin() + index);
										index--;
									}
								}
								if (i->getDirection() == 1) // Right
								{
									if (i->GetPosition().x < 0)
									{
										delete Gengar.at(index);
										Gengar.erase(Gengar.begin() + index);
										index--;
									}
								}
								if (i->getDirection() == 2) // Left
								{
									if (i->GetPosition().x > i->getMapsizeX())
									{
										delete Gengar.at(index);
										Gengar.erase(Gengar.begin() + index);
										index--;
									}
								}
								if (i->getDirection() == 3) // Bottom
								{
									if (i->GetPosition().y < 0)
									{
										delete Gengar.at(index);
										Gengar.erase(Gengar.begin() + index);
										index--;
									}
								}
								index++;
							}

							// Gengar Limited
							if (Gengar.size() < 4)
							{
								Gengar.push_back(new Ghost(&GengarTexture, int(rand()), &Background4, 82.f, 80.f));
							}

							// Draw Gengar
							for (auto* i : Gengar)
								i->Draw(window);

							window.setView(view);
							window.display();
						}
					}
				}

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

				/*...................................Background..................................*/

				// Draw Background
				view.setCenter(player.GetPosition());
				std::cout << "x = " << player.GetPosition().x << " y = " << player.GetPosition().y << std::endl;
				window.clear();
				Background4.Draw(window);

				/*.............................Trap.........AfterDraw_Player........................*/

				// Trap Left Mushroom -----> Die
				if (!checkPokeballTrap1 && player.GetGlobalBounds().intersects(trapLeft_Pokeball.GetGlobalBounds())) //Get Pokeball
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
						Background4.Draw(window);
						trap2_Mushroom1.Draw(window);
						trap2_Mushroom2.Draw(window);
						trap2_Mushroom3.Draw(window);
						trap2_Mushroom4.Draw(window);
						trap2_Mushroom5.Draw(window);
						trap2_Mushroom6.Draw(window);
						player.Draw(window);
						window.setView(view);
						trap1TextKey.Draw(window);
						window.display();
					}
				}
				if (checkPokeballTrap1)
				{

					trapLeft_Mushroom.Draw(window);
					trapLeft_Stone.Draw(window);
					trapLeft_Stone.GetCollider().CheckCollision(playerCollision, 1.0f);
					if (player.GetGlobalBounds().intersects(trapLeft_Mushroom.GetGlobalBounds()))
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

							if (restartGame)
							{
								std::cout << "xxxx\n\n";
								break;
							}
							window.clear();
							Background4.Draw(window);
							trapLeft_Stone.Draw(window);
					
							trap2_Mushroom1.Draw(window);
							trap2_Mushroom2.Draw(window);
							trap2_Mushroom3.Draw(window);
							trap2_Mushroom4.Draw(window);
							trap2_Mushroom5.Draw(window);
							trap2_Mushroom6.Draw(window);
							
							//Gengar Update
							int index = 0;
							for (auto* i : Gengar)
							{
								i->Update();
								if (i->getDirection() == 0) // Top
								{
									if (i->GetPosition().y > i->getMapsizeY())
									{
										delete Gengar.at(index);
										Gengar.erase(Gengar.begin() + index);
										index--;
									}
								}
								if (i->getDirection() == 1) // Right
								{
									if (i->GetPosition().x < 0)
									{
										delete Gengar.at(index);
										Gengar.erase(Gengar.begin() + index);
										index--;
									}
								}
								if (i->getDirection() == 2) // Left
								{
									if (i->GetPosition().x > i->getMapsizeX())
									{
										delete Gengar.at(index);
										Gengar.erase(Gengar.begin() + index);
										index--;
									}
								}
								if (i->getDirection() == 3) // Bottom
								{
									if (i->GetPosition().y < 0)
									{
										delete Gengar.at(index);
										Gengar.erase(Gengar.begin() + index);
										index--;
									}
								}
								index++;
							}

							// Gengar Limited
							if (Gengar.size() < 4)
							{
								Gengar.push_back(new Ghost(&GengarTexture, int(rand()), &Background4, 82.f, 80.f));
							}
							
							// Draw Gengar
							for (auto* i : Gengar)
								i->Draw(window);


							trapLeft_Die.Draw(window);
							TextDieMushroomTrap1.Draw(window);
							window.setView(view);
							window.display();
						}
					}
				}
				else
				{
					trapLeft_Pokeball.Draw(window);
				}

				// Trap Mid Medicine
				if (player.GetPosition().x > 48 * 4 && player.GetPosition().x < 100 * 4 && player.GetPosition().y > 416 * 4 && player.GetPosition().y < 480 * 4)
				{
					checkTrap3 = true;
				}
				if (checkTrap3)
				{
					trapMid_stone1.Draw(window);
					trapMid_stone2.Draw(window);
					trapMid_stone1.GetCollider().CheckCollision(playerCollision, 1.0f);
					trapMid_stone2.GetCollider().CheckCollision(playerCollision, 1.0f);

					if (!checkTrap3Pokeball && player.GetGlobalBounds().intersects(trapMid_Pokeball.GetGlobalBounds()))
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
							Background4.Draw(window);
							player.Draw(window);
							window.setView(view);

							trap2_Mushroom1.Draw(window);
							trap2_Mushroom2.Draw(window);
							trap2_Mushroom3.Draw(window);
							trap2_Mushroom4.Draw(window);
							trap2_Mushroom5.Draw(window);
							trap2_Mushroom6.Draw(window);

							trapMid_stone1.Draw(window);
							trapMid_stone2.Draw(window);
							trapLeft_Pokeball.Draw(window);
							trap3TextMedicine.Draw(window);
							window.display();
						}
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
					{
						Platform TextDieMedicineTrap3(&TextDieMedicine, sf::Vector2f(1000, 120), sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 400));
						Platform trap3Die(&dieTexture, sf::Vector2f(56.f * 2, 82.f * 1.5), sf::Vector2f(player.GetPosition().x, player.GetPosition().y));
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

							if (restartGame)
							{
								std::cout << "xxxx\n\n";
								break;
							}
							window.clear();
							Background4.Draw(window);
							trap3Die.Draw(window);

							//Gengar Update
							int index = 0;
							for (auto* i : Gengar)
							{
								i->Update();
								if (i->getDirection() == 0) // Top
								{
									if (i->GetPosition().y > i->getMapsizeY())
									{
										delete Gengar.at(index);
										Gengar.erase(Gengar.begin() + index);
										index--;
									}
								}
								if (i->getDirection() == 1) // Right
								{
									if (i->GetPosition().x < 0)
									{
										delete Gengar.at(index);
										Gengar.erase(Gengar.begin() + index);
										index--;
									}
								}
								if (i->getDirection() == 2) // Left
								{
									if (i->GetPosition().x > i->getMapsizeX())
									{
										delete Gengar.at(index);
										Gengar.erase(Gengar.begin() + index);
										index--;
									}
								}
								if (i->getDirection() == 3) // Bottom
								{
									if (i->GetPosition().y < 0)
									{
										delete Gengar.at(index);
										Gengar.erase(Gengar.begin() + index);
										index--;
									}
								}
								index++;
							}

							// Gengar Limited
							if (Gengar.size() < 4)
							{
								Gengar.push_back(new Ghost(&GengarTexture, int(rand()), &Background4, 82.f, 80.f));
							}

							// Draw Gengar
							for (auto* i : Gengar)
								i->Draw(window);
							trapMid_stone1.Draw(window);
							trapMid_stone2.Draw(window);
							trapMid_Pokeball.Draw(window);
							TextDieMedicineTrap3.Draw(window);
							window.setView(view);
							window.display();
						}

					}
				}
				if (!checkTrap3Pokeball)
				{
					trapMid_Pokeball.Draw(window);
				}


				// Trap1 Bottom Way
				if (player.GetPosition().x < 448 * 4 && player.GetPosition().x > 400 * 4 && player.GetPosition().y > 496 * 4)
				{
					state4_CheckTrap1 = true;
				}
				if (state4_CheckTrap1)
				{
					trap1Stone1.GetCollider().CheckCollision(playerCollision, 1.0f);
					trap1Stone2.GetCollider().CheckCollision(playerCollision, 1.0f);
					trap1Stone1.Draw(window);
					trap1Stone2.Draw(window);

					trap1Stone2.GetCollider().CheckCollision(playerCollision, 1.0f);
					trap1Stone3.Draw(window);
					trap1Mushroom.Draw(window);

					//Die
					if (player.GetPosition().y >= 496 * 4 && player.GetPosition().x <= 309 * 4)
					{
						std::cout << "\nDIE\n";
						Platform trap1_Die2(&dieLeftTexture, sf::Vector2f(56.f * 2, 82.f * 1.5), sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 15));
						Platform SadudKha_Die(&TextSadudKha, sf::Vector2f(1000, 120), sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 400));
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
							Background4.Draw(window);
							trap1_Die2.Draw(window);
							trap1Stone1.Draw(window);
							trap1Stone2.Draw(window);
							trap1Stone3.Draw(window);
							trap1Mushroom.Draw(window);
							SadudKha_Die.Draw(window);

							//Gengar Update
							int index = 0;
							for (auto* i : Gengar)
							{
								i->Update();
								if (i->getDirection() == 0) // Top
								{
									if (i->GetPosition().y > i->getMapsizeY())
									{
										delete Gengar.at(index);
										Gengar.erase(Gengar.begin() + index);
										index--;
									}
								}
								if (i->getDirection() == 1) // Right
								{
									if (i->GetPosition().x < 0)
									{
										delete Gengar.at(index);
										Gengar.erase(Gengar.begin() + index);
										index--;
									}
								}
								if (i->getDirection() == 2) // Left
								{
									if (i->GetPosition().x > i->getMapsizeX())
									{
										delete Gengar.at(index);
										Gengar.erase(Gengar.begin() + index);
										index--;
									}
								}
								if (i->getDirection() == 3) // Bottom
								{
									if (i->GetPosition().y < 0)
									{
										delete Gengar.at(index);
										Gengar.erase(Gengar.begin() + index);
										index--;
									}
								}
								index++;
							}

							// Gengar Limited
							if (Gengar.size() < 4)
							{
								Gengar.push_back(new Ghost(&GengarTexture, int(rand()), &Background4, 82.f, 80.f));
							}

							// Draw Gengar
							for (auto* i : Gengar)
								i->Draw(window);

							window.setView(view);
							window.display();
						}

					}
				}

				// Trap2 Top Way
				if (player.GetPosition().x < 432 * 4 && player.GetPosition().x > 384 * 4 && player.GetPosition().y > 368 * 4 && player.GetPosition().y < 400 * 4)
				{
					state4_checkTrap2 = true;
				}
				if (state4_checkTrap2)
				{
					trap2_Mushroom1.Draw(window);
					trap2_Mushroom2.Draw(window);
					trap2_Mushroom3.Draw(window);
					trap2_Mushroom4.Draw(window);
					trap2_Mushroom5.Draw(window);
					trap2_Mushroom6.Draw(window);

					if (player.GetPosition().x > 336 * 4 && player.GetPosition().x < 352 * 4 && player.GetPosition().y > 384 * 4 && player.GetPosition().y < 400 * 4)
					{
						//Die 1
						std::cout << "DiE1";
						Platform player_Die(&dieLeftTexture, sf::Vector2f(56.f * 2, 82.f * 1.5), sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 15));
						Platform Text_Die(&TextDieMushroom, sf::Vector2f(1000, 120), sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 400));
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
							Background4.Draw(window);

							player_Die.Draw(window);
							Text_Die.Draw(window);
							
							trap2_Mushroom2.Draw(window);
							trap2_Mushroom3.Draw(window);
							trap2_Mushroom4.Draw(window);
							trap2_Mushroom5.Draw(window);
							trap2_Mushroom6.Draw(window);

							//Gengar Update
							int index = 0;
							for (auto* i : Gengar)
							{
								i->Update();
								if (i->getDirection() == 0) // Top
								{
									if (i->GetPosition().y > i->getMapsizeY())
									{
										delete Gengar.at(index);
										Gengar.erase(Gengar.begin() + index);
										index--;
									}
								}
								if (i->getDirection() == 1) // Right
								{
									if (i->GetPosition().x < 0)
									{
										delete Gengar.at(index);
										Gengar.erase(Gengar.begin() + index);
										index--;
									}
								}
								if (i->getDirection() == 2) // Left
								{
									if (i->GetPosition().x > i->getMapsizeX())
									{
										delete Gengar.at(index);
										Gengar.erase(Gengar.begin() + index);
										index--;
									}
								}
								if (i->getDirection() == 3) // Bottom
								{
									if (i->GetPosition().y < 0)
									{
										delete Gengar.at(index);
										Gengar.erase(Gengar.begin() + index);
										index--;
									}
								}
								index++;
							}

							// Gengar Limited
							if (Gengar.size() < 4)
							{
								Gengar.push_back(new Ghost(&GengarTexture, int(rand()), &Background4, 82.f, 80.f));
							}

							// Draw Gengar
							for (auto* i : Gengar)
								i->Draw(window);

							window.setView(view);
							window.display();
						}
					}
					if (player.GetPosition().x > 352 * 4 && player.GetPosition().x < 368 * 4 && player.GetPosition().y > 336 * 4 && player.GetPosition().y < 352 * 4)
					{
						//Die 2
						std::cout << "DiE2";
						Platform player_Die(&dieUpTexture, sf::Vector2f(56.f * 2, 82.f * 1.5), sf::Vector2f(player.GetPosition().x, player.GetPosition().y - 15));
						Platform Text_Die(&TextDieMushroom, sf::Vector2f(1000, 120), sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 400));
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
							Background4.Draw(window);

							player_Die.Draw(window);
							Text_Die.Draw(window);

							trap2_Mushroom1.Draw(window);
							trap2_Mushroom3.Draw(window);
							trap2_Mushroom4.Draw(window);
							trap2_Mushroom5.Draw(window);
							trap2_Mushroom6.Draw(window);

							//Gengar Update
							int index = 0;
							for (auto* i : Gengar)
							{
								i->Update();
								if (i->getDirection() == 0) // Top
								{
									if (i->GetPosition().y > i->getMapsizeY())
									{
										delete Gengar.at(index);
										Gengar.erase(Gengar.begin() + index);
										index--;
									}
								}
								if (i->getDirection() == 1) // Right
								{
									if (i->GetPosition().x < 0)
									{
										delete Gengar.at(index);
										Gengar.erase(Gengar.begin() + index);
										index--;
									}
								}
								if (i->getDirection() == 2) // Left
								{
									if (i->GetPosition().x > i->getMapsizeX())
									{
										delete Gengar.at(index);
										Gengar.erase(Gengar.begin() + index);
										index--;
									}
								}
								if (i->getDirection() == 3) // Bottom
								{
									if (i->GetPosition().y < 0)
									{
										delete Gengar.at(index);
										Gengar.erase(Gengar.begin() + index);
										index--;
									}
								}
								index++;
							}

							// Gengar Limited
							if (Gengar.size() < 4)
							{
								Gengar.push_back(new Ghost(&GengarTexture, int(rand()), &Background4, 82.f, 80.f));
							}

							// Draw Gengar
							for (auto* i : Gengar)
								i->Draw(window);

							window.setView(view);
							window.display();
						}
					}
					if (player.GetPosition().x > 288 * 4 && player.GetPosition().x < 304 * 4 && player.GetPosition().y > 352 * 4 && player.GetPosition().y < 368 * 4)
					{
						//Die 3
						std::cout << "DiE3";
						Platform player_Die(&dieTexture, sf::Vector2f(56.f * 2, 82.f * 1.5), sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 15));
						Platform Text_Die(&TextDieMushroom, sf::Vector2f(1000, 120), sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 400));
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
							Background4.Draw(window);

							player_Die.Draw(window);
							Text_Die.Draw(window);

							trap2_Mushroom1.Draw(window);
							trap2_Mushroom2.Draw(window);
							trap2_Mushroom4.Draw(window);
							trap2_Mushroom5.Draw(window);
							trap2_Mushroom6.Draw(window);

							//Gengar Update
							int index = 0;
							for (auto* i : Gengar)
							{
								i->Update();
								if (i->getDirection() == 0) // Top
								{
									if (i->GetPosition().y > i->getMapsizeY())
									{
										delete Gengar.at(index);
										Gengar.erase(Gengar.begin() + index);
										index--;
									}
								}
								if (i->getDirection() == 1) // Right
								{
									if (i->GetPosition().x < 0)
									{
										delete Gengar.at(index);
										Gengar.erase(Gengar.begin() + index);
										index--;
									}
								}
								if (i->getDirection() == 2) // Left
								{
									if (i->GetPosition().x > i->getMapsizeX())
									{
										delete Gengar.at(index);
										Gengar.erase(Gengar.begin() + index);
										index--;
									}
								}
								if (i->getDirection() == 3) // Bottom
								{
									if (i->GetPosition().y < 0)
									{
										delete Gengar.at(index);
										Gengar.erase(Gengar.begin() + index);
										index--;
									}
								}
								index++;
							}

							// Gengar Limited
							if (Gengar.size() < 4)
							{
								Gengar.push_back(new Ghost(&GengarTexture, int(rand()), &Background4, 82.f, 80.f));
							}

							// Draw Gengar
							for (auto* i : Gengar)
								i->Draw(window);

							window.setView(view);
							window.display();
						}
					}
					if (player.GetPosition().x > 240 * 4 && player.GetPosition().x < 256 * 4 && player.GetPosition().y > 352 * 4 && player.GetPosition().y < 368 * 4)
					{
						//Die 4
						std::cout << "DiE4";
						Platform player_Die(&dieUpTexture, sf::Vector2f(56.f * 2, 82.f * 1.5), sf::Vector2f(player.GetPosition().x, player.GetPosition().y - 15));
						Platform Text_Die(&TextDieMushroom, sf::Vector2f(1000, 120), sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 400));
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
							Background4.Draw(window);

							player_Die.Draw(window);
							Text_Die.Draw(window);

							trap2_Mushroom1.Draw(window);
							trap2_Mushroom2.Draw(window);
							trap2_Mushroom3.Draw(window);
							trap2_Mushroom5.Draw(window);
							trap2_Mushroom6.Draw(window);

							//Gengar Update
							int index = 0;
							for (auto* i : Gengar)
							{
								i->Update();
								if (i->getDirection() == 0) // Top
								{
									if (i->GetPosition().y > i->getMapsizeY())
									{
										delete Gengar.at(index);
										Gengar.erase(Gengar.begin() + index);
										index--;
									}
								}
								if (i->getDirection() == 1) // Right
								{
									if (i->GetPosition().x < 0)
									{
										delete Gengar.at(index);
										Gengar.erase(Gengar.begin() + index);
										index--;
									}
								}
								if (i->getDirection() == 2) // Left
								{
									if (i->GetPosition().x > i->getMapsizeX())
									{
										delete Gengar.at(index);
										Gengar.erase(Gengar.begin() + index);
										index--;
									}
								}
								if (i->getDirection() == 3) // Bottom
								{
									if (i->GetPosition().y < 0)
									{
										delete Gengar.at(index);
										Gengar.erase(Gengar.begin() + index);
										index--;
									}
								}
								index++;
							}

							// Gengar Limited
							if (Gengar.size() < 4)
							{
								Gengar.push_back(new Ghost(&GengarTexture, int(rand()), &Background4, 82.f, 80.f));
							}

							// Draw Gengar
							for (auto* i : Gengar)
								i->Draw(window);

							window.setView(view);
							window.display();
						}
					}
					if (player.GetPosition().x > 208 * 4 && player.GetPosition().x < 224 * 4 && player.GetPosition().y > 384 * 4 && player.GetPosition().y < 400 * 4)
					{
						//Die 5
						std::cout << "DiE5";
						Platform player_Die(&dieTexture, sf::Vector2f(56.f * 2, 82.f * 1.5), sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 15));
						Platform Text_Die(&TextDieMushroom, sf::Vector2f(1000, 120), sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 400));
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
							Background4.Draw(window);

							player_Die.Draw(window);
							Text_Die.Draw(window);

							trap2_Mushroom1.Draw(window);
							trap2_Mushroom2.Draw(window);
							trap2_Mushroom3.Draw(window);
							trap2_Mushroom4.Draw(window);
							trap2_Mushroom6.Draw(window);

							//Gengar Update
							int index = 0;
							for (auto* i : Gengar)
							{
								i->Update();
								if (i->getDirection() == 0) // Top
								{
									if (i->GetPosition().y > i->getMapsizeY())
									{
										delete Gengar.at(index);
										Gengar.erase(Gengar.begin() + index);
										index--;
									}
								}
								if (i->getDirection() == 1) // Right
								{
									if (i->GetPosition().x < 0)
									{
										delete Gengar.at(index);
										Gengar.erase(Gengar.begin() + index);
										index--;
									}
								}
								if (i->getDirection() == 2) // Left
								{
									if (i->GetPosition().x > i->getMapsizeX())
									{
										delete Gengar.at(index);
										Gengar.erase(Gengar.begin() + index);
										index--;
									}
								}
								if (i->getDirection() == 3) // Bottom
								{
									if (i->GetPosition().y < 0)
									{
										delete Gengar.at(index);
										Gengar.erase(Gengar.begin() + index);
										index--;
									}
								}
								index++;
							}

							// Gengar Limited
							if (Gengar.size() < 4)
							{
								Gengar.push_back(new Ghost(&GengarTexture, int(rand()), &Background4, 82.f, 80.f));
							}

							// Draw Gengar
							for (auto* i : Gengar)
								i->Draw(window);

							window.setView(view);
							window.display();
						}
					}
					if (player.GetPosition().x > 192 * 4 && player.GetPosition().x < 208 * 4 && player.GetPosition().y > 336 * 4 && player.GetPosition().y < 352 * 4)
					{
						//Die 6
						std::cout << "DiE6";
						Platform player_Die(&dieLeftTexture, sf::Vector2f(56.f * 2, 82.f * 1.5), sf::Vector2f(player.GetPosition().x, player.GetPosition().y));
						Platform Text_Die(&TextDieMushroom, sf::Vector2f(1000, 120), sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 400));
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
							Background4.Draw(window);

							player_Die.Draw(window);
							Text_Die.Draw(window);

							trap2_Mushroom1.Draw(window);
							trap2_Mushroom2.Draw(window);
							trap2_Mushroom3.Draw(window);
							trap2_Mushroom4.Draw(window);
							trap2_Mushroom5.Draw(window);

							//Gengar Update
							int index = 0;
							for (auto* i : Gengar)
							{
								i->Update();
								if (i->getDirection() == 0) // Top
								{
									if (i->GetPosition().y > i->getMapsizeY())
									{
										delete Gengar.at(index);
										Gengar.erase(Gengar.begin() + index);
										index--;
									}
								}
								if (i->getDirection() == 1) // Right
								{
									if (i->GetPosition().x < 0)
									{
										delete Gengar.at(index);
										Gengar.erase(Gengar.begin() + index);
										index--;
									}
								}
								if (i->getDirection() == 2) // Left
								{
									if (i->GetPosition().x > i->getMapsizeX())
									{
										delete Gengar.at(index);
										Gengar.erase(Gengar.begin() + index);
										index--;
									}
								}
								if (i->getDirection() == 3) // Bottom
								{
									if (i->GetPosition().y < 0)
									{
										delete Gengar.at(index);
										Gengar.erase(Gengar.begin() + index);
										index--;
									}
								}
								index++;
							}

							// Gengar Limited
							if (Gengar.size() < 4)
							{
								Gengar.push_back(new Ghost(&GengarTexture, int(rand()), &Background4, 82.f, 80.f));
							}

							// Draw Gengar
							for (auto* i : Gengar)
								i->Draw(window);

							window.setView(view);
							window.display();
						}
					}
				}

				// Trap3 Medaim Way
				if (player.GetPosition().x > 176 * 4 && player.GetPosition().x < 208 * 4 && player.GetPosition().y > 480 * 4 && player.GetPosition().y < 496 * 4)
				{
					std::cout << "\nDIE\n";
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
					{
						Platform player_Die(&dieTexture, sf::Vector2f(56.f * 2, 82.f * 1.5), sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 15));
						Platform SadudKha_Die(&TextSadudKha, sf::Vector2f(1000, 120), sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 400));
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
							Background4.Draw(window);
							player_Die.Draw(window);

							SadudKha_Die.Draw(window);

							//Gengar Update
							int index = 0;
							for (auto* i : Gengar)
							{
								i->Update();
								if (i->getDirection() == 0) // Top
								{
									if (i->GetPosition().y > i->getMapsizeY())
									{
										delete Gengar.at(index);
										Gengar.erase(Gengar.begin() + index);
										index--;
									}
								}
								if (i->getDirection() == 1) // Right
								{
									if (i->GetPosition().x < 0)
									{
										delete Gengar.at(index);
										Gengar.erase(Gengar.begin() + index);
										index--;
									}
								}
								if (i->getDirection() == 2) // Left
								{
									if (i->GetPosition().x > i->getMapsizeX())
									{
										delete Gengar.at(index);
										Gengar.erase(Gengar.begin() + index);
										index--;
									}
								}
								if (i->getDirection() == 3) // Bottom
								{
									if (i->GetPosition().y < 0)
									{
										delete Gengar.at(index);
										Gengar.erase(Gengar.begin() + index);
										index--;
									}
								}
								index++;
							}

							// Gengar Limited
							if (Gengar.size() < 4)
							{
								Gengar.push_back(new Ghost(&GengarTexture, int(rand()), &Background4, 82.f, 80.f));
							}

							// Draw Gengar
							for (auto* i : Gengar)
								i->Draw(window);

							window.setView(view);
							window.display();
						}
					}
					else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
					{
						Platform player_Die(&dieUpTexture, sf::Vector2f(56.f * 2, 82.f * 1.5), sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 32));
						Platform SadudKha_Die(&TextSadudKha, sf::Vector2f(1000, 120), sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 400));
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
							Background4.Draw(window);
							player_Die.Draw(window);

							SadudKha_Die.Draw(window);

							//Gengar Update
							int index = 0;
							for (auto* i : Gengar)
							{
								i->Update();
								if (i->getDirection() == 0) // Top
								{
									if (i->GetPosition().y > i->getMapsizeY())
									{
										delete Gengar.at(index);
										Gengar.erase(Gengar.begin() + index);
										index--;
									}
								}
								if (i->getDirection() == 1) // Right
								{
									if (i->GetPosition().x < 0)
									{
										delete Gengar.at(index);
										Gengar.erase(Gengar.begin() + index);
										index--;
									}
								}
								if (i->getDirection() == 2) // Left
								{
									if (i->GetPosition().x > i->getMapsizeX())
									{
										delete Gengar.at(index);
										Gengar.erase(Gengar.begin() + index);
										index--;
									}
								}
								if (i->getDirection() == 3) // Bottom
								{
									if (i->GetPosition().y < 0)
									{
										delete Gengar.at(index);
										Gengar.erase(Gengar.begin() + index);
										index--;
									}
								}
								index++;
							}

							// Gengar Limited
							if (Gengar.size() < 4)
							{
								Gengar.push_back(new Ghost(&GengarTexture, int(rand()), &Background4, 82.f, 80.f));
							}

							// Draw Gengar
							for (auto* i : Gengar)
								i->Draw(window);

							window.setView(view);
							window.display();
						}
					}
					
				}

				/*.................................Player...Gengar.................................*/

				// Draw Player
				player.Draw(window);
				// Draw Gengar
				for (auto* i : Gengar)
					i->Draw(window);

				/*............................Trap.........AfterDraw_Player........................*/

				// Door1 && Door2 Collision
				if (player.GetGlobalBounds().intersects(door1.GetGlobalBounds()) || player.GetGlobalBounds().intersects(door2.GetGlobalBounds()))
				{
					Platform DoorLocked(&TextDoorLocked, sf::Vector2f(1000, 120), sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 400));
					DoorLocked.Draw(window);
				}

				// Dooe3 Collision
				if (player.GetGlobalBounds().intersects(door3.GetGlobalBounds()))
				{
					state = 5;
					break;
				}
				
				//CheckPoint
				if(player.GetGlobalBounds().intersects(Flower_checkPoint.GetGlobalBounds()))
				{ 
					if (checkPointMap4 == false)
					{
						Platform FoundCheckPoint(&TextFoundCheckPoint, sf::Vector2f(1000, 120), sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 400));
						
						std::cout << "CHECKPOINT ON\n";
						checkPoint = 4;
						checkPointMap4 = true;
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
							Background4.Draw(window);
							player.Draw(window);
							window.setView(view);
							FoundCheckPoint.Draw(window);
							window.display();
						}
					}
				}
				
				/*......................................Restart.......................................*/

				//Goto Restart
				if (restartGame)
				{
					std::cout << "\nRestart in State 1\n";
					break;
				}

				//Window Display
				window.setView(view);
				window.display();
			}
		}
		else if (state == 5)
		{
			//Background
			sf::Texture backgroundState5Texture;
			backgroundState5Texture.loadFromFile("assets/maps/Map5.png");
			Platform Background5(&backgroundState5Texture, sf::Vector2f(1280 * 64 / 16, 880 * 64 / 16), sf::Vector2f(1280 * 64 / 32, 880 * 64 / 32));

			// BitMap Init
			std::vector<Bitmap> block0;
			int outdoor[55][80] = {
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1},
									{1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1},
									{1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1},
									{1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1},
									{1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1},
									{1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1},
									{1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1},
									{1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1},
									{1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1},
									{1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1},
									{1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1},
									{1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1},
									{1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1},
									{1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1},
									{1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1},
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1},
									{1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1},
									{1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1},
									{1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1},
									{1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1},
									{1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1},
									{1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1},
									{1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1},
									{1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1},
									{1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
									{1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1},
									{1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
									{1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
									{1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
									{1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
									{1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
									{1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
									{1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
									{1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
									{1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
									{1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
									{1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
									{1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
									{1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
									{1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
									{1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
									{1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
									{1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
									{1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
									{1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
									{1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
									{1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
									{1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
			};

			// DrawBitMap
			for (int mapX = 0; mapX < 80; mapX++)
			{
				for (int mapY = 0; mapY < 55; mapY++)
				{
					if (outdoor[mapY][mapX] == 1)
					{
						Bitmap outdoor(nullptr, sf::Vector2f(((mapX) * 64.f) + 32.f, ((mapY) * 64.f) + 32.f), sf::Vector2f(64.f, 64.f));
						block0.push_back(outdoor);
					}
				}
			}

			// Ganger init
			Ghosty.push_back(new Ghost(&GengarTexture, int(rand()), &Background5, 82.f, 80.f));
			Ghosty.push_back(new Ghost(&GengarTexture, int(rand()), &Background5, 82.f, 80.f));
			Ghosty.push_back(new Ghost(&GengarTexture, int(rand()), &Background5, 82.f, 80.f));
			Ghosty.push_back(new Ghost(&GengarTexture, int(rand()), &Background5, 82.f, 80.f));
			Ghosty.push_back(new Ghost(&GengarTexture, int(rand()), &Background5, 82.f, 80.f));
			Ghosty.push_back(new Ghost(&GengarTexture, int(rand()), &Background5, 82.f, 80.f));
			Ghosty.push_back(new Ghost(&GengarTexture, int(rand()), &Background5, 82.f, 80.f));
			Ghosty.push_back(new Ghost(&GengarTexture, int(rand()), &Background5, 82.f, 80.f));
			Ghosty.push_back(new Ghost(&GengarTexture, int(rand()), &Background5, 82.f, 80.f));
			Ghosty.push_back(new Ghost(&GengarTexture, int(rand()), &Background5, 82.f, 80.f));

			// Insect init
			Insect insect_Ghost1(&GengarTexture, 16.0 * 4, 19.0 *4, sf::Vector2f(1162.0 * 4, 416.0 * 4), 3);
			bool check_insect_Ghost1 = false;

			// Trap init
			Platform trap1_Mushroom(&mushroomTexture, sf::Vector2f(64, 64), sf::Vector2f((1184 - 8) * 4, (256 - 8) * 4));
			bool check_trap1_Mushroom = false;
			Platform trap1_Jar(nullptr, sf::Vector2f(70, 70), sf::Vector2f((1184 - 8) * 4, (432 - 8) * 4));
			Platform trap1_Snake(&snakeTexture, sf::Vector2f(24, 36), sf::Vector2f((1177 ) * 4, (417 ) * 4));

			Platform trap2_Mushroom_1(&mushroomTexture, sf::Vector2f(64, 64), sf::Vector2f((656 - 8) * 4, (576 - 8) * 4));
			Platform trap2_Mushroom_2(&mushroomTexture, sf::Vector2f(64, 64), sf::Vector2f((672 - 8) * 4, (576 - 8) * 4));
			
			// label init
			Platform label(nullptr, sf::Vector2f(66, 66), sf::Vector2f((992 - 8) * 4, (400 - 8) * 4));
			
			// Pokeball init
			Platform Pokeball_1(&pokeballTexture, sf::Vector2f(64, 64), sf::Vector2f((848 - 8) * 4, (96 - 8) * 4));
			bool check_Pokeball_1 = false;

			// Flower init
			Platform flower_Checkpoint_1(&flowerItemTexture, sf::Vector2f(64, 64), sf::Vector2f((672 - 8) * 4, (816 - 8) * 4));

			// Stone init
			Platform stone_Checkpoint1(&stoneTexture, sf::Vector2f(64, 64), sf::Vector2f((672 - 8) * 4, (816 - 8) * 4));
			bool check_FlowerToStone = false;

			//---------------------------------------------Run Game---------------------------------------------
			player.SetPosition(1160 * 4, 48 * 4);
			while (window.isOpen())
			{
				//------------------------------Time Event------------------------------//

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

				//------------------------------status Update------------------------------//

				// Update Player
				player.Update(deltaTime);

				// Status Insect
				if (player.GetPosition().y > 90 * 4 && player.GetPosition().y < 352.0 * 4)
				{
					check_insect_Ghost1 = true;
				}
				else
				{
					check_insect_Ghost1 = false;
				}

				// Muchroom status	
				if(player.GetPosition().y >= 224 * 4)
				{
					check_trap1_Mushroom = true;
				}
				
				// Gengar Update
				int index = 0;
				for (auto* i : Ghosty)
				{
					i->Update();
					if (i->getDirection() == 0) // Top
					{
						if (i->GetPosition().y > 880 * 4)
						{
							delete Ghosty.at(index);
							Ghosty.erase(Ghosty.begin() + index);
							index--;
						}
					}
					if (i->getDirection() == 1) // Right
					{
						if (i->GetPosition().x < 0)
						{
							delete Ghosty.at(index);
							Ghosty.erase(Ghosty.begin() + index);
							index--;
						}
					}
					if (i->getDirection() == 2) // Left
					{
						if (i->GetPosition().x > 1280 * 4)
						{
							delete Ghosty.at(index);
							Ghosty.erase(Ghosty.begin() + index);
							index--;
						}
					}
					if (i->getDirection() == 3) // Bottom
					{
						if (i->GetPosition().y < 0)
						{
							delete Ghosty.at(index);
							Ghosty.erase(Ghosty.begin() + index);
							index--;
						}
					}
					index++;
				}

				// Gengar Limited
				if (Ghosty.size() < 10)
				{
					Ghosty.push_back(new Ghost(&GengarTexture, int(rand()), &Background5, 82.f, 80.f));
				}

				//------------------------------ Colllision ------------------------------//

				// BitMap Collision
				Collider playerCollision = player.GetCollider();
				for (int i = 0; i < block0.size(); i++)
					block0[i].getCollider().CheckCollision(playerCollision, 1.0f);

				// Gengar Collision
				for (auto* i : Ghosty)
				{
					if (i->GetGlobalBounds().intersects(player.GetGlobalBounds()))
					{
						std::cout << "\nDIE\n";
						Platform player_Die(&dieTexture, sf::Vector2f(56.f * 2, 82.f * 1.5), sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 15));
						Platform DieBy_Ghost(&TextDieGhost, sf::Vector2f(1000, 120), sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 400));
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
							Background5.Draw(window);
							player_Die.Draw(window);
							DieBy_Ghost.Draw(window);

							//Gengar Update
							int index = 0;
							for (auto* i : Ghosty)
							{
								i->Update();
								if (i->getDirection() == 0) // Top
								{
									if (i->GetPosition().y > 880 * 4)
									{
										delete Ghosty.at(index);
										Ghosty.erase(Ghosty.begin() + index);
										index--;
									}
								}
								if (i->getDirection() == 1) // Right
								{
									if (i->GetPosition().x < 0)
									{
										delete Ghosty.at(index);
										Ghosty.erase(Ghosty.begin() + index);
										index--;
									}
								}
								if (i->getDirection() == 2) // Left
								{
									if (i->GetPosition().x > 1280 * 4)
									{
										delete Ghosty.at(index);
										Ghosty.erase(Ghosty.begin() + index);
										index--;
									}
								}
								if (i->getDirection() == 3) // Bottom
								{
									if (i->GetPosition().y < 0)
									{
										delete Ghosty.at(index);
										Ghosty.erase(Ghosty.begin() + index);
										index--;
									}
								}
								index++;
							}

							// Gengar Limited
							if (Ghosty.size() < 10)
							{
								Ghosty.push_back(new Ghost(&GengarTexture, int(rand()), &Background5, 82.f, 80.f));
							}

							for (auto* i : Ghosty) //--> Draw Gengar
								i->Draw(window);

							if (!check_Pokeball_1)
							{
								Pokeball_1.Draw(window);
							}

							// Mushroom Draw
							if (check_trap1_Mushroom)
							{
								trap1_Mushroom.Draw(window);
							}

							//Window Display
							window.setView(view);
							window.display();
						}
					}
				}

				// Insect Colision
				if (player.GetGlobalBounds().intersects(insect_Ghost1.GetGlobalBounds()))
				{
					Platform player_Die(&dieTexture, sf::Vector2f(56.f * 2, 82.f * 1.5), sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 15));
					Platform DieBy_Ghost(&TextDieGhost, sf::Vector2f(1000, 120), sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 400));
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
						Background5.Draw(window);
						player_Die.Draw(window);
						DieBy_Ghost.Draw(window);

						//Gengar Update
						int index = 0;
						for (auto* i : Ghosty)
						{
							i->Update();
							if (i->getDirection() == 0) // Top
							{
								if (i->GetPosition().y > 880 * 4)
								{
									delete Ghosty.at(index);
									Ghosty.erase(Ghosty.begin() + index);
									index--;
								}
							}
							if (i->getDirection() == 1) // Right
							{
								if (i->GetPosition().x < 0)
								{
									delete Ghosty.at(index);
									Ghosty.erase(Ghosty.begin() + index);
									index--;
								}
							}
							if (i->getDirection() == 2) // Left
							{
								if (i->GetPosition().x > 1280 * 4)
								{
									delete Ghosty.at(index);
									Ghosty.erase(Ghosty.begin() + index);
									index--;
								}
							}
							if (i->getDirection() == 3) // Bottom
							{
								if (i->GetPosition().y < 0)
								{
									delete Ghosty.at(index);
									Ghosty.erase(Ghosty.begin() + index);
									index--;
								}
							}
							index++;
						}

						// Gengar Limited
						if (Ghosty.size() < 10)
						{
							Ghosty.push_back(new Ghost(&GengarTexture, int(rand()), &Background5, 82.f, 80.f));
						}

						for (auto* i : Ghosty) //--> Draw Gengar
							i->Draw(window);


						//Window Display
						window.setView(view);
						window.display();
					}
				}

				// Mushroom Collision
				if (player.GetGlobalBounds().intersects(trap1_Mushroom.GetGlobalBounds()))
				{
					Platform player_Die(&dieTexture, sf::Vector2f(56.f * 2, 82.f * 1.5), sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 15));
					Platform TextDieMushroomTrap1(&TextDieMushroom, sf::Vector2f(1000, 120), sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 400));
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
						Background5.Draw(window);
						
						player_Die.Draw(window);
						TextDieMushroomTrap1.Draw(window);

						//Gengar Update
						int index = 0;
						for (auto* i : Ghosty)
						{
							i->Update();
							if (i->getDirection() == 0) // Top
							{
								if (i->GetPosition().y > 880 * 4)
								{
									delete Ghosty.at(index);
									Ghosty.erase(Ghosty.begin() + index);
									index--;
								}
							}
							if (i->getDirection() == 1) // Right
							{
								if (i->GetPosition().x < 0)
								{
									delete Ghosty.at(index);
									Ghosty.erase(Ghosty.begin() + index);
									index--;
								}
							}
							if (i->getDirection() == 2) // Left
							{
								if (i->GetPosition().x > 1280 * 4)
								{
									delete Ghosty.at(index);
									Ghosty.erase(Ghosty.begin() + index);
									index--;
								}
							}
							if (i->getDirection() == 3) // Bottom
							{
								if (i->GetPosition().y < 0)
								{
									delete Ghosty.at(index);
									Ghosty.erase(Ghosty.begin() + index);
									index--;
								}
							}
							index++;
						}

						// Gengar Limited
						if (Ghosty.size() < 10)
						{
							Ghosty.push_back(new Ghost(&GengarTexture, int(rand()), &Background5, 82.f, 80.f));
						}

						for (auto* i : Ghosty) //--> Draw Gengar
							i->Draw(window);

						window.setView(view);
						window.display();
					}
				}

				// Goto check Point 3
				if (player.GetPosition().x < 800 * 4 && player.GetPosition().x > 780 * 4 && player.GetPosition().y > 400 * 4 && player.GetPosition().y < 432 * 4)
				{
					state = checkPoint;
					break;
				}

				// Hint CheckPoint
				if (!check_Pokeball_1)
				{
					if (player.GetGlobalBounds().intersects(Pokeball_1.GetGlobalBounds()))
					{
						check_Pokeball_1 = true;
						Platform TextHintCheckPoint(&HintCheckPoint, sf::Vector2f(1000, 120), sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 400));
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
							Background5.Draw(window);
							player.Draw(window);
							window.setView(view);
							TextHintCheckPoint.Draw(window);
							window.display();
						}
					}
				}

				// flower -> stone
				if (player.GetPosition().x > 640 * 4 && player.GetPosition().x < 672 * 4 && player.GetPosition().y > 592 * 4 && player.GetPosition().y < 624 * 4)
				{
					check_FlowerToStone = true;
				}

				//------------------------------  Draw ------------------------------//

				//Draw Player 
				view.setCenter(player.GetPosition());
				std::cout << "x = " << player.GetPosition().x << " y = " << player.GetPosition().y << std::endl;
				window.clear();
				Background5.Draw(window);
				player.Draw(window);   
				
				//Insect Draw
				if (check_insect_Ghost1)
				{
					std::cout << "snakeeeeee\n";
					if(insect_Ghost1.GetPosition().y > 40.0 * 4)
						insect_Ghost1.Draw(window);
					insect_Ghost1.Update();
				}

				// Ghost Draw
				for (auto* i : Ghosty) 
					i->Draw(window);
				
				// Mushroom Draw
				if (check_trap1_Mushroom)
				{
					trap1_Mushroom.Draw(window);
				}
				
				// Jar
				if (player.GetGlobalBounds().intersects(trap1_Jar.GetGlobalBounds()))
				{

					Platform PressToWatch(&TextToWatchInsideJar, sf::Vector2f(1000, 120), sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 400));
					PressToWatch.Draw(window);
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1))
					{
						//backgroundState5Texture.loadFromFile("assets/maps/Map5-Snake.png");
						Platform player_Die(&dieTexture, sf::Vector2f(56.f * 2, 82.f * 1.5), sf::Vector2f(player.GetPosition().x, player.GetPosition().y));
						Platform DieBy_Snake(&TextDieSnake, sf::Vector2f(1000, 120), sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 400));
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
							Background5.Draw(window);
							player_Die.Draw(window);
							DieBy_Snake.Draw(window);

							//Gengar Update
							int index = 0;
							for (auto* i : Ghosty)
							{
								i->Update();
								if (i->getDirection() == 0) // Top
								{
									if (i->GetPosition().y > 880 * 4)
									{
										delete Ghosty.at(index);
										Ghosty.erase(Ghosty.begin() + index);
										index--;
									}
								}
								if (i->getDirection() == 1) // Right
								{
									if (i->GetPosition().x < 0)
									{
										delete Ghosty.at(index);
										Ghosty.erase(Ghosty.begin() + index);
										index--;
									}
								}
								if (i->getDirection() == 2) // Left
								{
									if (i->GetPosition().x > 1280 * 4)
									{
										delete Ghosty.at(index);
										Ghosty.erase(Ghosty.begin() + index);
										index--;
									}
								}
								if (i->getDirection() == 3) // Bottom
								{
									if (i->GetPosition().y < 0)
									{
										delete Ghosty.at(index);
										Ghosty.erase(Ghosty.begin() + index);
										index--;
									}
								}
								index++;
							}

							// Gengar Limited
							if (Ghosty.size() < 10)
							{
								Ghosty.push_back(new Ghost(&GengarTexture, int(rand()), &Background5, 82.f, 80.f));
							}

							for (auto* i : Ghosty) //--> Draw Gengar
								i->Draw(window);

							trap1_Snake.Draw(window);
							//Window Display
							window.setView(view);
							window.display();
						}
					}
				}

				// Label
				if (player.GetGlobalBounds().intersects(label.GetGlobalBounds()))
				{
					Platform Label(&TextLabel, sf::Vector2f(1000, 120), sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 400));
					Label.Draw(window);
				}

				// Pokeball
				if (!check_Pokeball_1)
				{
					Pokeball_1.Draw(window);
				}

				// flower -> stone
				if (check_FlowerToStone)
				{
					stone_Checkpoint1.Draw(window);
					stone_Checkpoint1.GetCollider().CheckCollision(playerCollision, 1.0f);
				}
				else
				{
					flower_Checkpoint_1.Draw(window);
					
				}
				if (check_FlowerToStone)
				{
					trap2_Mushroom_1.Draw(window);
					trap2_Mushroom_2.Draw(window);

					if (player.GetGlobalBounds().intersects(trap2_Mushroom_1.GetGlobalBounds()) || player.GetGlobalBounds().intersects(trap2_Mushroom_2.GetGlobalBounds()))
					{
						Platform TextDieMushroomTrap1(&TextDieMushroom, sf::Vector2f(1000, 120), sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 400));
						Platform player_Die(&dieUpTexture, sf::Vector2f(56.f * 2, 82.f * 1.5), sf::Vector2f(player.GetPosition().x, player.GetPosition().y - 62));
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
							Background5.Draw(window);
							
							player_Die.Draw(window);
							TextDieMushroomTrap1.Draw(window);

							window.setView(view);
							window.display();
						}
					}
				}

				//------------------------------ Go Other State  ------------------------------//
				//Goto Restart
				if (restartGame)
				{
					std::cout << "\nRestart in State 1\n";
					break;
				}

				// Window Display
				window.setView(view);
				window.display();
			}
		}

		//============================= Restart =============================//
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
			std::cout << "Restart\n";

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
					state = checkPoint;
					checkGameRestart = false;
					restartGame = false;
					checkstate1_out = false;
					while (Gengar.size() != 0)
					{
						delete Gengar.at(0);
						Gengar.erase(Gengar.begin());
					}
					break;
				}

			}
		}
	}

	//==========================================================================================================================================// 
	// EndGame
	return 0;
}