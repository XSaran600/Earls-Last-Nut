#include "spritelib/spritelib.h"
#include "mainCharacter.h"
#include "Projectile.h"
#include "Enemy.h"
#include "Kiss.h"
#include "Doritos.h"
#include "Sausage.h"
#include "Lollipop.h"
#include "Projectile_E.h"
#include "babyTomato.h"
#include "Wall.h"
#include "Boss.h"


#include <Windows.h>
#include <fstream>
#include <streambuf>
#include <mmsystem.h>

using namespace spritelib;
using namespace std;
using namespace std::chrono;

bool timeToQuit = false;

Player mainCharacter(180, 144, 11, 11);
Projectile Magic_Attack(48, 30);

enum Areas
{
	area1, area2, area3, area4, area5, area6, area7, area8, area9, area10, bossFight
};

Areas currArea = area1;

bool A1 = false;
bool A2 = false;
bool A3 = false;
bool A4 = false;
bool A5 = false;
bool H1 = false;
bool H2 = false;
bool H3 = false;
bool B1 = false;
bool B2 = false;
bool BF = false;
bool transitioning = false;
bool blackScreen = false;
bool tutorial = false;
bool broken = false;

// Spawning of enemies
bool once1 = false;
bool once1_2 = false;
bool once2 = false;
bool once3 = false;
bool once4 = false;
bool once5 = false;
bool once6 = false;
bool once7 = false;
bool once8 = false;
bool once9 = false;
bool once10 = false;
bool onceBoss = false;
bool babies = false;

//Player mainCharacter("mainCharacter");

// Let's create some sprites!
Sprite background, player, health_bar, health_bar_trans, health_bar_empty, mana_bar, mana_bar_trans, mana_bar_empty, hunger_bar, hunger_bar_trans, hunger_bar_empty, fire, yellow_background, earl, mainMenu, controlMenu, earlPause, pauseMenu, pauseControl, BS, earlDeath, deathMenu, laser, story1, story2, story3, story4, story5, story6, story7, winScreen;

Sprite enemy1_Kiss, enemy2_Kiss, enemy3_Kiss, enemy4_Kiss;
Sprite enemy1_Doritos, enemy2_Doritos, enemy3_Doritos, enemy4_Doritos;
Sprite enemy1_Lollipop, enemy2_Lollipop, enemy3_Lollipop, enemy4_Lollipop;
Sprite enemy1_Sausage;
Sprite enemy1_babyTomato, enemy2_babyTomato, enemy3_babyTomato, enemy4_babyTomato;
Sprite bossSprite;

Sprite projectile1, projectile2, projectile3, projectile4;


// A vector container to hold all of the sprites we want to draw
vector<Sprite*> spritesToDraw;
vector<Sprite*> enemySprites;
vector<Enemy*> enemyList;

vector<Projectile_E*> projectileList;
vector<Sprite*> projectileSprites;

vector<Sprite*> menuSprites;
vector<Sprite*> pauseSprites;
vector<Sprite*> deathSprites;
vector<Sprite*> storySprites;
vector<Sprite*> winSprites;

vector<Wall> walls;

// Music Vector
vector<sf::Music*> musicVector;



// Back to front selection sort, to solve the depth issues with transparent sprites
void IterativeSelectionSort(std::vector<Sprite*>& a_sprites);

void processArea();
void processArrow();
void BSAnimation(Sprite&);

#pragma region Math Functions

Vector2 getProjection(Vector2, Vector2);
float getProjectionAmount(Vector2, Vector2);
Vector2 get_normal(Vector2);
void checkWallCollision(Wall, Player&);

#pragma endregion

void Update_Stats();

void retry();

void KeyboardFunc(Window::Key a_key, Window::EventType a_eventType)
{

	switch (a_eventType)
	{
	case Window::EventType::KeyPressed:
	{
		if (mainCharacter.game == true)
		{
			if (a_key == Window::Key::X)
			{
				cout << mainCharacter.getPositionX() << ", ";
			}

			if (a_key == Window::Key::Y)
			{
				cout << mainCharacter.getPositionY() - mainCharacter.getFrameSizeY() / 2 << endl;
			}

			if (a_key == Window::Key::Escape)
			{
				mainCharacter.beep.play();
				mainCharacter.game = false;
				mainCharacter.pause = true;
			}
			if (a_key == Window::Key::Right && (mainCharacter.currentstate == mainCharacter.Run || mainCharacter.currentstate == mainCharacter.Idle) && blackScreen == false)
			{
				mainCharacter.right_run = true;
				mainCharacter.isRunning = true;
				mainCharacter.currentstate = mainCharacter.Run;
			}

			if (a_key == Window::Key::Left && (mainCharacter.currentstate == mainCharacter.Run || mainCharacter.currentstate == mainCharacter.Idle) && blackScreen == false)
			{
				mainCharacter.left_run = true;
				mainCharacter.isRunning = true;
				mainCharacter.currentstate = mainCharacter.Run;
			}

			if (a_key == Window::Key::Up && (mainCharacter.currentstate == mainCharacter.Run || mainCharacter.currentstate == mainCharacter.Idle) && blackScreen == false)
			{
				mainCharacter.up_run = true;
				mainCharacter.isRunning = true;
				mainCharacter.currentstate = mainCharacter.Run;
			}
			if (a_key == Window::Key::Down && (mainCharacter.currentstate == mainCharacter.Run || mainCharacter.currentstate == mainCharacter.Idle) && blackScreen == false)
			{
				mainCharacter.down_run = true;
				mainCharacter.isRunning = true;
				mainCharacter.currentstate = mainCharacter.Run;
			}
			if (a_key == Window::Key::Q && mainCharacter.currentstate == mainCharacter.Idle)
			{
				mainCharacter.currentstate = mainCharacter.LightA;
			}
			if (a_key == Window::Key::W && mainCharacter.currentstate == mainCharacter.Idle)
			{
				mainCharacter.currentstate = mainCharacter.MediumA;
			}
			if (a_key == Window::Key::E && mainCharacter.currentstate == mainCharacter.Idle)
			{
				mainCharacter.currentstate = mainCharacter.HeavyA;

				if (currArea == area4 && mainCharacter.getFacingRight() && mainCharacter.getPositionX() >= 380 && (mainCharacter.getPositionY() <= 300) && (mainCharacter.getPositionY() >= 164))
					broken = true;

			}
			if (a_key == Window::Key::R && mainCharacter.currentstate == mainCharacter.Idle)
			{
				mainCharacter.currentstate = mainCharacter.Magic_Charge;
			}

		}
		else if (mainCharacter.menu == true)
		{
			math::Vector3 earlPosition = earl.get_position();

			if (a_key == Window::Key::Up && mainCharacter.controlsMenu == false)
			{
				if (earlPosition.y == mainCharacter.optionY)
				{
					earlPosition.y = mainCharacter.playY;
					earlPosition.x = mainCharacter.playX;
				}
				else if (earlPosition.y == mainCharacter.exitY)
				{
					earlPosition.y = mainCharacter.optionY;
					earlPosition.x = mainCharacter.optionX;
				}
			}
			if (a_key == Window::Key::Down && mainCharacter.controlsMenu == false)
			{
				if (earlPosition.y == mainCharacter.playY)
				{
					earlPosition.y = mainCharacter.optionY;
					earlPosition.x = mainCharacter.optionX;
				}
				else if (earlPosition.y == mainCharacter.optionY)
				{
					earlPosition.y = mainCharacter.exitY;
					earlPosition.x = mainCharacter.exitX;
				}
			}
			if (a_key == Window::Key::Return && mainCharacter.controlsMenu == false)
			{
				if (earlPosition.y == mainCharacter.optionY)
				{
					mainCharacter.beep.play();
					mainCharacter.controlsMenu = true;

				}
				if (earlPosition.y == mainCharacter.playY)
				{
					mainCharacter.beep.play();
					mainCharacter.menu = false;
					mainCharacter.story = true;
				}
				if (earlPosition.y == mainCharacter.exitY)
				{
					mainCharacter.beep.play();
					timeToQuit = true;
				}
			}
			if (a_key == Window::Key::Space && mainCharacter.controlsMenu == false)
			{
				if (earlPosition.y == mainCharacter.optionY)
				{
					mainCharacter.beep.play();
					mainCharacter.controlsMenu = true;

				}
				if (earlPosition.y == mainCharacter.playY)
				{
					mainCharacter.beep.play();
					mainCharacter.menu = false;
					mainCharacter.story = true;
				}
				if (earlPosition.y == mainCharacter.exitY)
				{
					mainCharacter.beep.play();
					timeToQuit = true;
				}
			}
			if (a_key == Window::Key::Escape && mainCharacter.controlsMenu == true)
			{
				mainCharacter.beep.play();
				mainCharacter.controlsMenu = false;
			}

			earl.set_position(earlPosition.x, earlPosition.y);
		}
		else if (mainCharacter.pause == true)
		{
			math::Vector3 earlPausePosition = earlPause.get_position();

			if (a_key == Window::Key::Escape && mainCharacter.controlsMenu == false)
			{
				mainCharacter.beep.play();
				mainCharacter.pause = false;
				mainCharacter.game = true;
			}
			if (a_key == Window::Key::Escape && mainCharacter.controlsMenu == true)
			{
				mainCharacter.beep.play();
				mainCharacter.controlsMenu = false;

			}

			if (a_key == Window::Key::Right)
			{
				earlPausePosition.x = mainCharacter.controlsX;
				earlPausePosition.y = mainCharacter.controlsY;
			}
			if (a_key == Window::Key::Left)
			{
				earlPausePosition.x = mainCharacter.continueX;
				earlPausePosition.y = mainCharacter.continueY;
			}
			if (a_key == Window::Key::Down)
			{
				earlPausePosition.x = mainCharacter.quitX;
				earlPausePosition.y = mainCharacter.quitY;
			}
			if (a_key == Window::Key::Up && earlPausePosition.y == mainCharacter.quitY)
			{
				earlPausePosition.x = mainCharacter.continueX;
				earlPausePosition.y = mainCharacter.continueY;
			}
			if (a_key == Window::Key::Return && mainCharacter.controlsMenu == false)
			{
				if (earlPausePosition.x == mainCharacter.controlsX)
				{
					mainCharacter.beep.play();
					mainCharacter.controlsMenu = true;
				}
				if (earlPausePosition.x == mainCharacter.continueX)
				{
					mainCharacter.beep.play();
					mainCharacter.pause = false;
					mainCharacter.game = true;
				}
				if (earlPausePosition.y == mainCharacter.quitY)
				{
					mainCharacter.beep.play();
					timeToQuit = true;

				}
			}
			if (a_key == Window::Key::Space && mainCharacter.controlsMenu == false)
			{
				if (earlPausePosition.x == mainCharacter.controlsX)
				{
					mainCharacter.beep.play();
					mainCharacter.controlsMenu = true;
				}
				if (earlPausePosition.x == mainCharacter.continueX)
				{
					mainCharacter.beep.play();
					mainCharacter.pause = false;
					mainCharacter.game = true;
				}
				if (earlPausePosition.y == mainCharacter.quitY)
				{
					mainCharacter.beep.play();
					timeToQuit = true;

				}
			}
			earlPause.set_position(earlPausePosition.x, earlPausePosition.y);
		}
		else if (mainCharacter.death == true)
		{
			math::Vector3 earlDeathPosition = earlDeath.get_position();

			if (a_key == Window::Key::Return)
			{
				if (earlDeathPosition.y == mainCharacter.retryY)
				{
					retry();
					mainCharacter.beep.play();
					mainCharacter.death = false;
					mainCharacter.game = true;
				}

				if (earlDeathPosition.y == mainCharacter.deathExitY)
				{
					mainCharacter.beep.play();
					timeToQuit = true;

				}
			}
			if (a_key == Window::Key::Space)
			{
				if (earlDeathPosition.y == mainCharacter.retryY)
				{
					retry();
					mainCharacter.beep.play();
					mainCharacter.death = false;
					mainCharacter.game = true;
				}

				if (earlDeathPosition.y == mainCharacter.deathExitY)
				{
					mainCharacter.beep.play();
					timeToQuit = true;

				}
			}
			if (a_key == Window::Key::Down)
			{
				//earlDeathPosition.x = mainCharacter.deathExitX;
				//earlDeathPosition.y = mainCharacter.deathExitY;
				earlDeathPosition.x = 270;
				earlDeathPosition.y = 50;
			}
			if (a_key == Window::Key::Up)
			{
				earlDeathPosition.x = mainCharacter.retryX;
				earlDeathPosition.y = mainCharacter.retryY;
			}

			earlDeath.set_position(earlDeathPosition.x, earlDeathPosition.y);

		}
		else if (mainCharacter.story == true)
		{

			if (a_key == Window::Key::Return)
			{
				mainCharacter.story_slide = mainCharacter.story_slide + 1;
			}
			if (a_key == Window::Key::Space)
			{
				mainCharacter.story_slide = mainCharacter.story_slide + 1;
			}
			if (a_key == Window::Key::Escape)
			{
				mainCharacter.story = false;
				mainCharacter.game = true;
			}
			if (mainCharacter.story_slide >= 7)
			{
				mainCharacter.story_slide = 7;
				mainCharacter.story = false;
				mainCharacter.game = true;
			}
		}
		else if (mainCharacter.win == true)
		{

			if (a_key == Window::Key::Return)
			{
				mainCharacter.beep.play();
				timeToQuit = true;
			}
			if (a_key == Window::Key::Space)
			{
				mainCharacter.beep.play();
				timeToQuit = true;
			}
			if (a_key == Window::Key::Escape)
			{
				mainCharacter.beep.play();
				timeToQuit = true;
			}
		}

		break;
	}
	case Window::EventType::KeyReleased:
	{
		if (mainCharacter.game == true)
		{
			if (a_key == Window::Key::Right)
			{
				mainCharacter.right_run = false;
				mainCharacter.isRunning = false;
				mainCharacter.done = false;
				mainCharacter.currentstate = mainCharacter.Idle;
				mainCharacter.vX = 0;
			}
			if (a_key == Window::Key::Left)
			{
				mainCharacter.left_run = false;
				mainCharacter.isRunning = false;
				mainCharacter.done = false;
				mainCharacter.currentstate = mainCharacter.Idle;
				mainCharacter.vX = 0;
			}
			if (a_key == Window::Key::Up)
			{
				mainCharacter.up_run = false;
				mainCharacter.isRunning = false;
				mainCharacter.done = false;
				mainCharacter.currentstate = mainCharacter.Idle;
			}
			if (a_key == Window::Key::Down)
			{
				mainCharacter.down_run = false;
				mainCharacter.isRunning = false;
				mainCharacter.done = false;
				mainCharacter.currentstate = mainCharacter.Idle;
			}
			if (a_key == Window::Key::R)
			{
				mainCharacter.currentstate = mainCharacter.Magic;
			}
		}
		else if (mainCharacter.menu == true)
		{

		}
		else if (mainCharacter.pause == true)
		{

		}

		break;
	}
	}

}

