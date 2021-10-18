#ifndef MAIN_CHARACTER_H
#define MAIN_CHARACTER_H

#include "spritelib/spritelib.h"
#include "controller.h"
#include "Enemy.h"
#include "Projectile.h"
#include <SFML\Audio.hpp>



using namespace spritelib;
using namespace std;
using namespace std::chrono;


class Enemy;
class Projectile;

class Player
{
public:
	Player(int x, int y, int lA, int hA);
	~Player();

	void Update(Sprite &a_sprite, Sprite &earl, Sprite &earlPause, Sprite &earlDeath, Window &theGame, vector<Enemy*>&, Projectile &Magic_Attack);

	void Move(Sprite &a_sprite, Sprite &earl, Sprite &earlPause, Sprite &earlDeath, Window &theGame);

	bool One_Dimensional_Check(float x1, float x2, float x3, float x4);

	bool Collision_AABB(Enemy &other, bool checkDirection);

	void Attack(vector<Enemy*>&);

	void Process(Sprite &a_sprite, vector<Enemy*>&, Projectile &Magic_Attack);

	void checkHunger();

	float getMovementSpeed() const;
	void setMovementSpeed(float movSpd);

	float getPositionX() const;
	void setPositionX(float posX);

	float getPositionY() const;
	void setPositionY(float posY);

	float getFrameSizeX() const;
	void setFrameSizeX(float posX);

	float getFrameSizeY() const;
	void setFrameSizeY(float posY);

	int getHealth() const;
	void setHealth(int hp);

	int getMaxHealth() const;
	void setMaxHealth(int Mhp);

	double getMana() const;
	void setMana(double mp);

	int getMaxMana() const;
	void setMaxMana(int Mhp);

	int getHunger() const;
	void setHunger(int hg);

	int getMaxHunger() const;
	void setMaxHunger(int Mhg);

	int getLightDamage() const;
	void setLightDamage(int lD);

	int getHeavyDamage() const;
	void setHeavyDamage(int hD);

	int getMagicDamage() const;
	void setMagicDamage(int mD);

	bool getFacingLeft() const;
	void setFacingLeft(bool left);

	bool getFacingRight() const;
	void setFacingRight(bool right);

	bool getLightAttack() const;

	bool getMediumAttack() const;

	bool getHeavyAttack() const;

	bool getPowerLight() const;

	bool getPowerMedium() const;

	bool getPowerHeavy() const;

	bool getSuperHunger() const;


	friend void KeyboardFunc(Window::Key a_key, Window::EventType a_eventType);
	friend void Update_Stats();
	friend void DrawSprites();
	friend int main();
	friend void Update();
	friend void processArea();

	bool getRight() const;
	bool getLeft() const;
	bool getUp() const;
	bool getDown() const;


protected:
	math::Vector3 position;

	int power_light = 50;
	int power_medium = 75;
	int power_heavy = 100;

	bool Super_Hunger = false;

	float rotation;

	float movementSpeed = 20.0;

	bool facingLeft = false;
	bool facingRight = true;

	float spriteX;
	float spriteY;

	int lightAttackFrames;
	int heavyAttackFrames;

	// Attack bools
	bool lightAttack = false;
	bool mediumAttack = false;
	bool heavyAttack = false;
	bool magicAttack = false;

	// Stats
	int maxHealth = 100;
	int health = maxHealth;
	double maxMana = 100;
	double mana = maxMana;
	int maxHunger = 100;
	int hunger = 0;

	// Attack Damage
	int lightDamage = 1;
	int mediumDamage = 2;
	int heavyDamage = 3;
	int magicDamage = 2;


	enum states
	{
		Run, Idle, LeftI, RightI, LightA, MediumA, HeavyA, Magic_Charge, Magic
	};

	states currentstate = Idle;

	// Running speed
	steady_clock::time_point t1;
	steady_clock::time_point t2;

	// Jumping speed
	steady_clock::time_point Jt1;
	steady_clock::time_point Jt2;

	bool isRunning = false;
	bool done = false;
	bool attacked = false;
	bool isJumping = false;


	bool left_run = false;
	bool right_run = false;
	bool up_run = false;
	bool down_run = false;
	bool leftI_run = false;
	bool rightI_run = false;

	float startX = 0;
	float startY = 0;

	bool up = true;
	bool down = false;

	float g;
	float vX;
	float vY;


	// The different menus
	bool menu = true;
	bool story = false;
	bool game = false;
	bool pause = false;
	bool death = false;
	bool win = false;

	// checks if the controls should be displayed
	bool controlsMenu = false;

	// Main menu cursor coordinates
	int playX = 400;
	int playY = 154;
	int optionX = 350;
	int optionY = 100;
	int exitX = 400;
	int exitY = 40;

	// Pause menu cursor coordinates
	int continueX = 275;
	int continueY = 312;
	int controlsX = 535;
	int controlsY = 312;
	int quitX = 460;
	int quitY = 250;

	// Death menu cursor coordinates
	int retryX = 229;
	int retryY = 207;
	int deathExitX = 270;
	int deathExitY = 50;

	// Story
	int story_slide = 0;
	int story_slide_done = 7;

	bool controller = false;
	Input2::XBoxInput XBoxController;


	// All Sounds
	// Beep
	sf::SoundBuffer beepBuffer;
	sf::Sound beep;

	// Slash
	sf::SoundBuffer slashBuffer;
	sf::Sound slash;
	

	// Magic
	sf::SoundBuffer magicBuffer;
	sf::Sound magic;
	
	float tempMana = 0;
	bool once_Magic = false;

	bool controller_reset = false;

};

#endif