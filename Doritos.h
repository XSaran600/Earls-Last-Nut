#ifndef DORITOS_H
#define DORITOS_H

#include "Enemy.h"

class Doritos : public Enemy
{
public:
	Doritos(string, float, float, float, int, int, float, float, int, int, int, bool);
	~Doritos();
	void behave(Player &p1, vector<Enemy*> &enemies, vector<Sprite*>& enemySprite, vector<Projectile_E*> &pro, vector<Sprite*>& proSprite);

private:
	bool flinch_once = false;
	bool attack_once = false;
};

#endif