void MouseFunc(Window::Button a_button, int a_mouseX, int a_mouseY, Window::EventType a_eventType)
{
}

void handleEnemies()
{
	for (unsigned int i = 0; i < enemyList.size(); i++)
	{
		enemyList[i]->behave(mainCharacter, enemyList, enemySprites, projectileList, projectileSprites);
		enemySprites[i]->next_frame();

	}

	for (unsigned int i = 0; i < projectileList.size(); i++)
	{
		projectileList[i]->Update(enemyList, projectileList, projectileSprites, mainCharacter);
	}
}

void Update()
{
	//cout << mainCharacter.getPositionX() << ", " << mainCharacter.getPositionY() << endl;
	processArea();

	handleEnemies();

	Magic_Attack.Update(mainCharacter, fire, enemyList);

	mainCharacter.setMana(mainCharacter.getMana() + 0.1); // Regens Mana

	player.set_position(mainCharacter.getPositionX(), mainCharacter.getPositionY());

	if (currArea == bossFight)
	{
		static bool once = false;
		static steady_clock::time_point t1;
		steady_clock::time_point t2;
		duration<double> dt;

		if (!once)
		{
			once = true;
			t1 = steady_clock::now();
		}

		t2 = steady_clock::now();
		dt = duration_cast<duration<double>>(t2 - t1);

		if (dt.count() > 30)
		{
			switch (enemyList.size())
			{
			case 1:
				enemyList.push_back(new babyTomato("babyTomato", 3.0f, 500.0f, 200.0f, 60, 60, 1, 0.3, 10, 5, 1, false));
				enemySprites.push_back(&enemy1_babyTomato);

				enemySprites[1]->load_sprite_image("assets/images/Enemy_babyTomato/tomatoBaby.png")
					.set_sprite_frame_size(60, 60)
					.push_frame("idle", 0, 0)
					.push_frame("flinch", 0, 0)
					.push_frame("attack", 0, 0)
					.set_center(0.5f, 0.5f)
					.set_position(enemyList[1]->getPositionX(), enemyList[1]->getPositionY())
					.set_animation("idle");

				t1 = t2;

				break;

			case 2:
				enemyList.push_back(new babyTomato("babyTomato", 3.0f, 500.0f, 200.0f, 60, 60, 1, 0.3, 10, 5, 1, false));
				enemySprites.push_back(&enemy2_babyTomato);

				enemySprites[2]->load_sprite_image("assets/images/Enemy_babyTomato/tomatoBaby.png")
					.set_sprite_frame_size(60, 60)
					.push_frame("idle", 0, 0)
					.push_frame("flinch", 0, 0)
					.push_frame("attack", 0, 0)
					.set_center(0.5f, 0.5f)
					.set_position(enemyList[2]->getPositionX(), enemyList[2]->getPositionY())
					.set_animation("idle");

				t1 = t2;

				break;

			case 3:
				enemyList.push_back(new babyTomato("babyTomato", 3.0f, 500.0f, 200.0f, 60, 60, 1, 0.3, 10, 5, 1, false));
				enemySprites.push_back(&enemy3_babyTomato);

				enemySprites[3]->load_sprite_image("assets/images/Enemy_babyTomato/tomatoBaby.png")
					.set_sprite_frame_size(60, 60)
					.push_frame("idle", 0, 0)
					.push_frame("flinch", 0, 0)
					.push_frame("attack", 0, 0)
					.set_center(0.5f, 0.5f)
					.set_position(enemyList[3]->getPositionX(), enemyList[3]->getPositionY())
					.set_animation("idle");

				t1 = t2;

				break;

			case 4:
				enemyList.push_back(new babyTomato("babyTomato", 3.0f, 500.0f, 200.0f, 60, 60, 1, 0.3, 10, 5, 1, false));
				enemySprites.push_back(&enemy4_babyTomato);

				enemySprites[4]->load_sprite_image("assets/images/Enemy_babyTomato/tomatoBaby.png")
					.set_sprite_frame_size(60, 60)
					.push_frame("idle", 0, 0)
					.push_frame("flinch", 0, 0)
					.push_frame("attack", 0, 0)
					.set_center(0.5f, 0.5f)
					.set_position(enemyList[4]->getPositionX(), enemyList[4]->getPositionY())
					.set_animation("idle");

				t1 = t2;

				break;

			default:
				t1 = t2;

			}
		}
	}
}

