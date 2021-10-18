#include "Doritos.h"

Doritos::Doritos(string n, float ms, float pX, float pY, int fSX, int fSY, float cd, float ft, int hp, int rng, int dmg, bool R)
	:Enemy::Enemy(n, ms, pX, pY, fSX, fSY, cd, ft, hp, rng, dmg, R)
{

}

Doritos::~Doritos()
{

}


void Doritos::behave(Player &p1, vector<Enemy*> &enemies, vector<Sprite*>& enemySprite, vector<Projectile_E*> &pro, vector<Sprite*>& proSprite)
{
	if (newHealth != health) // Flinch Check
	{
		flinch();
		for (int i = 0; i < enemies.size(); i++)
		{
			if (*enemies[i] == &(*this))
			{
				enemySprite[i]->set_animation("flinch");
			}
		}
		flinch_once = true;
	}

	if (flinching == false && flinch_once == true) // End Flinch
	{
		for (int i = 0; i < enemies.size(); i++)
		{
			if (*enemies[i] == &(*this))
			{
				enemySprite[i]->set_animation("idle");
			}
		}
		flinch_once = false;
	}

	if (dummy == false && flinching == false && knockback == false)
	{
		if (aggro == true)
		{
			if (attacking == false)
			{
				follow(p1, enemies);
				for (int i = 0; i < enemies.size(); i++)
				{
					if (*enemies[i] == &(*this))
					{
						enemySprite[i]->set_animation("idle");
					}
				}
			}
			if ((p1.getPositionX() - getPositionX() < 75 && p1.getPositionX() - getPositionX() > -75 && p1.getPositionY() - getPositionY() < 50 && p1.getPositionY() - getPositionY() > -50) || attacking == true)
			{
				attack(p1);
				attack_once = true;
				for (int i = 0; i < enemies.size(); i++)
				{
					if (*enemies[i] == &(*this))
					{
						enemySprite[i]->set_animation("attack");
					}
				}
			}

			if (p1.getPositionX() > getPositionX())
				setRight(true);
			else setRight(false);
		}

		else if (aggro == false && getHealth() != 10)
		{
			aggro = true;
		}

		if (facingRight == true && p1.getPositionX() > getPositionX())
		{
			aggro = true;
		}

		else if (facingRight == false && p1.getPositionX() < getPositionX())
		{
			aggro = true;
		}

		if (attacking == false && attack_once == true) // End Attack
		{
			for (int i = 0; i < enemies.size(); i++)
			{
				if (*enemies[i] == &(*this))
				{
					enemySprite[i]->set_animation("idle");
				}
			}
			attack_once = false;
		}
	}

	else if (flinching == false && knockback == false)
	{
		if (aggro == true)
		{
			if (p1.getPositionX() > getPositionX())
				setRight(true);
			else setRight(false);
		}

		else if (aggro == false && getHealth() != 10)
		{
			aggro = true;
		}

		if (facingRight == true && p1.getPositionX() > getPositionX())
		{
			aggro = true;
		}

		else if (facingRight == false && p1.getPositionX() < getPositionX())
		{
			aggro = true;
		}
	}

	else if (flinching == true && knockback == false)
	{
		flinch();
	}

	else if (knockback == true)
	{
		if (p1.getLightAttack() == true)
		{
			knockedback(p1, p1.getPowerLight(), knockbackTIME);
		}
		else if (p1.getMediumAttack() == true)
		{
			knockedback(p1, p1.getPowerMedium(), knockbackTIME);
		}
		else if (p1.getHeavyAttack() == true)
		{
			knockedback(p1, p1.getPowerHeavy(), knockbackTIME);
		}
	}

	health = newHealth;
}