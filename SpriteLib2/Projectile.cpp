#include "Projectile.h"

Projectile::Projectile(float frameSizeX, float frameSizeY)
{
	frameSize.x = frameSizeX;
	frameSize.y = frameSizeY;
	vX = 0;
	vY = 0;
}

Projectile::~Projectile()
{

}

bool Projectile::One_Dimensional_Check(float x1, float x2, float x3, float x4)
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

bool Projectile::Collision_AABB(Enemy &other)
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

void Projectile::Update(Player &player, Sprite &a_sprite, vector<Enemy*>& enemies)
{
	position = a_sprite.get_position();
	position.x = player.getPositionX() - (frameSize.x / 2);
	position.y = player.getPositionY() - (frameSize.y / 2);

	if (isAttacking == true)
	{
		if (timer == false) // Starts the timer and sets the start positions
		{
			start.x = position.x;
			start.y = position.y;
			t1 = steady_clock::now();
			timer = true;
		}


		t2 = steady_clock::now(); // end time
		duration<double> dt = duration_cast<duration<double>> (t2 - t1) * 10; // Delta time

		if (player.getFacingLeft() == true) // If the projectile should go left or right
		{
			a_sprite.set_flipped(true);
			position.x = start.x - (vX * dt.count());
		}
		else
		{
			a_sprite.set_flipped(false);
			position.x = start.x + (vX * dt.count());

		}

		//position.y = start.y + (vY * dt.count()) + (0.5 * g * pow(dt.count(), 2)); // The effect of gravity

		for (int i = 0; i < enemies.size(); i++)
		{
			if (Collision_AABB(*enemies[i]) == true)
			{
				steady_clock::time_point tempTime = steady_clock::now();
				enemies[i]->flinch();
				//cout << "Projectile hits enemy." << endl;
				position.x = player.getPositionX() - (frameSize.x / 2);
				position.y = player.getPositionY() - (frameSize.y / 2);
				if (vX < 250)
				{
					damage = 1;
				}
				else
				{
					damage = 2;
				}
				enemies[i]->setHealth(enemies[i]->getHealth() - player.getMagicDamage() * damage);
				vX = 0;
				vY = 0;
				isAttacking = false;
			}
		}

		if (position.x <= (start.x - vX * 5) && player.getFacingLeft() == true)
		{
			position.x = player.getPositionX() - (frameSize.x / 2);
			position.y = player.getPositionY() - (frameSize.y / 2);
			vX = 0;
			vY = 0;
			isAttacking = false;
		}
		else if (position.x >= (start.x + vX * 5) && player.getFacingRight() == true)
		{
			position.x = player.getPositionX() - (frameSize.x / 2);
			position.y = player.getPositionY() - (frameSize.y / 2);
			vX = 0;
			vY = 0;
			isAttacking = false;
		}

		if ((position.x + frameSize.x) >= 1080) // Right Side
		{
			position.x = player.getPositionX() - (frameSize.x / 2);
			position.y = player.getPositionY() - (frameSize.y / 2);
			vX = 0;
			vY = 0;
			isAttacking = false;
		}
		if (position.x <= 0) // Left Side
		{
			position.x = player.getPositionX() - (frameSize.x / 2);
			position.y = player.getPositionY() - (frameSize.y / 2);
			vX = 0;
			vY = 0;
			isAttacking = false;
		}

		/*
		if (position.y <= (player.getPositionY() - (player.getFrameSizeY() / 2)))
		{
		position.x = player.getPositionX() - (frameSize.x / 2);
		position.y = player.getPositionY() - (frameSize.y / 2);
		vX = 0;
		vY = 0;
		isAttacking = false;
		}*/

	}
	else
	{
		position.x = player.getPositionX() - (frameSize.x / 2);
		position.y = player.getPositionY() - (frameSize.y / 2);
		timer = false;
	}


	a_sprite.set_position(position.x, position.y);
}

float Projectile::getPositionX() const
{
	return position.x;
}

void Projectile::setPositionX(float posX)
{
	position.x = posX;
}

float Projectile::getPositionY() const
{
	return position.y;
}

void Projectile::setPositionY(float posY)
{
	position.y = posY;
}

float Projectile::getVX() const
{
	return vX;
}

void Projectile::setVX(float posX)
{
	vX = posX;
}

float Projectile::getVY() const
{
	return vY;
}

void Projectile::setVY(float posX)
{
	vY = posX;
}

bool Projectile::getIsAttacking() const
{
	return isAttacking;
}

void Projectile::setIsAttacking(bool Att)
{
	isAttacking = Att;
}