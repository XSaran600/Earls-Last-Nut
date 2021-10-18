#include "Lollipop.h"

Lollipop::Lollipop(string n, float ms, float pX, float pY, int fSX, int fSY, float cd, float ft, int hp, int rng, int dmg, bool R)
	:Enemy::Enemy(n, ms, pX, pY, fSX, fSY, cd, ft, hp, rng, dmg, R)
{

}

Lollipop::~Lollipop()
{
}

bool Lollipop::One_Dimensional_Check(float x1, float x2, float x3, float x4)
{
	//cout << x1 << ", " << x2 << ", " << x3 << ", " << x4 << endl;
	if (x1 >= x3 && x1 <= x4)
	{
		//cout << "check 1" << endl;
		return true;
	}
	else if (x2 >= x3 && x2 <= x4)
	{
		//cout << "check 2" << endl;
		return true;
	}
	else if (x3 >= x1 && x3 <= x2)
	{
		//cout << "check 3" << endl;
		return true;
	}
	else if (x4 >= x1 && x4 <= x2)
	{
		//cout << "check 4" << endl;
		return true;
	}
	else
	{
		//cout << "check false" << endl;
		return false;
	}
}

void Lollipop::behave(Player &p1, vector<Enemy*> &enemies, vector<Sprite*>& enemySprite, vector<Projectile_E*> &pro, vector<Sprite*>& proSprite)
{
	float otherDown = (p1.getPositionY() - p1.getFrameSizeY() / 2);
	float otherUp = (p1.getPositionY() + p1.getFrameSizeY() / 2);
	float Down = (getPositionY() + 35);
	float Up = (getPositionY() + getFrameSizeY() / 2 - 13);
	bool check_y = One_Dimensional_Check(Down, Up, otherDown, otherUp);



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
			for (int i = 0; i < enemies.size(); i++)
			{
				if (*enemies[i] == &(*this))
				{
					if (check_y == true && attacking == false)
					{
						t1 = steady_clock::now();
						pro[i]->setIsAttacking(true);
						enemySprite[i]->set_animation("attack");
						attack_once = true;
						attacking = true;
					}
					else if (pro[i]->getIsAttacking() == false && check_y == false && attacking == false)
					{
						pro[i]->setIsAttacking(false);
						enemySprite[i]->set_animation("idle");

						if (getPositionY() < p1.getPositionY())
						{
							setPositionY(getPositionY() + getMovementSpeed());
						}
						else if (getPositionY() > p1.getPositionY())
						{
							setPositionY(getPositionY() - getMovementSpeed());
						}
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

		if (attacking == true && attack_once == true) // End Attack
		{
			for (int i = 0; i < enemies.size(); i++)
			{
				if (*enemies[i] == &(*this))
				{
					t2 = steady_clock::now();
					duration<double> dt = duration_cast<duration<double>> (t2 - t1);

					if (dt.count() > getCooldown())
					{
						enemySprite[i]->set_animation("idle");
						attack_once = false;
						attacking = false;
						t1 = t2;
					}
				}
			}
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