void DrawSprites()
{
	// IMPORTANT: Sprites NEED to be drawn from back to front! This is one sorting algorithm you could use
	//IterativeSelectionSort(spritesToDraw);
	// https://hub.jmonkeyengine.org/t/alpha-transparency-sorting-your-z-buffer-and-you/33709
	//for (auto itr = spritesToDraw.begin(), itrEnd = spritesToDraw.end(); itr != itrEnd; itr++)
	//	(*itr)->draw();
	/* we could just do the following to draw the four sprites
	but that would be silly since we have a list of sprites to draw
	stored, so all we need to do is go through the list and draw eaach
	sprite in the list */
	/* // silly way
	background.draw();
	donkeyKong.draw();
	ninja.draw();
	hagger.draw();
	*/


	// Let's draw each sprite
	if (mainCharacter.game == true)
	{
		for (unsigned int i = 0; i < spritesToDraw.size(); i++)
		{
			if (Magic_Attack.getIsAttacking() == true) // Makes it so that the projectile doesnt get drawn
			{
				spritesToDraw[i]->draw();
			}
			else if (i != 1)
			{
				spritesToDraw[i]->draw();
			}
		}

		for (unsigned int i = 0; i < projectileList.size(); i++) // Draws enemy projectile
		{
			projectileSprites[i]->draw();
		}

		if (enemyList.size() != 0)
		{
			for (unsigned int i = 0; i < enemyList.size(); i++)
			{
				if (enemyList[i]->getHealth() < enemyList[i]->getMaxHealth()) // makes enemies aggro if you hit a enemy
				{
					for (unsigned int i = 0; i < enemyList.size(); i++)
					{
						enemyList[i]->setAggro(true);
					}
				}
				if (enemyList[i]->getHealth() <= 0 && enemyList[i]->getName() == "Lollipop")
				{
					delete enemyList[i];
					enemyList.erase(enemyList.begin() + i);
					enemySprites.erase(enemySprites.begin() + i);

					delete projectileList[i];
					projectileList.erase(projectileList.begin() + i);
					projectileSprites.erase(projectileSprites.begin() + i);
					for (unsigned int i = 0; i < enemyList.size(); i++)
					{
						enemyList[i]->setAggro(true);
					}
					continue;
				}

				if (enemyList[i]->getHealth() <= 0 && enemyList[i]->getName() != "Sausage" && enemyList[i]->getName() != "Lollipop")
				{
					delete enemyList[i];
					enemyList.erase(enemyList.begin() + i);
					enemySprites.erase(enemySprites.begin() + i);
					for (unsigned int i = 0; i < enemyList.size(); i++)
					{
						enemyList[i]->setAggro(true);
					}
					continue;
				}
				else if (enemyList[i]->getHealth() <= 0 && enemyList[i]->getName() == "Sausage" && currArea != area3)
				{
					delete enemyList[i];
					enemyList.erase(enemyList.begin() + i);
					enemySprites.erase(enemySprites.begin() + i);
					continue;
				}



				if (enemyList[i]->checkRight() && !enemyList[i]->checkAttacking())
				{
					enemySprites[i]->set_flipped(true);
					enemySprites[i]->set_position(enemyList[i]->getPositionX(), enemyList[i]->getPositionY());
				}

				else if (!enemyList[i]->checkAttacking())
				{
					enemySprites[i]->set_flipped();
					enemySprites[i]->set_position(enemyList[i]->getPositionX(), enemyList[i]->getPositionY());
				}
				if (enemyList[i]->getPositionY() < mainCharacter.getPositionY())
				{
					spritesToDraw[2]->draw();
					enemySprites[i]->draw();
				}
				if (enemyList[i]->getPositionY() > mainCharacter.getPositionY() || enemyList[i]->getName() == "Sausage")
				{
					enemySprites[i]->draw();
					spritesToDraw[2]->draw();
				}

			}
		}



		if (mainCharacter.getSuperHunger() == true)
		{
			yellow_background.draw();
		}

		if (blackScreen)
		{
			BS.draw();
		}
	}
	else if (mainCharacter.menu == true)
	{
		if (mainCharacter.controlsMenu == false)
		{
			for (unsigned int i = 0; i < menuSprites.size() - 1; i++)
			{
				menuSprites[i]->draw();
			}
		}
		else
		{
			menuSprites[2]->draw();
		}

	}
	else if (mainCharacter.pause == true)
	{

		// Game Screen
		for (unsigned int i = 0; i < spritesToDraw.size(); i++)
		{
			if (Magic_Attack.getIsAttacking() == true) // Makes it so that the projectile doesnt get drawn
			{
				spritesToDraw[i]->draw();
			}
			else if (i != 1)
			{
				spritesToDraw[i]->draw();
			}
		}

		for (unsigned int i = 0; i < projectileList.size(); i++) // Draws enemy projectile
		{
			projectileSprites[i]->draw();
		}

		if (enemyList.size() != 0)
		{
			for (unsigned int i = 0; i < enemyList.size(); i++)
			{
				if (enemyList[i]->getHealth() < enemyList[i]->getMaxHealth()) // makes enemies aggro if you hit a enemy
				{
					for (unsigned int i = 0; i < enemyList.size(); i++)
					{
						enemyList[i]->setAggro(true);
					}
				}

				if (enemyList[i]->getHealth() <= 0 && enemyList[i]->getName() == "Lollipop")
				{
					delete enemyList[i];
					enemyList.erase(enemyList.begin() + i);
					enemySprites.erase(enemySprites.begin() + i);

					delete projectileList[i];
					projectileList.erase(projectileList.begin() + i);
					projectileSprites.erase(projectileSprites.begin() + i);
					for (unsigned int i = 0; i < enemyList.size(); i++)
					{
						enemyList[i]->setAggro(true);
					}
					continue;
				}

				if (enemyList[i]->getHealth() <= 0 && enemyList[i]->getName() != "Sausage" && enemyList[i]->getName() != "Lollipop")
				{
					delete enemyList[i];
					enemyList.erase(enemyList.begin() + i);
					enemySprites.erase(enemySprites.begin() + i);
					for (unsigned int i = 0; i < enemyList.size(); i++)
					{
						enemyList[i]->setAggro(true);
					}
					continue;
				}
				else if (enemyList[i]->getHealth() <= 0 && enemyList[i]->getName() == "Sausage" && currArea != area3)
				{
					delete enemyList[i];
					enemyList.erase(enemyList.begin() + i);
					enemySprites.erase(enemySprites.begin() + i);
					continue;
				}



				if (enemyList[i]->checkRight() && !enemyList[i]->checkAttacking())
				{
					enemySprites[i]->set_flipped(true);
					enemySprites[i]->set_position(enemyList[i]->getPositionX(), enemyList[i]->getPositionY());
				}

				else if (!enemyList[i]->checkAttacking())
				{
					enemySprites[i]->set_flipped();
					enemySprites[i]->set_position(enemyList[i]->getPositionX(), enemyList[i]->getPositionY());
				}

				if (enemyList[i]->getPositionY() < mainCharacter.getPositionY())
				{
					spritesToDraw[2]->draw();
					enemySprites[i]->draw();
				}
				if (enemyList[i]->getPositionY() > mainCharacter.getPositionY() || enemyList[i]->getName() == "Sausage")
				{
					enemySprites[i]->draw();
					spritesToDraw[2]->draw();
				}
			}
		}


		if (mainCharacter.getSuperHunger() == true)
		{
			yellow_background.draw();
		}

		if (blackScreen)
		{
			BS.draw();
		}

		// Pause Menu
		if (mainCharacter.controlsMenu == false)
		{
			for (unsigned int i = 0; i < pauseSprites.size() - 1; i++)
			{
				pauseSprites[i]->draw();
			}
		}
		else
		{
			pauseSprites[2]->draw();
		}

	}
	else if (mainCharacter.death == true)
	{
		// Game Screen
		for (unsigned int i = 0; i < spritesToDraw.size(); i++)
		{
			if (Magic_Attack.getIsAttacking() == true) // Makes it so that the projectile doesnt get drawn
			{
				spritesToDraw[i]->draw();
			}
			else if (i != 1)
			{
				spritesToDraw[i]->draw();
			}
		}

		for (unsigned int i = 0; i < projectileList.size(); i++) // Draws enemy projectile
		{
			projectileSprites[i]->draw();
		}

		if (enemyList.size() != 0)
		{
			for (unsigned int i = 0; i < enemyList.size(); i++)
			{
				if (enemyList[i]->getHealth() < enemyList[i]->getMaxHealth()) // makes enemies aggro if you hit a enemy
				{
					for (unsigned int i = 0; i < enemyList.size(); i++)
					{
						enemyList[i]->setAggro(true);
					}
				}

				if (enemyList[i]->getHealth() <= 0 && enemyList[i]->getName() == "Lollipop")
				{
					delete enemyList[i];
					enemyList.erase(enemyList.begin() + i);
					enemySprites.erase(enemySprites.begin() + i);

					delete projectileList[i];
					projectileList.erase(projectileList.begin() + i);
					projectileSprites.erase(projectileSprites.begin() + i);
					for (unsigned int i = 0; i < enemyList.size(); i++)
					{
						enemyList[i]->setAggro(true);
					}
					continue;
				}

				if (enemyList[i]->getHealth() <= 0 && enemyList[i]->getName() != "Sausage" && enemyList[i]->getName() != "Lollipop")
				{
					delete enemyList[i];
					enemyList.erase(enemyList.begin() + i);
					enemySprites.erase(enemySprites.begin() + i);
					for (unsigned int i = 0; i < enemyList.size(); i++)
					{
						enemyList[i]->setAggro(true);
					}
					continue;
				}
				else if (enemyList[i]->getHealth() <= 0 && enemyList[i]->getName() == "Sausage" && currArea != area3)
				{
					delete enemyList[i];
					enemyList.erase(enemyList.begin() + i);
					enemySprites.erase(enemySprites.begin() + i);
					continue;
				}



				if (enemyList[i]->checkRight() && !enemyList[i]->checkAttacking())
				{
					enemySprites[i]->set_flipped(true);
					enemySprites[i]->set_position(enemyList[i]->getPositionX(), enemyList[i]->getPositionY());
				}

				else if (!enemyList[i]->checkAttacking())
				{
					enemySprites[i]->set_flipped();
					enemySprites[i]->set_position(enemyList[i]->getPositionX(), enemyList[i]->getPositionY());
				}

				if (enemyList[i]->getPositionY() < mainCharacter.getPositionY())
				{
					spritesToDraw[2]->draw();
					enemySprites[i]->draw();
				}
				if (enemyList[i]->getPositionY() > mainCharacter.getPositionY() || enemyList[i]->getName() == "Sausage")
				{
					enemySprites[i]->draw();
					spritesToDraw[2]->draw();
				}
			}
		}


		if (mainCharacter.getSuperHunger() == true)
		{
			yellow_background.draw();
		}

		if (blackScreen)
		{
			BS.draw();
		}

		// Death Screen
		for (unsigned int i = 0; i < deathSprites.size(); i++)
		{
			deathSprites[i]->draw();
		}
	}
	else if (mainCharacter.story == true)
	{
		storySprites[mainCharacter.story_slide]->draw();
	}
	else if (mainCharacter.win == true)
	{
		winSprites[0]->draw();
	}
}

