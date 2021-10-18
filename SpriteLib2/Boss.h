#ifndef BOSS_H
#define BOSS_H
#include "Enemy.h"
#include <math.h>
#include <stdio.h>
#include "Vector2.h"

class Boss : public Enemy
{
public:

	Boss(float, float, float, int, int, float, float, int, int, int, bool);
	~Boss();

	void behave(Player &p1, vector<Enemy*> &enemies, vector<Sprite*>& enemySprite, vector<Projectile_E*> &pro, vector<Sprite*>& proSprite);
	void dashAttack(Player&);
	void jumpSmash(Player&);
	void goLeft(Player&);
	void goRight(Player&);
	void walk(float = 0, float = 0);
	bool checkJump() const;
	bool checkDashing() const;
	bool checkWalking() const;
	bool checkGoingLeft() const;
	bool checkGoingRight() const;
	bool checkSide() const;

	int getDashes() const;
	friend int main();

private:
	bool jumping;
	bool dashing;
	bool walking;
	bool rightSide;
	bool goingLeft;
	bool goingRight;
	int dashes;
	float pi;

	// Roar
	sf::SoundBuffer roarBuffer;
	sf::Sound roar;

	bool flinch_once = false;

	steady_clock::time_point ft1;
	steady_clock::time_point ft2;
	duration<double> fdt;


};

#endif
