#ifndef ENEMY_H
#define ENEMY_H
#include "mainCharacter.h"
#include <cmath>
#include <ctime>
#include <ratio>
#include <chrono>
#include <iostream>
#include <vector>
#include <string>


#include "Projectile_E.h"


using namespace spritelib;
using namespace std::chrono;
using namespace std;


class Player;
class Projectile;
class Projectile_E;


class Enemy
{
public:
	Enemy(string, float, float, float, int, int, float, float, int, int, int, bool);
	~Enemy();
	float getMovementSpeed() const;
	float getPositionX() const;
	float getPositionY() const;
	float getCooldown() const;
	int getHealth() const;
	int getRange() const;
	int getDamage() const;
	int getFrameSizeX() const;
	int getFrameSizeY() const;
	bool checkAttacking() const;
	bool checkRight() const;
	string getName() const;
	bool getAggro() const;
	int getMaxHealth() const;

	void setMovementSpeed(float);
	void setPositionX(float);
	void setPositionY(float);
	void setCooldown(float);
	void setHealth(int);
	void setRange(int);
	void setDamage(int);
	void makeDummy();
	void setRight(bool = true);
	void setKnockback(bool);
	void setName(string);
	void setAggro(bool);

	float dist2Player(Player &p1);
	float checkFriends(Enemy* enemies);
	float direction2PlayerX(Player &p1);
	float direction2PlayerY(Player &p1);
	void follow(Player p1, std::vector<Enemy*> enemies);
	void attack(Player &p1);
	void wander(Player p1, float, float);
	void wander(Player p1, int, int);
	void flinch();
	void knockedback(Player &p1, float pwr, steady_clock::time_point);

	virtual void behave(Player &p1, vector<Enemy*> &enemies, vector<Sprite*>& enemySprite, vector<Projectile_E*> &pro, vector<Sprite*>& proSprite) = 0;

	bool operator==(Enemy* other);

protected:
	string name;
	bool followed;
	bool wandering;
	bool attacking;
	bool aggro;
	bool facingRight;
	bool dummy;
	bool flinching;
	bool knockback;
	float movementSpeed;
	float positionX;
	float positionY;
	float cooldown;
	float flinchTime;
	int health;
	int maxHealth;
	int newHealth;
	int range;
	int damage;
	int frameSizeX;
	int frameSizeY;

	steady_clock::time_point knockbackT1;
	steady_clock::time_point knockbackT2;
	duration<double> knockbackDT;
	steady_clock::time_point knockbackTIME;
};

#endif