int main()
{

	// All Music
	// Main Menu Music
	sf::Music mainMenuMusic;
	if (!mainMenuMusic.openFromFile("_main_menu.ogg"))
	{
		cout << "Can't open _main_menu.ogg" << endl;
	}
	// Story Music
	sf::Music storyMusic;
	if (!storyMusic.openFromFile("_story_music.ogg"))
	{
		cout << "Can't open _story_music.ogg" << endl;
	}
	// Death Screen Music
	sf::Music deathMusic;
	if (!deathMusic.openFromFile("_death.ogg"))
	{
		cout << "Can't open _death.ogg" << endl;
	}
	// Street Music
	sf::Music streetMusic;
	if (!streetMusic.openFromFile("_game_background.ogg"))
	{
		cout << "Can't open _game_background.ogg" << endl;
	}
	// Lair Music
	sf::Music lairMusic;
	if (!lairMusic.openFromFile("_lair_background.ogg"))
	{
		cout << "Can't open _lair_background.ogg" << endl;
	}
	// Boss Music
	sf::Music bossMusic;
	if (!bossMusic.openFromFile("_boss_fight.ogg"))
	{
		cout << "Can't open _boss_fight.ogg" << endl;
	}
	// Low Health Music
	sf::Music lowHealthMusic;
	if (!lowHealthMusic.openFromFile("_Low_Health.wav"))
	{
		cout << "Can't open _Low_Health.wav" << endl;
	}

	// Music Vector
	musicVector.push_back(&mainMenuMusic);
	musicVector.push_back(&storyMusic);
	musicVector.push_back(&deathMusic);
	musicVector.push_back(&streetMusic);
	musicVector.push_back(&lairMusic);
	musicVector.push_back(&bossMusic);
	musicVector.push_back(&lowHealthMusic);

	// Loading Sound Effects
	// Beep
	if (!mainCharacter.beepBuffer.loadFromFile("_Beep.wav"))
	{
		cout << "Can't load _Beep.wav" << endl;
	}
	mainCharacter.beep.setBuffer(mainCharacter.beepBuffer);
	mainCharacter.beep.setVolume(50);

	// Slash
	if (!mainCharacter.slashBuffer.loadFromFile("_Slash_test.wav"))
	{
		cout << "Can't load _Slash_test.wav" << endl;
	}
	mainCharacter.slash.setBuffer(mainCharacter.slashBuffer);
	mainCharacter.slash.setVolume(50);

	// Magic
	if (!mainCharacter.magicBuffer.loadFromFile("_Magic_Attack.wav"))
	{
		cout << "Can't load _Magic_Attack.wav" << endl;
	}
	mainCharacter.magic.setBuffer(mainCharacter.slashBuffer);
	mainCharacter.magic.setVolume(50);


	// Let's make a game window. use the static function get_game_window to get a handle to the main game window
	Window& theGame = Window::get_game_window(); // This is a singleton, useful for managing one window https://en.wikipedia.org/wiki/Singleton_pattern
	theGame.init("MY GAME", 1080, 720)
		.set_screen_size(1080, 720)
		.set_keyboard_callback(KeyboardFunc)
		.set_mouse_callback(MouseFunc)
		.set_clear_color(255, 255, 0);
	Text::load_font("assets/times.ttf", "TimesNewRoman");

	// Let's load in the sprites
	// Backgrounds
	background.load_sprite_image("assets/images/Game Maps/First_Stage.png");

	const int x = 182;
	const int y = 146;

	player.load_sprite_image("assets/images/Final_Animation.png")
		.set_scale(180, 180)
		.set_center(0.5f, 0.5f)
		.set_sprite_frame_size(x, y)
		.set_position(90, 640)
		.push_frame("idle", 0, 0)
		.push_frame_row("run", 0, 0, x, 0, 8)
		.push_frame_row("magicAttack", 0, y, x, 0, 8)
		.push_frame_row("jump", 0, y * 2, x, 0, 8)
		.push_frame_row("lightAttack", 0, y * 3, x, 0, 11)
		.push_frame_row("mediumAttack", 0, y * 4, x, 0, 12)
		.push_frame_row("heavyAttack", 0, y * 5, 182, 0, 13)
		.set_animation("idle");

	// Dead Health Bar
	health_bar_empty.load_sprite_image("assets/images/Health Bar/Health_Bar_Empty.png")
		.set_sprite_frame_size(238, 38)
		.set_position(0, 682);

	// Red Health Bar
	health_bar.load_sprite_image("assets/images/Health Bar/Health_Bar_Red.png")
		.set_sprite_frame_size(238, 38)
		.set_position(0, 682);

	// Transparent (Alive) Health Bar
	health_bar_trans.load_sprite_image("assets/images/Health Bar/Health_Bar_Transparent.png")
		.set_sprite_frame_size(238, 38)
		.set_position(0, 682);

	// Empty Mana Bar
	mana_bar_empty.load_sprite_image("assets/images/Mana Bar/Mana Bar Empty.png")
		.set_sprite_frame_size(238, 38)
		.set_position(0, 644);

	// Blue Mana Bar
	mana_bar.load_sprite_image("assets/images/Mana Bar/Mana Bar Blue.png")
		.set_sprite_frame_size(238, 38)
		.set_position(0, 644);

	// Transparent Mana Bar
	mana_bar_trans.load_sprite_image("assets/images/Mana Bar/Mana Bar Meter.png")
		.set_sprite_frame_size(238, 38)
		.set_position(0, 644);

	// Empty Hunger Bar
	hunger_bar_empty.load_sprite_image("assets/images/Hunger Bar/Hunger Bar Empty.png")
		.set_sprite_frame_size(238, 38)
		.set_position(0, 606);

	// Yellow Hunger Bar
	hunger_bar.load_sprite_image("assets/images/Hunger Bar/Hunger Bar Yellow.png")
		.set_sprite_frame_size(238, 38)
		.set_position(-198, 606);

	// Transparent Hunger Bar
	hunger_bar_trans.load_sprite_image("assets/images/Hunger Bar/Hunger Bar Meter.png")
		.set_sprite_frame_size(238, 38)
		.set_position(0, 606);

	fire.load_sprite_image("assets/images/Fire.png")
		.set_sprite_frame_size(48, 30)
		.set_position(300, 200);

	yellow_background.load_sprite_image("assets/images/Yellow_Foreground.png")
		.set_sprite_frame_size(1080, 720)
		.set_position(0, 0);

	// Main Menu
	earl.load_sprite_image("assets/images/Game Screens/Earl.png")
		.set_sprite_frame_size(66, 50)
		.set_position(mainCharacter.playX, mainCharacter.playY);

	mainMenu.load_sprite_image("assets/images/Game Screens/Main Menu.png")
		.set_position(0, 0);

	controlMenu.load_sprite_image("assets/images/Game Screens/Control_Menu.png")
		.set_position(0, 0);

	// Pause Menu
	earlPause.load_sprite_image("assets/images/Game Screens/Earl_Pause.png")
		.set_sprite_frame_size(20, 15)
		.set_position(mainCharacter.continueX, mainCharacter.continueY);

	pauseMenu.load_sprite_image("assets/images/Game Screens/Pause_Screen.png")
		.set_position(0, 0);

	pauseControl.load_sprite_image("assets/images/Game Screens/Pause_Screen_Controls.png")
		.set_position(0, 0);

	// Death Screen
	earlDeath.load_sprite_image("assets/images/Game Screens/Earl_Orignal.png")
		.set_sprite_frame_size(129, 98)
		.set_position(mainCharacter.retryX, mainCharacter.retryY);

	deathMenu.load_sprite_image("assets/images/Game Screens/Death_Screen.png")
		.set_position(0, 0);

	// Tranistion sprite
	BS.load_sprite_image("assets/images/Game Maps/black.png")
		.set_position(0, 0)
		.push_frame_row("transition", 0, 0, 1080, 0, 3)
		.push_frame_row("transition", 2160, 0, -1080, 0, 3)
		.set_sprite_frame_size(1080, 720)
		.set_animation("transition");

	// Story
	story1.load_sprite_image("assets/images/Story/Story1.png")
		.set_position(0, 0);

	story2.load_sprite_image("assets/images/Story/Story2.png")
		.set_position(0, 0);

	story3.load_sprite_image("assets/images/Story/Story3.png")
		.set_position(0, 0);

	story4.load_sprite_image("assets/images/Story/Story4.png")
		.set_position(0, 0);

	story5.load_sprite_image("assets/images/Story/Story5.png")
		.set_position(0, 0);

	story6.load_sprite_image("assets/images/Story/Story6.png")
		.set_position(0, 0);

	story7.load_sprite_image("assets/images/Story/Story7.png")
		.set_position(0, 0);

	// Win
	winScreen.load_sprite_image("assets/images/Game Screens/winScreen.png")
		.set_position(0, 0);

	// Main Menu Vector
	menuSprites.push_back(&mainMenu);
	menuSprites.push_back(&earl);
	menuSprites.push_back(&controlMenu);

	// Pause Menu Vector
	pauseSprites.push_back(&pauseMenu);
	pauseSprites.push_back(&earlPause);
	pauseSprites.push_back(&pauseControl);

	// Death Screen Vector
	deathSprites.push_back(&deathMenu);
	deathSprites.push_back(&earlDeath);

	// Story Vector
	storySprites.push_back(&story1);
	storySprites.push_back(&story2);
	storySprites.push_back(&story3);
	storySprites.push_back(&story4);
	storySprites.push_back(&story5);
	storySprites.push_back(&story6);
	storySprites.push_back(&story7);

	// Win Screen
	winSprites.push_back(&winScreen);


	// Let's add them to our vector container
	spritesToDraw.push_back(&background);
	spritesToDraw.push_back(&fire);
	spritesToDraw.push_back(&player);
	spritesToDraw.push_back(&health_bar_empty);
	spritesToDraw.push_back(&health_bar);
	spritesToDraw.push_back(&health_bar_trans);
	spritesToDraw.push_back(&mana_bar_empty);
	spritesToDraw.push_back(&mana_bar);
	spritesToDraw.push_back(&mana_bar_trans);
	spritesToDraw.push_back(&hunger_bar_empty);
	spritesToDraw.push_back(&hunger_bar);
	spritesToDraw.push_back(&hunger_bar_trans);

	bool once_game = false;
	bool once_lair = false;
	bool once_boss = false;
	bool once_menu = false;
	bool once_pause = false;
	bool once_death = false;
	bool once_story = false;

	// IMPORTANT: This is how spritelib 2.0 handles the main game loop
	while (theGame.update(30))
	{
		if (mainCharacter.controller_reset == true)
		{
			retry();
			mainCharacter.controller_reset = false;
		}

		if (timeToQuit == true)
		{
			break;
		}
		if (mainCharacter.getHealth() < 30)
		{
			lowHealthMusic.setLoop(true);
			lowHealthMusic.setVolume(100 - mainCharacter.getHealth());
			lowHealthMusic.play();
		}
		else
		{
			lowHealthMusic.stop();
		}

		if (mainCharacter.getHealth() <= 0)
		{
			mainCharacter.death = true;
			mainCharacter.menu = false;
			mainCharacter.story = false;
			mainCharacter.game = false;
			mainCharacter.pause = false;
		}

		if (mainCharacter.game == true)
		{

			// Street
			if (currArea == area1 && once1 == false)
			{
				// Enemy
				enemyList.push_back(new Doritos("Doritos", 3.0f, 500.0f, 300.0f, 113, 126, 0.5, 0.7, 10, 300, 1, true));

				enemySprites.push_back(&enemy1_Doritos);

				for (int i = 0; i < enemySprites.size(); i++)
				{
					enemySprites[i]->load_sprite_image("assets/images/Enemy_Doritos/Dorito_Final.png")
						.set_sprite_frame_size(113, 126)
						.push_frame("idle", 0, 0)
						.push_frame("flinch", 113, 0)
						.push_frame("attack", 0, 0)
						.set_center(0.5f, 0.5f)
						.set_position(enemyList[i]->getPositionX(), enemyList[i]->getPositionY())
						.set_animation("idle");
				}
				once1 = true;
			}
			if (enemyList.size() <= 0 && currArea == area1 && once1_2 == false)
			{
				enemyList.push_back(new Doritos("Doritos", 3.0f, 1300.0f, 400.0f, 113, 126, 0.5, 0.7, 20, 300, 1, false));
				enemyList.push_back(new Doritos("Doritos", 3.0f, 1300.0f, 100.0f, 113, 126, 0.5, 0.7, 20, 300, 1, false));

				enemySprites.push_back(&enemy1_Doritos);
				enemySprites.push_back(&enemy2_Doritos);

				for (int i = 0; i < enemySprites.size(); i++)
				{
					enemySprites[i]->load_sprite_image("assets/images/Enemy_Doritos/Dorito_Final.png")
						.set_sprite_frame_size(113, 126)
						.push_frame("idle", 0, 0)
						.push_frame("flinch", 113, 0)
						.push_frame("attack", 0, 0)
						.set_center(0.5f, 0.5f)
						.set_position(enemyList[i]->getPositionX(), enemyList[i]->getPositionY())
						.set_animation("idle");
				}
				once1_2 = true;
			}

			if (currArea == area2 && once2 == false && mainCharacter.getPositionX() > 540)
			{
				enemyList.push_back(new Kiss("Kiss", 5.0f, 1200.00f, 230.0f, 144, 144, 0.5, 0.7, 30, 300, 2, false));
				enemyList.push_back(new Kiss("Kiss", 5.0f, -80.0f, 230.0f, 144, 144, 0.5, 0.7, 30, 300, 2, true));

				enemySprites.push_back(&enemy1_Kiss);
				enemySprites.push_back(&enemy2_Kiss);

				for (unsigned int i = 0; i < enemySprites.size(); i++)
				{
					enemySprites[i]->load_sprite_image("assets/images/Enemy_Kiss/Kiss_1.png")
						.set_sprite_frame_size(144, 144)
						.push_frame("idle", 0, 0)
						.push_frame("flinch", 0, 0)
						.push_frame_row("attack", 0, 0, 144, 0, 5)
						.set_center(0.5f, 0.5f)
						.set_position(enemyList[i]->getPositionX(), enemyList[i]->getPositionY())
						.set_animation("idle");
				}
				once2 = true;
			}
			if (currArea == area3 && once3 == false)
			{
				enemyList.push_back(new Sausage("Sausage", 5.0f, 750.0f, 200.0f, 161, 375, 0.5, 0.7, 10, 300, 1, false));

				enemySprites.push_back(&enemy1_Sausage);

				for (unsigned int i = 0; i < enemySprites.size(); i++)
				{
					enemySprites[i]->load_sprite_image("assets/images/Sausage Enemy/Sausage_Final.png")
						.set_sprite_frame_size(161, 375)
						.push_frame("idle", 0, 0)
						.push_frame("dead", 161, 0)
						.push_frame("flinch", 322, 0)
						.set_position(enemyList[i]->getPositionX(), enemyList[i]->getPositionY())
						.set_animation("idle");
				}
				once3 = true;
			}

			if (currArea == area5 && once4 == false)
			{
				// Enemy
				enemyList.push_back(new Kiss("Kiss", 5.0f, 850.00f, 290.0f, 144, 144, 0.5, 0.7, 30, 300, 2, false));
				enemyList.push_back(new Kiss("Kiss", 5.0f, 920.0f, 100.0f, 144, 144, 0.5, 0.7, 30, 300, 2, false));

				enemySprites.push_back(&enemy1_Kiss);
				enemySprites.push_back(&enemy2_Kiss);

				for (unsigned int i = 0; i < enemySprites.size(); i++)
				{
					enemySprites[i]->load_sprite_image("assets/images/Enemy_Kiss/Kiss_1.png")
						.set_sprite_frame_size(144, 144)
						.push_frame("idle", 0, 0)
						.push_frame("flinch", 0, 0)
						.push_frame_row("attack", 0, 0, 144, 0, 5)
						.set_center(0.5f, 0.5f)
						.set_rotation(0)
						.set_position(enemyList[i]->getPositionX(), enemyList[i]->getPositionY())
						.set_animation("idle");
				}
				once4 = true;
			}

			if (once_game == false && (currArea == area1 || currArea == area2 || currArea == area3 || currArea == area4 || currArea == area5)) // Street
			{
				for (int i = 0; i < musicVector.size() - 1; i++)
				{
					musicVector[i]->stop();
					musicVector[i]->setVolume(50);
				}
				streetMusic.setLoop(true);
				streetMusic.play();

				once_game = true;
				once_lair = false;
				once_boss = false;
				once_menu = false;
				once_pause = false;
				once_death = false;
				once_story = false;
			}

			// Lair
			if (currArea == area6 && once6 == false)
			{
				// Enemy
				enemyList.push_back(new Kiss("Kiss", 5.0f, 900.00f, 300, 144, 144, 0.5, 0.7, 30, 300, 2, false));
				enemyList.push_back(new Kiss("Kiss", 5.0f, 900.0f, 100.0f, 144, 144, 0.5, 0.7, 30, 300, 2, false));
				enemyList.push_back(new Doritos("Doritos", 5.0f, 800.0f, 200.0f, 113, 126, 0.5, 0.7, 20, 300, 1, false));


				enemySprites.push_back(&enemy1_Kiss);
				enemySprites.push_back(&enemy2_Kiss);
				enemySprites.push_back(&enemy3_Doritos);

				for (unsigned int i = 0; i < enemySprites.size() - 1; i++)
				{
					enemySprites[i]->load_sprite_image("assets/images/Enemy_Kiss/Kiss_1.png")
						.set_sprite_frame_size(144, 144)
						.push_frame("idle", 0, 0)
						.push_frame("flinch", 0, 0)
						.push_frame_row("attack", 0, 0, 144, 0, 5)
						.set_center(0.5f, 0.5f)
						.set_position(enemyList[i]->getPositionX(), enemyList[i]->getPositionY())
						.set_animation("idle");
				}

				enemySprites[2]->load_sprite_image("assets/images/Enemy_Doritos/Dorito_Final.png")
					.set_sprite_frame_size(113, 126)
					.push_frame("idle", 0, 0)
					.push_frame("flinch", 113, 0)
					.push_frame("attack", 0, 0)
					.set_center(0.5f, 0.5f)
					.set_position(enemyList[2]->getPositionX(), enemyList[2]->getPositionY())
					.set_animation("idle");

				once6 = true;
			}
			if (currArea == area7 && once7 == false && mainCharacter.getPositionX() > 540)
			{
				// Enemy
				enemyList.push_back(new Kiss("Kiss", 5.0f, 1200.0f, 300.0f, 144, 144, 0.5, 0.7, 30, 300, 2, false));
				enemyList.push_back(new Kiss("Kiss", 5.0f, 1200.0f, 100.0f, 144, 144, 0.5, 0.7, 30, 300, 2, false));
				enemyList.push_back(new Doritos("Doritos", 3.0f, -80.0f, 100.0f, 111, 126, 0.5, 0.7, 20, 300, 1, false));
				enemyList.push_back(new Doritos("Doritos", 3.0f, -80.0f, 300.0f, 111, 126, 0.5, 0.7, 20, 300, 1, false));

				enemySprites.push_back(&enemy1_Kiss);
				enemySprites.push_back(&enemy2_Kiss);
				enemySprites.push_back(&enemy3_Doritos);
				enemySprites.push_back(&enemy4_Doritos);

				for (unsigned int i = 0; i < enemySprites.size() - 2; i++)
				{
					enemySprites[i]->load_sprite_image("assets/images/Enemy_Kiss/Kiss_1.png")
						.set_sprite_frame_size(144, 144)
						.push_frame("idle", 0, 0)
						.push_frame("flinch", 0, 0)
						.push_frame_row("attack", 0, 0, 144, 0, 5)
						.set_center(0.5f, 0.5f)
						.set_position(enemyList[i]->getPositionX(), enemyList[i]->getPositionY())
						.set_animation("idle");
				}

				enemySprites[2]->load_sprite_image("assets/images/Enemy_Doritos/Dorito_Final.png")
					.set_sprite_frame_size(113, 126)
					.push_frame("idle", 0, 0)
					.push_frame("flinch", 113, 0)
					.push_frame("attack", 0, 0)
					.set_center(0.5f, 0.5f)
					.set_position(enemyList[2]->getPositionX(), enemyList[2]->getPositionY())
					.set_animation("idle");

				enemySprites[3]->load_sprite_image("assets/images/Enemy_Doritos/Dorito_Final.png")
					.set_sprite_frame_size(113, 126)
					.push_frame("idle", 0, 0)
					.push_frame("flinch", 113, 0)
					.push_frame("attack", 0, 0)
					.set_center(0.5f, 0.5f)
					.set_position(enemyList[3]->getPositionX(), enemyList[3]->getPositionY())
					.set_animation("idle");

				once7 = true;
			}

			if (currArea == area8 && once8 == false && mainCharacter.getPositionX() > 540)
			{
				// Enemy
				enemyList.push_back(new Kiss("Kiss", 5.0f, 1200.0f, 300.0f, 144, 144, 0.5, 0.7, 30, 300, 2, false));
				enemyList.push_back(new Kiss("Kiss", 5.0f, 1200.0f, 100.0f, 144, 144, 0.5, 0.7, 30, 300, 2, false));
				enemyList.push_back(new Kiss("Kiss", 5.0f, -80.0f, 100.0f, 144, 144, 0.5, 0.7, 30, 300, 2, true));
				enemyList.push_back(new Kiss("Kiss", 5.0f, -80.0f, 300.0f, 144, 144, 0.5, 0.7, 30, 300, 2, true));


				enemySprites.push_back(&enemy1_Kiss);
				enemySprites.push_back(&enemy2_Kiss);
				enemySprites.push_back(&enemy3_Kiss);
				enemySprites.push_back(&enemy4_Kiss);

				for (unsigned int i = 0; i < enemySprites.size(); i++)
				{
					enemySprites[i]->load_sprite_image("assets/images/Enemy_Kiss/Kiss_1.png")
						.set_sprite_frame_size(144, 144)
						.push_frame("idle", 0, 0)
						.push_frame("flinch", 0, 0)
						.push_frame_row("attack", 0, 0, 144, 0, 5)
						.set_center(0.5f, 0.5f)
						.set_position(enemyList[i]->getPositionX(), enemyList[i]->getPositionY())
						.set_animation("idle");
				}
				once8 = true;
			}

			if (currArea == area9 && once9 == false)
			{
				// Enemy
				enemyList.push_back(new Lollipop("Lollipop", 5.0f, 1000.0f, 300.0f, 59, 132, 1, 1.5, 30, 300, 3, false));
				projectileList.push_back(new Projectile_E(57, 17));

				enemySprites.push_back(&enemy1_Lollipop);
				projectileSprites.push_back(&projectile1);

				for (unsigned int i = 0; i < enemySprites.size(); i++)
				{
					enemySprites[i]->load_sprite_image("assets/images/lollipopEnemy/Lollipop_Final.png")
						.set_sprite_frame_size(59, 132)
						.push_frame("idle", 59, 0)
						.push_frame("attack", 59, 0)
						.push_frame("flinch", 118, 0)
						.set_center(0.5f, 0.5f)
						.set_position(enemyList[i]->getPositionX(), enemyList[i]->getPositionY())
						.set_animation("idle");

					projectileSprites[i]->load_sprite_image("assets/images/lollipopEnemy/lolipopEnemyLazer2.png")
						.set_sprite_frame_size(57, 17)
						.push_frame("idle", 0, 0)
						.set_position(enemyList[i]->getPositionX(), enemyList[i]->getPositionY())
						.set_animation("idle");
				}

				once9 = true;
			}

			if (currArea == area10 && once10 == false && mainCharacter.getPositionX() > 540)
			{
				// Enemy
				enemyList.push_back(new Lollipop("Lollipop", 5.0f, 1000.0f, 300.0f, 59, 132, 1, 1.5, 30, 300, 3, false));
				enemyList.push_back(new Lollipop("Lollipop", 5.0f, 100.0f, 300.0f, 59, 132, 1, 1.5, 30, 300, 3, true));
				enemyList.push_back(new Kiss("Kiss", 5.0f, 1200.0f, 300.0f, 144, 144, 0.5, 0.7, 30, 300, 2, false));
				enemyList.push_back(new Kiss("Kiss", 5.0f, 1200.0f, 100.0f, 144, 144, 0.5, 0.7, 30, 300, 2, false));
				enemyList.push_back(new Kiss("Kiss", 5.0f, -80.0f, 100.0f, 144, 144, 0.5, 0.7, 30, 300, 2, true));
				enemyList.push_back(new Kiss("Kiss", 5.0f, -80.0f, 300.0f, 144, 144, 0.5, 0.7, 30, 300, 2, true));

				projectileList.push_back(new Projectile_E(57, 17));
				projectileList.push_back(new Projectile_E(57, 17));

				enemySprites.push_back(&enemy1_Lollipop);
				enemySprites.push_back(&enemy2_Lollipop);
				enemySprites.push_back(&enemy1_Kiss);
				enemySprites.push_back(&enemy2_Kiss);
				enemySprites.push_back(&enemy3_Kiss);
				enemySprites.push_back(&enemy4_Kiss);

				projectileSprites.push_back(&projectile1);
				projectileSprites.push_back(&projectile2);


				for (unsigned int i = 0; i < enemySprites.size() - 4; i++)
				{
					enemySprites[i]->load_sprite_image("assets/images/lollipopEnemy/Lollipop_Final.png")
						.set_sprite_frame_size(59, 132)
						.push_frame("idle", 59, 0)
						.push_frame("attack", 59, 0)
						.push_frame("flinch", 118, 0)
						.set_center(0.5f, 0.5f)
						.set_position(enemyList[i]->getPositionX(), enemyList[i]->getPositionY())
						.set_animation("idle");

					projectileSprites[i]->load_sprite_image("assets/images/lollipopEnemy/lolipopEnemyLazer2.png")
						.set_sprite_frame_size(57, 17)
						.push_frame("idle", 0, 0)
						.set_position(enemyList[i]->getPositionX(), enemyList[i]->getPositionY())
						.set_animation("idle");
				}
				for (unsigned int i = 2; i < enemySprites.size(); i++)
				{
					enemySprites[i]->load_sprite_image("assets/images/Enemy_Kiss/Kiss_1.png")
						.set_sprite_frame_size(144, 144)
						.push_frame("idle", 0, 0)
						.push_frame("flinch", 0, 0)
						.push_frame_row("attack", 0, 0, 144, 0, 5)
						.set_center(0.5f, 0.5f)
						.set_position(enemyList[i]->getPositionX(), enemyList[i]->getPositionY())
						.set_animation("idle");
				}

				once10 = true;
			}


			if (once_lair == false && (currArea == area6 || currArea == area7 || currArea == area8 || currArea == area9)) // Lair
			{
				for (int i = 0; i < musicVector.size() - 1; i++)
				{
					musicVector[i]->stop();
					musicVector[i]->setVolume(50);
				}
				lairMusic.setLoop(true);
				lairMusic.play();

				once_game = false;
				once_lair = true;
				once_boss = false;
				once_menu = false;
				once_pause = false;
				once_death = false;
				once_story = false;
			}

			if (currArea == bossFight && onceBoss == false) // ******************************************************************************SPAWN BOSS HERE
			{
				// Enemy
				// WRITE THE FRAMESIZE HERE                 *X    *Y
				enemyList.push_back(new Boss(5, 1300, 161, 308, 266, 3, 0.7, 100, 0, 4, false));

				enemyList.push_back(new babyTomato("babyTomato", 3.0f, 500.0f, 200.0f, 60, 60, 1, 0.3, 10, 5, 1, false));

				enemySprites.push_back(&bossSprite);
				enemySprites.push_back(&enemy1_babyTomato);

				enemySprites[0]->load_sprite_image("assets/images/Tomato-Boss.png")
					.set_sprite_frame_size(44, 38, false)
					.set_scale(308, 266)
					.push_frame("idle", 0, 0)
					.push_frame("flinch", 46, 0) //*** **********************************************************SET FLINCH COORDINATES
					.set_center(0.5f, 0.0f)
					.set_position(enemyList[0]->getPositionX(), enemyList[0]->getPositionY())
					.set_animation("idle");

				enemySprites[1]->load_sprite_image("assets/images/Enemy_babyTomato/tomatoBaby.png")
					.set_sprite_frame_size(60, 60)
					.push_frame("idle", 0, 0)
					.push_frame("flinch", 0, 0)
					.push_frame("attack", 0, 0)
					.set_center(0.5f, 0.5f)
					.set_position(enemyList[1]->getPositionX(), enemyList[1]->getPositionY())
					.set_animation("idle");

				onceBoss = true;
			}
			if (onceBoss == true && enemyList.size() == 0)
			{
				mainCharacter.game = false;
				mainCharacter.win = true;
			}


			if (once_boss == false && currArea == bossFight) // Boss
			{
				for (int i = 0; i < musicVector.size() - 1; i++)
				{
					musicVector[i]->stop();
					musicVector[i]->setVolume(50);
				}
				bossMusic.setLoop(true);
				bossMusic.play();

				once_game = false;
				once_lair = false;
				once_boss = true;
				once_menu = false;
				once_pause = false;
				once_death = false;
				once_story = false;
			}

			// You can put movement code inside of this update function, it is called every frame
			Update();

			// Checks the Hunger
			mainCharacter.checkHunger();
			// Updates Stats
			Update_Stats();

			// Controller doesnt work
			mainCharacter.Update(player, earl, earlPause, earlDeath, theGame, enemyList, Magic_Attack);

			// deals mana damage
			//mainCharacter.setMana(mainCharacter.getMana() - 5);
			// deals damage
			//mainCharacter.setHealth(mainCharacter.getHealth() - 5);
		}
		else if (mainCharacter.menu == true)
		{

			if (once_menu == false)
			{
				for (int i = 0; i < musicVector.size() - 1; i++)
				{
					musicVector[i]->stop();
					musicVector[i]->setVolume(50);
				}
				mainMenuMusic.setLoop(true);
				mainMenuMusic.play();
				once_game = false;
				once_lair = false;
				once_boss = false;
				once_menu = true;
				once_pause = false;
				once_death = false;
				once_story = false;
			}

			mainCharacter.Update(player, earl, earlPause, earlDeath, theGame, enemyList, Magic_Attack);

		}
		else if (mainCharacter.pause == true)
		{

			if (once_pause == false)
			{
				// Reduces the volume by half
				for (int i = 0; i < musicVector.size(); i++)
				{
					musicVector[i]->setVolume(50);
				}

				once_game = false;
				once_lair = false;
				once_boss = false;
				once_menu = false;
				once_pause = true;
				once_death = false;
				once_story = false;
			}

			mainCharacter.Update(player, earl, earlPause, earlDeath, theGame, enemyList, Magic_Attack);

		}
		else if (mainCharacter.death == true)
		{
			if (once_death == false)
			{
				for (int i = 0; i < musicVector.size() - 1; i++)
				{
					musicVector[i]->stop();
					musicVector[i]->setVolume(100);
				}
				deathMusic.setLoop(true);
				deathMusic.play();
				once_game = false;
				once_lair = false;
				once_boss = false;
				once_menu = false;
				once_pause = false;
				once_death = true;
				once_story = false;
			}

			mainCharacter.Update(player, earl, earlPause, earlDeath, theGame, enemyList, Magic_Attack);

		}
		else if (mainCharacter.story == true)
		{
			if (once_story == false)
			{
				for (int i = 0; i < musicVector.size() - 1; i++)
				{
					musicVector[i]->stop();
					musicVector[i]->setVolume(50);
				}
				storyMusic.setLoop(true);
				storyMusic.play();
				once_game = false;
				once_lair = false;
				once_boss = false;
				once_menu = false;
				once_pause = false;
				once_death = false;
				once_story = true;
			}

			mainCharacter.Update(player, earl, earlPause, earlDeath, theGame, enemyList, Magic_Attack);

		}
		else if (mainCharacter.win == true)
		{
			for (int i = 0; i < musicVector.size() - 1; i++)
			{
				musicVector[i]->stop();
				musicVector[i]->setVolume(50);
			}

			mainCharacter.Update(player, earl, earlPause, earlDeath, theGame, enemyList, Magic_Attack);

		}

		// You can put sprite drawing code inside of this draw function
		DrawSprites();
		if (mainCharacter.game == true && transitioning == true && enemyList.size() == 0)
			processArrow();

	}



	// Enemey Vector Delete
	for (int i = enemyList.size() - 1; i >= 0; i--)
	{
		delete enemyList[i];
	}
	for (int i = projectileList.size() - 1; i >= 0; i--)
	{
		delete projectileList[i];
	}
}

