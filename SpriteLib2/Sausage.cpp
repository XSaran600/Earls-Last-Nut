#include "Sausage.h"

Sausage::Sausage(string n, float ms, float pX, float pY, int fSX, int fSY, float cd, float ft, int hp, int rng, int dmg, bool R)
	:Enemy::Enemy(n, ms, pX, pY, fSX, fSY, cd, ft, hp, rng, dmg, R)
{
	dead = false;
}

Sausage::~Sausage()
{
}

void Sausage::behave(Player &p1, vector<Enemy*> &enemies, vector<Sprite*>& enemySprite, vector<Projectile_E*> &pro, vector<Sprite*>& proSprite)
{

	if (health <= 0 && angle < 90)
	{

		for (int i = 0; i < enemies.size(); i++)
		{
			if (*enemies[i] == &(*this))
			{
				enemySprite[i]->set_rotation(angle);
				enemySprite[i]->set_flipped(true);
				enemySprite[i]->set_animation("dead");
			}
		}
		angle = angle + 1;

	}
	else if (health > 0)
	{
		if (newHealth != health) // Flinch Check
		{
			flinch();
			for (int i = 0; i < enemies.size(); i++)
			{
				if (*enemies[i] == &(*this))
				{
					enemySprite[i]->set_animation("flinch");
					ft1 = steady_clock::now();
				}
			}
			flinch_once = true;
		}
		ft2 = steady_clock::now();
		fdt = duration_cast<duration<double>> (ft2 - ft1);

		if (flinch_once = true && fdt.count() > flinchTime) // End Flinch
		{
			for (int i = 0; i < enemies.size(); i++)
			{
				if (*enemies[i] == &(*this))
				{
					enemySprite[i]->set_animation("idle");
				}
			}
			flinch_once = false;
			ft1 = ft2;
		}

		if (dummy == false && flinching == false && knockback == false)
		{
			if (aggro == true)
			{
				if (attacking == false)
				{
					for (int i = 0; i < enemies.size(); i++)
					{
						if (*enemies[i] == &(*this))
						{
							enemySprite[i]->set_animation("idle");
						}
					}
				}
				
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

		else if (flinching == false && knockback == false)
		{

			if (aggro == false && getHealth() != 10)
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
	health = newHealth;

}

bool Sausage::checkDead() const
{
	return dead;
}

void Sausage::kill()
{
	dead = true;
}