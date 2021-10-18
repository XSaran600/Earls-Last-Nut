#ifndef SAUSAGE_H
#define SAUSAGE_H

#include "Enemy.h"

class Sausage : public Enemy
{
public:
	Sausage(string, float, float, float, int, int, float, float, int, int, int, bool);
	~Sausage();
	void behave(Player &p1, vector<Enemy*> &enemies, vector<Sprite*>& enemySprite, vector<Projectile_E*> &pro, vector<Sprite*>& proSprite);

	bool checkDead() const;
	void kill();

private:
	bool flinch_once = false;
	bool dead;
	float angle = 0;

	steady_clock::time_point ft1;
	steady_clock::time_point ft2;
	duration<double> fdt;
};

#endif