// Back to front selection sort, to solve the depth issues with transparent sprites
// https://en.wikipedia.org/wiki/Selection_sort
void IterativeSelectionSort(std::vector<Sprite*>& a_sprites)
{
	for (unsigned int i = 0; i < a_sprites.size(); i++)
	{
		int minIndex = i;
		for (unsigned int j = i; j < a_sprites.size(); j++)
		{
			if (a_sprites[j]->get_depth() < a_sprites[minIndex]->get_depth())
			{
				minIndex = j;
			}
		}
		std::swap(a_sprites[minIndex], a_sprites[i]);
	}
}

float healthbarX = 0;
float healthbarY = 682;

float manabarX = 0;
float manabarY = 644;

float hungerbarX = -198;
float hungerbarY = 606;
int temp_hunger = 0;

void Update_Stats()
{

	// Updates health
	if (mainCharacter.getHealth() != mainCharacter.getMaxHealth())
	{
		health_bar.set_position(healthbarX - ((mainCharacter.getMaxHealth() - mainCharacter.getHealth()) * 2), healthbarY);
	}

	// Updates mana
	if (mainCharacter.getMana() != mainCharacter.getMaxMana())
	{
		mana_bar.set_position(manabarX - ((mainCharacter.getMaxMana() - mainCharacter.getMana()) * 2), manabarY);
	}

	// Updates hunger
	if (temp_hunger != mainCharacter.getHunger() && mainCharacter.Super_Hunger == false)
	{
		hunger_bar.set_position((hungerbarX + mainCharacter.getHunger() * 2), hungerbarY);
	}
	else
	{
		temp_hunger = mainCharacter.getHunger();
	}

	// Does the Super Hunger when the hunger bar reachs 100
	if (mainCharacter.Super_Hunger == true && mainCharacter.getHunger() != 0)
	{
		hunger_bar.set_position(0 - ((mainCharacter.getMaxHunger() - mainCharacter.getHunger()) * 2), hungerbarY);
		mainCharacter.setHunger(mainCharacter.getHunger() - 1);
		mainCharacter.lightDamage = 1 + 2;
		mainCharacter.mediumDamage = 2 + 2;
		mainCharacter.heavyDamage = 3 + 2;
		mainCharacter.magicDamage = 2 + 2;
	}
	else if (mainCharacter.Super_Hunger == true && mainCharacter.getHunger() >= 0)
	{
		mainCharacter.lightDamage = 1;
		mainCharacter.mediumDamage = 2;
		mainCharacter.heavyDamage = 3;
		mainCharacter.magicDamage = 2;
		mainCharacter.Super_Hunger = false;
	}
}

