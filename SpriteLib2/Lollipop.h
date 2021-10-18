#ifndef LOLLIPOP_H
#define LOLLIPOP_H

#include "Enemy.h"
#include "Projectile_E.h"

class Lollipop : public Enemy
{
public:
	Lollipop(string, float, float, float, int, int, float, float, int, int, int, bool);
	~Lollipop();
	void behave(Player &p1, vector<Enemy*> &enemies, vector<Sprite*>& enemySprite, vector<Projectile_E*> &pro, vector<Sprite*>& proSprite);
	bool One_Dimensional_Check(float x1, float x2, float x3, float x4);


private:
	bool flinch_once = false;
	bool attack_once = false;

	steady_clock::time_point t1;
	steady_clock::time_point t2;
};

#endif