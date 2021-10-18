#ifndef BABYTOMATO_H
#define BABYTOMATO_H

#include "Enemy.h"

class babyTomato : public Enemy
{
public:
	babyTomato(string, float, float, float, int, int, float, float, int, int, int, bool);
	~babyTomato();
	void behave(Player &p1, vector<Enemy*> &enemies, vector<Sprite*>& enemySprite, vector<Projectile_E*> &pro, vector<Sprite*>& proSprite);

private:
	bool flinch_once = false;
	bool attack_once = false;
};

#endif