void processArrow()
{
	Shapes::set_color(1.0f, 0.0f, 0.0f);
	Shapes::draw_triangle(true, 1000, 710, 1000, 620, 1050, 665);
	Shapes::draw_rectangle(true, 900, 642.5f, 101, 45);
}

void processArea()
{
	static bool once = false;
	static bool onceWalls = false;
	static bool sausage = false;
	static bool barrier = false;
	static bool sausageWall = true;

	switch (currArea)
	{
	case area1:

		if (enemyList.size() == 0)
		{
			A1 = true;
			transitioning = true;

			if ((mainCharacter.getPositionX() + mainCharacter.getFrameSizeX() / 2) >= 1060 && once == false)
			{
				once = true;
				BS.set_frame(0);
				blackScreen = true;
				transitioning = false;
			}
		}

		if (blackScreen == true)
		{
			BSAnimation(BS);

			if (BS.get_current_frame() == 3)
			{
				float y = mainCharacter.getPositionY();
				background.load_sprite_image("assets/images/Game Maps/Background_1.png");
				mainCharacter.setPositionX(100);
				player.set_position(100, y);
			}

			if (BS.get_current_frame() == 5)
			{
				blackScreen = false;
				currArea = area2;
				once = false;
				transitioning = false;

			}
		}
		break;

	case area2:

		if (enemyList.size() == 0)
		{
			A2 = true;
			transitioning = true;
			if ((mainCharacter.getPositionX() + mainCharacter.getFrameSizeX() / 2) >= 1060 && once == false && A2 == true)
			{
				once = true;
				BS.set_frame(0);
				blackScreen = true;
			}
		}

		if (blackScreen == true)
		{
			BSAnimation(BS);

			if (BS.get_current_frame() == 3)
			{
				float y = mainCharacter.getPositionY();
				background.load_sprite_image("assets/images/Game Maps/Background_2.png");
				mainCharacter.setPositionX(100);
				player.set_position(100, y);
			}

			if (BS.get_current_frame() == 5)
			{
				blackScreen = false;
				currArea = area3;
				once = false;
				transitioning = false;


				if (!onceWalls)
				{
					walls.push_back(Wall(235, 475, 325, 329));
					walls.push_back(Wall(325, 329, 730, 329));
					walls.push_back(Wall(730, 329, 715, 464));
					walls.push_back(Wall(370, 209, 430, 000));
					walls.push_back(Wall(310, 209, 805, 209));
					walls.push_back(Wall(805, 209, 910, 000));
					walls.push_back(Wall(325, 329, 370, 209));
				}
			}
		}
		break;

	case area3:
		for (int i = 0; i < walls.size(); i++)
		{
			checkWallCollision(walls[i], mainCharacter);
		}

		if (enemyList[0]->getHealth() <= 0 && sausageWall == true)
		{
			sausageWall = false;
			walls.erase(walls.begin() + 6);
		}

		A3 = true;
		transitioning = true;
		if ((mainCharacter.getPositionX() + mainCharacter.getFrameSizeX() / 2) >= 1060 && once == false && A3 == true)
		{
			once = true;
			BS.set_frame(0);
			blackScreen = true;
		}

		if (blackScreen == true)
		{
			BSAnimation(BS);

			if (BS.get_current_frame() == 3)
			{
				float y = mainCharacter.getPositionY();
				background.load_sprite_image("assets/images/Game Maps/Background_3.png");
				mainCharacter.setPositionX(100);
				player.set_position(100, y);
			}

			if (BS.get_current_frame() == 5)
			{
				blackScreen = false;
				currArea = area4;
				once = false;
				transitioning = false;


				for (int j = walls.size() - 1; j >= 0; j--)
				{
					walls.erase(walls.begin() + j);
				}

				if (!onceWalls)
				{
					walls.push_back(Wall(340, 464, 400, 299));
					walls.push_back(Wall(400, 299, 715, 344));
					walls.push_back(Wall(655, 464, 715, 344));
					walls.push_back(Wall(475, 136, 790, 211));
					walls.push_back(Wall(475, 136, 430, 000));
					walls.push_back(Wall(790, 211, 880, 000));
					walls.push_back(Wall(400, 299, 475, 136));

				}
			}
		}
		break;

	case area4:

		for (int i = 0; i < walls.size(); i++)
		{
			checkWallCollision(walls[i], mainCharacter);
		}

		if (enemyList.size() == 0)
		{
			A4 = true;
			transitioning = true;
			if ((mainCharacter.getPositionX() + mainCharacter.getFrameSizeX() / 2) >= 1060 && once == false && A4 == true)
			{
				once = true;
				BS.set_frame(0);
				blackScreen = true;
			}
		}

		if (broken == true && barrier == false)
		{
			barrier = true;
			background.load_sprite_image("assets/images/Game Maps/Background_3_Barrier.png");
			walls.erase(walls.begin() + 6);
		}

		if (blackScreen == true)
		{
			BSAnimation(BS);

			if (BS.get_current_frame() == 3)
			{
				float y = mainCharacter.getPositionY();
				background.load_sprite_image("assets/images/Game Maps/Background_4.png");
				mainCharacter.setPositionX(100);
				player.set_position(100, y);
			}

			if (BS.get_current_frame() == 5)
			{
				blackScreen = false;
				currArea = area5;
				once = false;
				transitioning = false;


				for (int j = walls.size() - 1; j >= 0; j--)
				{
					walls.erase(walls.begin() + j);
				}

				walls.push_back(Wall(790, 464, 790, 404));
				walls.push_back(Wall(790, 404, 865, 314));
				walls.push_back(Wall(940, 057, 940, 001));
			}
		}
		break;

	case area5:

		for (int i = 0; i < walls.size(); i++)
		{
			checkWallCollision(walls[i], mainCharacter);
		}

		if (enemyList.size() == 0)
		{
			A5 = true;
			transitioning = true;
			if ((mainCharacter.getPositionX() + mainCharacter.getFrameSizeX() / 2) >= 1060 && once == false && A5 == true)
			{
				once = true;
				BS.set_frame(0);
				blackScreen = true;
			}
		}

		if (blackScreen == true)
		{
			BSAnimation(BS);

			if (BS.get_current_frame() == 3)
			{
				float y = mainCharacter.getPositionY();
				background.load_sprite_image("assets/images/Game Maps/Corridor_1.png");
				mainCharacter.setPositionX(100);
				player.set_position(100, y);
			}

			if (BS.get_current_frame() == 5)
			{
				blackScreen = false;
				currArea = area6;
				once = false;
				transitioning = false;


				for (int j = walls.size() - 1; j >= 0; j--)
				{
					walls.erase(walls.begin() + j);
				}

				walls.push_back(Wall(106, 299, 1080, 299));
			}
		}
		break;

	case area6:

		for (int i = 0; i < walls.size(); i++)
		{
			checkWallCollision(walls[i], mainCharacter);
		}

		if (enemyList.size() == 0)
		{
			H1 = true;
			transitioning = true;
			if ((mainCharacter.getPositionX() + mainCharacter.getFrameSizeX() / 2) >= 1060 && once == false && H1 == true)
			{
				once = true;
				BS.set_frame(0);
				blackScreen = true;
			}
		}

		if (blackScreen == true)
		{
			BSAnimation(BS);

			if (BS.get_current_frame() == 3)
			{
				float y = mainCharacter.getPositionY();
				background.load_sprite_image("assets/images/Game Maps/Corridor_2.png");
				mainCharacter.setPositionX(100);
				player.set_position(100, y);
			}

			if (BS.get_current_frame() == 5)
			{
				blackScreen = false;
				currArea = area7;
				once = false;
				transitioning = false;

			}
		}
		break;

	case area7:

		for (int i = 0; i < walls.size(); i++)
		{
			checkWallCollision(walls[i], mainCharacter);
		}

		if (enemyList.size() == 0)
		{
			H2 = true;
			transitioning = true;
			if ((mainCharacter.getPositionX() + mainCharacter.getFrameSizeX() / 2) >= 1060 && once == false && H2 == true)
			{
				once = true;
				BS.set_frame(0);
				blackScreen = true;
			}
		}

		if (blackScreen == true)
		{
			BSAnimation(BS);

			if (BS.get_current_frame() == 3)
			{
				float y = mainCharacter.getPositionY();
				background.load_sprite_image("assets/images/Game Maps/Corridor_3.png");
				mainCharacter.setPositionX(100);
				player.set_position(100, y);
			}

			if (BS.get_current_frame() == 5)
			{
				blackScreen = false;
				currArea = area8;
				once = false;
				transitioning = false;

			}
		}
		break;

	case area8:

		for (int i = 0; i < walls.size(); i++)
		{
			checkWallCollision(walls[i], mainCharacter);
		}

		if (enemyList.size() == 0)
		{
			H3 = true;
			transitioning = true;
			if ((mainCharacter.getPositionX() + mainCharacter.getFrameSizeX() / 2) >= 1060 && once == false && H3 == true)
			{
				once = true;
				BS.set_frame(0);
				blackScreen = true;
			}
		}

		if (blackScreen == true)
		{
			BSAnimation(BS);

			if (BS.get_current_frame() == 3)
			{
				float y = mainCharacter.getPositionY();
				background.load_sprite_image("assets/images/Game Maps/Lair_1.png");
				mainCharacter.setPositionX(100);
				player.set_position(100, y);
			}

			if (BS.get_current_frame() == 5)
			{
				blackScreen = false;
				currArea = area9;
				once = false;
				transitioning = false;


				for (int j = walls.size() - 1; j >= 0; j--)
				{
					walls.erase(walls.begin() + j);
				}

				walls.push_back(Wall(100, 419, 1080, 419));
			}
		}
		break;

	case area9:

		for (int i = 0; i < walls.size(); i++)
		{
			checkWallCollision(walls[i], mainCharacter);
		}


		if (enemyList.size() == 0)
		{
			if ((mainCharacter.getPositionX() + mainCharacter.getFrameSizeX() / 2) >= 1060 && once == false)
			{
				once = true;
				BS.set_frame(0);
				blackScreen = true;
			}
		}

		if (blackScreen == true)
		{
			BSAnimation(BS);

			if (BS.get_current_frame() == 3)
			{
				float y = mainCharacter.getPositionY();
				background.load_sprite_image("assets/images/Game Maps/Lair_2.png");
				mainCharacter.setPositionX(100);
				player.set_position(100, y);
			}

			if (BS.get_current_frame() == 5)
			{
				blackScreen = false;
				currArea = area10;
				once = false;
				transitioning = false;


				for (int j = walls.size() - 1; j >= 0; j--)
				{
					walls.erase(walls.begin() + j);
				}

				walls.push_back(Wall(100, 450, 1080, 450));

			}
		}
		break;

	case area10:

		for (int i = 0; i < walls.size(); i++)
		{
			checkWallCollision(walls[i], mainCharacter);
		}

		if (enemyList.size() == 0)
		{
			if ((mainCharacter.getPositionX() + mainCharacter.getFrameSizeX() / 2) >= 1060 && once == false)
			{
				once = true;
				BS.set_frame(0);
				blackScreen = true;
			}
		}

		if (blackScreen == true)
		{
			BSAnimation(BS);

			if (BS.get_current_frame() == 3)
			{
				float y = mainCharacter.getPositionY();
				background.load_sprite_image("assets/images/Game Maps/Lair_3.png");
				mainCharacter.setPositionX(100);
				player.set_position(100, y);
			}

			if (BS.get_current_frame() == 5)
			{
				blackScreen = false;
				currArea = bossFight;
				once = false;
				transitioning = false;

			}
		}
		break;

	case bossFight:

		for (int i = 0; i < walls.size(); i++)
		{
			checkWallCollision(walls[i], mainCharacter);
		}
		break;

	}
}

