#ifndef KISS_H
#define KISS_H
#include "Enemy.h"

class Kiss : public Enemy
{
public:
	Kiss(string, float, float, float, int, int, float, float, int, int, int, bool);
	~Kiss();

	void behave(Player &p1, vector<Enemy*> &enemies, vector<Sprite*>& enemySprite, vector<Projectile_E*> &pro, vector<Sprite*>& proSprite);
private:
	bool flinch_once = false;
	bool attack_once = false;
};

#endif

