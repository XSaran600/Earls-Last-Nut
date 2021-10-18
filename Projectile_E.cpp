#include "Projectile_E.h"

Projectile_E::Projectile_E(float frameSizeX, float frameSizeY)
{
	frameSize.x = frameSizeX;
	frameSize.y = frameSizeY;
	vX = 100;
	vY = 0;
}

Projectile_E::~Projectile_E()
{

}

bool Projectile_E::One_Dimensional_Check(float x1, float x2, float x3, float x4)
{
	if (x1 >= x3 && x1 <= x4)
	{
		return true;
	}
	else if (x2 >= x3 && x2 <= x4)
	{
		return true;
	}
	else if (x3 >= x1 && x3 <= x2)
	{
		return true;
	}
	else if (x4 >= x1 && x4 <= x2)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Projectile_E::Collision_AABB(Player &other)
{
	float otherLeft = (other.getPositionX() - (other.getFrameSizeX() / 2));
	float otherRight = (other.getPositionX() + (other.getFrameSizeX() / 2));
	float otherDown = (other.getPositionY() - (other.getFrameSizeY() / 2));
	float otherUp = (other.getPositionY() + (other.getFrameSizeY() / 2));

	float left = position.x;
	float right = (position.x + frameSize.x);
	float down = position.y;
	float up = (position.y + frameSize.y);

	bool check_x = One_Dimensional_Check(left, right, otherLeft, otherRight);
	bool check_y = One_Dimensional_Check(down, up, otherDown, otherUp);


	if (check_x == true && check_y == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Projectile_E::Update(vector<Enemy*> &enemies, vector<Projectile_E*> &pro, vector<Sprite*>& proSprite, Player &p1) // NEED TO CHANGE THE PLAYER TO ENEMY
{
	for (int i = 0; i < pro.size(); i++)
	{
		if (*pro[i] == &(*this))
		{
			position = proSprite[i]->get_position();
			position.x = enemies[i]->getPositionX() - (frameSize.x / 2);
			position.y = enemies[i]->getPositionY() - (frameSize.y / 2) + 40;

			if (isAttacking == true)
			{
				if (timer == false) // Starts the timer and sets the start positions
				{
					vX = 100;
					start.x = position.x;
					start.y = position.y;
					t1 = steady_clock::now();
					timer = true;
				}


				t2 = steady_clock::now(); // end time
				duration<double> dt = duration_cast<duration<double>> (t2 - t1) * 10; // Delta time

				if (enemies[i]->checkRight() == false) // If the projectile should go left or right
				{
					proSprite[i]->set_flipped(true);
					position.x = start.x - (vX * dt.count());
				}
				else
				{
					proSprite[i]->set_flipped(false);
					position.x = start.x + (vX * dt.count());

				}

				//position.y = start.y + (vY * dt.count()) + (0.5 * g * pow(dt.count(), 2)); // The effect of gravity

				if (Collision_AABB(p1) == true)
				{
					steady_clock::time_point tempTime = steady_clock::now();
					//cout << "Projectile hits enemy." << endl;
					position.x = enemies[i]->getPositionX() - (frameSize.x / 2);
					position.y = enemies[i]->getPositionY() - (frameSize.y / 2) + 40;

					p1.setHealth(p1.getHealth() - enemies[i]->getDamage());
					vX = 0;
					vY = 0;
					isAttacking = false;
					timer = false;

				}

				if (position.x <= (start.x - vX * 5) && enemies[i]->checkRight() == false)
				{
					position.x = enemies[i]->getPositionX() - (frameSize.x / 2);
					position.y = enemies[i]->getPositionY() - (frameSize.y / 2) + 40;
					vX = 0;
					vY = 0;
					isAttacking = false;
					timer = false;

				}
				else if (position.x >= (start.x + vX * 5) && enemies[i]->checkRight() == true)
				{
					position.x = enemies[i]->getPositionX() - (frameSize.x / 2);
					position.y = enemies[i]->getPositionY() - (frameSize.y / 2) + 40;
					vX = 0;
					vY = 0;
					isAttacking = false;
					timer = false;

				}

				if ((position.x + frameSize.x) >= 1080) // Right Side
				{
					position.x = enemies[i]->getPositionX() - (frameSize.x / 2);
					position.y = enemies[i]->getPositionY() - (frameSize.y / 2) + 40;
					vX = 0;
					vY = 0;
					isAttacking = false;
					timer = false;

				}
				if (position.x <= 0) // Left Side
				{
					position.x = enemies[i]->getPositionX() - (frameSize.x / 2);
					position.y = enemies[i]->getPositionY() - (frameSize.y / 2) + 40;
					vX = 0;
					vY = 0;
					isAttacking = false;
					timer = false;

				}

				/*
				if (position.y <= (enemies[i]->getPositionY() - (enemies[i]->getFrameSizeY() / 2)))
				{
				position.x = enemies[i]->getPositionX() - (frameSize.x / 2);
				position.y = enemies[i]->getPositionY() - (frameSize.y / 2);
				vX = 0;
				vY = 0;
				isAttacking = false;
				}*/

			}
			else
			{
				position.x = enemies[i]->getPositionX() - (frameSize.x / 2);
				position.y = enemies[i]->getPositionY() - (frameSize.y / 2) + 40;
				isAttacking = false;
				timer = false;
			}

			proSprite[i]->set_position(position.x, position.y);

		}
	}

}

float Projectile_E::getPositionX() const
{
	return position.x;
}

void Projectile_E::setPositionX(float posX)
{
	position.x = posX;
}

float Projectile_E::getPositionY() const
{
	return position.y;
}

void Projectile_E::setPositionY(float posY)
{
	position.y = posY;
}

float Projectile_E::getVX() const
{
	return vX;
}

void Projectile_E::setVX(float posX)
{
	vX = posX;
}

float Projectile_E::getVY() const
{
	return vY;
}

void Projectile_E::setVY(float posX)
{
	vY = posX;
}

bool Projectile_E::getIsAttacking() const
{
	return isAttacking;
}

void Projectile_E::setIsAttacking(bool Att)
{
	isAttacking = Att;
}

bool Projectile_E::operator==(Projectile_E* other)
{
	if (getPositionX() == other->getPositionX() && getPositionY() == other->getPositionY())
		return true;

	else return false;
}