void BSAnimation(Sprite& a_sprite)
{
	static bool once = false;
	static steady_clock::time_point t1;
	steady_clock::time_point t2;
	duration<double> dt;

	if (once == false)
	{
		t1 = steady_clock::now();
		once = true;
	}

	t2 = steady_clock::now();
	dt = duration_cast<duration<double>>(t2 - t1);

	if (dt.count() > 0.1)
	{
		a_sprite.next_frame();
		once = false;
	}
}

void retry()
{
	once1 = false;
	once2 = false;
	once3 = false;
	once4 = false;
	once5 = false;
	once6 = false;
	once7 = false;
	once8 = false;
	once9 = false;
	once10 = false;
	onceBoss = false;
	player.set_position(150, 300);
	mainCharacter.setPositionX(150);
	mainCharacter.setPositionY(300);
	mainCharacter.setHealth(mainCharacter.getMaxHealth());
	mainCharacter.setMana(mainCharacter.getMaxMana());
	mainCharacter.setHunger(0);

	for (int i = enemyList.size() - 1; i >= 0; i--)
	{
		delete enemyList[i];
		enemyList.erase(enemyList.begin() + i);
		enemySprites.erase(enemySprites.begin() + i);
		continue;
	}
	for (int i = projectileList.size() - 1; i >= 0; i--)
	{
		delete projectileList[i];
		projectileList.erase(projectileList.begin() + i);
		projectileSprites.erase(projectileSprites.begin() + i);
		continue;

	}
}

#pragma region Math Function Definitions

Vector2 getProjection(Vector2 a, Vector2 b)
{
	float bottom = (a.dot(b)) / (b.magSq());
	return (b * bottom);
}

float getProjectionAmount(Vector2 a, Vector2 b)
{
	return (a.dot(b) / b.mag());
}

Vector2 get_normal(Vector2 p)
{
	return p * (1 / sqrt(p.x * p.x + p.y * p.y));
}

void checkWallCollision(Wall wall, Player& player)
{
	float footRadius = 15;

	//player position
	Vector2 pos;

	pos.x = player.getPositionX();
	pos.y = player.getPositionY() - player.getFrameSizeY() / 2;

	//vector from first wall coords to player
	Vector2 wall1_to_player;
	Vector2 wall1_to_wall2;
	Vector2 proj_1;


	wall1_to_player.x = pos.x - wall.getP1().x;
	wall1_to_player.y = pos.y - wall.getP1().y;
	wall1_to_wall2 = wall.getDirection(true);
	proj_1 = getProjection(wall1_to_player, wall1_to_wall2);


	//vector from second wall coords to player
	Vector2 wall2_to_player;
	Vector2 wall2_to_wall1;
	Vector2 proj_2;

	wall2_to_player.x = pos.x - wall.getP2().x;
	wall2_to_player.y = pos.y - wall.getP2().y;
	wall2_to_wall1 = wall.getDirection(false);
	proj_2 = getProjection(wall2_to_player, wall2_to_wall1);

	//projection position
	Vector2 proj_pos;
	proj_pos = (proj_1 + wall.getP1());

	//vector from projection to player
	Vector2 proj_to_player;
	proj_to_player.x = pos.x - proj_pos.x;
	proj_to_player.y = pos.y - proj_pos.y;

	//distance from projection to player
	float distance = Vector2(proj_pos.x - pos.x, proj_pos.y - pos.y).mag();

	//vector of line the size of ball radius 
	Vector2 wall1_to_wall2_radius_length;
	Vector2 wall2_to_wall1_radius_length;
	wall1_to_wall2_radius_length = get_normal(wall.getDirection(true)) * footRadius;
	wall2_to_wall1_radius_length = get_normal(wall.getDirection(false)) * footRadius;

	bool proj1_inside = ((proj_1 + wall1_to_wall2_radius_length).dot(wall.getDirection(true)) > 0) ? true : false;
	bool proj2_inside = ((proj_2 + wall2_to_wall1_radius_length).dot(wall.getDirection(false)) > 0) ? true : false;

	if (proj1_inside == true && proj2_inside == true && distance < footRadius)
	{
		if (player.getRight())
		{
			if (proj_to_player.x <= -2)
				player.setPositionX(player.getPositionX() - player.getMovementSpeed());
		}

		else if (player.getLeft())
		{
			if (proj_to_player.x >= 2)
				player.setPositionX(player.getPositionX() + player.getMovementSpeed());
		}

		if (player.getUp())
		{
			player.setPositionY(player.getPositionY() - player.getMovementSpeed());
		}

		else if (player.getDown())
		{
			player.setPositionY(player.getPositionY() - player.getMovementSpeed());
		}
	}
}

#pragma endregion 