#include "Boss.h"

Boss::Boss(float ms, float px, float py, int fsx, int fsy, float cd, float ft, int hp, int rng, int dmg, bool R)
	:Enemy("Tomato", ms, px, py, fsx, fsy, cd, ft, hp, rng, dmg, R)
{
	jumping = false;
	dashing = false;
	walking = false;
	rightSide = true;
	goingLeft = false;
	goingRight = false;
	pi = 3.151592654;
	// Roar
	if (!roarBuffer.loadFromFile("_Roar_test.wav"))
	{
		cout << "Can't load _Roar_test.wav" << endl;
	}
	roar.setBuffer(roarBuffer);
	roar.setVolume(100);
}

Boss::~Boss()
{
}

void Boss::jumpSmash(Player &player)
{
	float g = -9.81;
	static bool once = false;
	static steady_clock::time_point t1;
	steady_clock::time_point t2;
	duration<double> dt;
	static float startX;
	static float startY;
	static float targetX;
	static float targetY;
	static float theta = 75.0;
	static Vector2 velocity;
	static Vector2 position;

	if (!once)
	{
		once = true;
		jumping = true;
		t1 = steady_clock::now();
		startX = getPositionX();
		startY = getPositionY();
		targetX = player.getPositionX();
		targetY = player.getPositionY() - player.getFrameSizeY() / 2;
		float diffX = targetX - startX;
		float diffY = targetY - startY;

		float tempVel;
		float tempTop;
		float tempB1;
		float tempB2;
		float tempBT;

		tempTop = pow(diffX, 2) * g;
		tempB1 = pow(cos(theta * pi / 180), 2) * 4 * diffY;
		tempB2 = diffX * sin(theta * pi / 180) * cos(theta * pi / 180) * 2;
		tempBT = tempB1 + tempB2;
		tempVel = sqrt(abs(tempTop) / abs(tempBT));

		if (diffX < 0)
		{
			velocity.x = tempVel * cos(theta * pi / 180) * -1;
		}

		else velocity.x = tempVel * cos(theta * pi / 180);


		velocity.y = tempVel * sin(theta * pi / 180);
	}

	else if (once)
	{
		t2 = steady_clock::now();
		dt = duration_cast<duration<double>> (t2 - t1) * 7;

		position.x = startX + velocity.x * dt.count();
		position.y = startY + (velocity.y * dt.count()) + (0.5 * g * pow(dt.count(), 2));

		positionX = position.x;
		positionY = position.y;

		if ((positionY > targetY - 20 && positionY < targetY + 20) && (positionX > targetX - 70 && positionX < targetX + 70))
		{

			if ((player.getPositionY() - player.getFrameSizeY() / 2 > getPositionY() - 25) && (player.getPositionY() - player.getFrameSizeY() / 2 < getPositionX() + 50) && (player.getPositionX() < getPositionX() + 125) && (player.getPositionX() > getPositionX() - 125))
			{
				player.setHealth(player.getHealth() - 5);
			}

			jumping = false;
			once = false;
		}

		if (positionY <= 0)
		{

			if ((player.getPositionY() - player.getFrameSizeY() / 2 > getPositionY() - 25) && (player.getPositionY() - player.getFrameSizeY() / 2 < getPositionX() + 50) && (player.getPositionX() < getPositionX() + 125) && (player.getPositionX() > getPositionX() - 125))
			{
				player.setHealth(player.getHealth() - 5);
			}

			jumping = false;
			once = false;
			positionY = 10;
		}
	}
	else
		cout << "Something went terribly wrong..." << endl;

}

void Boss::goLeft(Player &player)
{
	float g = -9.81;
	static bool once = false;
	static steady_clock::time_point t1;
	steady_clock::time_point t2;
	duration<double> dt;
	static float startX;
	static float startY;
	static float targetX;
	static float targetY;
	static float theta = 75.0;
	static Vector2 velocity;
	static Vector2 position;

	if (!once)
	{
		once = true;
		goingLeft = true;
		t1 = steady_clock::now();
		startX = getPositionX();
		startY = getPositionY();
		targetX = 160;
		targetY = 161;
		float diffX = targetX - startX;
		float diffY = targetY - startY;

		float tempVel;
		float tempTop;
		float tempB1;
		float tempB2;
		float tempBT;

		tempTop = pow(diffX, 2) * g;
		tempB1 = pow(cos(theta * pi / 180), 2) * 4 * diffY;
		tempB2 = diffX * sin(theta * pi / 180) * cos(theta * pi / 180) * 2;
		tempBT = tempB1 + tempB2;
		tempVel = sqrt(abs(tempTop) / abs(tempBT));

		if (diffX < 0)
		{
			velocity.x = tempVel * cos(theta * pi / 180) * -1;
		}

		else velocity.x = tempVel * cos(theta * pi / 180);


		velocity.y = tempVel * sin(theta * pi / 180);
	}

	else if (once)
	{
		t2 = steady_clock::now();
		dt = duration_cast<duration<double>> (t2 - t1) * 7;

		position.x = startX + velocity.x * dt.count();
		position.y = startY + (velocity.y * dt.count()) + (0.5 * g * pow(dt.count(), 2));

		positionX = position.x;
		positionY = position.y;

		if ((positionY > targetY - 20 && positionY < targetY + 20) && (positionX > targetX - 70 && positionX < targetX + 70))
		{

			if ((player.getPositionY() - player.getFrameSizeY() / 2 > getPositionY() - 25) && (player.getPositionY() - player.getFrameSizeY() / 2 < getPositionX() + 50) && (player.getPositionX() < getPositionX() + 125) && (player.getPositionX() > getPositionX() - 125))
			{
				player.setHealth(player.getHealth() - 5);
			}

			goingLeft = false;
			once = false;
		}

		if (positionY <= 0)
		{

			if ((player.getPositionY() - player.getFrameSizeY() / 2 > getPositionY() - 25) && (player.getPositionY() - player.getFrameSizeY() / 2 < getPositionX() + 50) && (player.getPositionX() < getPositionX() + 125) && (player.getPositionX() > getPositionX() - 125))
			{
				player.setHealth(player.getHealth() - 5);
			}

			goingLeft = false;
			once = false;
			positionY = 10;
		}
	}
	else
		cout << "Something went terribly wrong..." << endl;

}

void Boss::goRight(Player &player)
{
	float g = -9.81;
	static bool once = false;
	static steady_clock::time_point t1;
	steady_clock::time_point t2;
	duration<double> dt;
	static float startX;
	static float startY;
	static float targetX;
	static float targetY;
	static float theta = 75.0;
	static Vector2 velocity;
	static Vector2 position;

	if (!once)
	{
		once = true;
		goingRight = true;
		t1 = steady_clock::now();
		startX = getPositionX();
		startY = getPositionY();
		targetX = 925;
		targetY = 161;
		float diffX = targetX - startX;
		float diffY = targetY - startY;

		float tempVel;
		float tempTop;
		float tempB1;
		float tempB2;
		float tempBT;

		tempTop = pow(diffX, 2) * g;
		tempB1 = pow(cos(theta * pi / 180), 2) * 4 * diffY;
		tempB2 = diffX * sin(theta * pi / 180) * cos(theta * pi / 180) * 2;
		tempBT = tempB1 + tempB2;
		tempVel = sqrt(abs(tempTop) / abs(tempBT));

		if (diffX < 0)
		{
			velocity.x = tempVel * cos(theta * pi / 180) * -1;
		}

		else velocity.x = tempVel * cos(theta * pi / 180);


		velocity.y = tempVel * sin(theta * pi / 180);
	}

	else if (once)
	{
		t2 = steady_clock::now();
		dt = duration_cast<duration<double>> (t2 - t1) * 7;

		position.x = startX + velocity.x * dt.count();
		position.y = startY + (velocity.y * dt.count()) + (0.5 * g * pow(dt.count(), 2));

		positionX = position.x;
		positionY = position.y;

		if ((positionY > targetY - 20 && positionY < targetY + 20) && (positionX > targetX - 70 && positionX < targetX + 70))
		{

			if ((player.getPositionY() - player.getFrameSizeY() / 2 > getPositionY() - 25) && (player.getPositionY() - player.getFrameSizeY() / 2 < getPositionX() + 50) && (player.getPositionX() < getPositionX() + 125) && (player.getPositionX() > getPositionX() - 125))
			{
				player.setHealth(player.getHealth() - 5);
			}

			goingRight = false;
			once = false;
		}

		if (positionY <= 0)
		{

			if ((player.getPositionY() - player.getFrameSizeY() / 2 > getPositionY() - 25) && (player.getPositionY() - player.getFrameSizeY() / 2 < getPositionX() + 50) && (player.getPositionX() < getPositionX() + 125) && (player.getPositionX() > getPositionX() - 125))
			{
				player.setHealth(player.getHealth() - 5);
			}

			goingRight = false;
			once = false;
			positionY = 10;
		}
	}
	else
		cout << "Something went terribly wrong..." << endl;

}

void Boss::dashAttack(Player &player)
{
	static bool once = false;
	static bool right = false;
	static bool waiting = false;
	static bool waitOnce = false;
	static bool hit = false;

	static steady_clock::time_point t1;
	steady_clock::time_point t2;
	static steady_clock::time_point wait1;
	duration<double> dt;
	Vector2 velocity(1000, 0);
	Vector2 position(getPositionX(), getPositionY());

	float dashSpeed = 10.0f;

	if (!once)
	{
		t1 = steady_clock::now();
		once = true;
		dashing = true;
		right = ((positionX - player.getPositionX()) >= 0) ? false : true;

	}

	switch (right)
	{
	case true:
		if (dashes == 0 && waiting == false)
		{
			if (getPositionX() > 1230)
			{
				hit = false;
				waiting = true;
			}

			else
			{
				t2 = steady_clock::now();
				dt = duration_cast<duration<double>>(t2 - t1);
				position.x = position.x + (velocity.x * dt.count());
				setPositionX(position.x);

				if ((player.getPositionY() - player.getFrameSizeY() / 2 > getPositionY() - 25) && (player.getPositionY() - player.getFrameSizeY() / 2 < getPositionX() + 50) && (player.getPositionX() < getPositionX() + 125) && (player.getPositionX() > getPositionX() - 125) && hit == false)
				{
					hit = true;
					player.setHealth(player.getHealth() - 4);
				}

				t1 = t2;
			}
		}

		else if (dashes == 0 && waiting == true)
		{
			if (!waitOnce)
			{
				waitOnce = true;
				wait1 = steady_clock::now();
			}

			t2 = steady_clock::now();
			dt = duration_cast<duration<double>>(t2 - wait1);

			if (dt.count() > 2)
			{
				dashes = 1;
				waiting = false;
				waitOnce = false;

				positionY = player.getPositionY() - player.getFrameSizeY() / 2;

				t1 = t2;
			}

		}

		if (dashes == 1 && waiting == false)
		{
			if (getPositionX() < -150)
			{
				hit = false;
				waiting = true;
			}

			else
			{
				t2 = steady_clock::now();
				dt = duration_cast<duration<double>>(t2 - t1);
				position.x = position.x - (velocity.x * dt.count());
				setPositionX(position.x);

				if ((player.getPositionY() - player.getFrameSizeY() / 2 > getPositionY() - 25) && (player.getPositionY() - player.getFrameSizeY() / 2 < getPositionX() + 50) && (player.getPositionX() < getPositionX() + 125) && (player.getPositionX() > getPositionX() - 125) && hit == false)
				{
					hit = true;
					player.setHealth(player.getHealth() - 4);
				}

				t1 = t2;
			}
		}

		else if (dashes == 1 && waiting == true)
		{
			if (!waitOnce)
			{
				waitOnce = true;
				wait1 = steady_clock::now();
			}

			t2 = steady_clock::now();
			dt = duration_cast<duration<double>>(t2 - wait1);

			if (dt.count() > 2)
			{
				dashes = 2;
				waiting = false;
				waitOnce = false;

				t1 = steady_clock::now();
			}

		}

		if (dashes == 2)
		{
			waiting = false;
			waitOnce = false;
			once = false;
			right = false;
			dashing = false;
			dashes = 0;

			walk(151, 161);
		}

		break;

	case false:
		if (dashes == 0 && waiting == false)
		{
			if (getPositionX() < -150)
			{
				hit = false;
				waiting = true;
			}

			else
			{
				t2 = steady_clock::now();
				dt = duration_cast<duration<double>>(t2 - t1);
				position.x = position.x - (velocity.x * dt.count());
				setPositionX(position.x);

				if ((player.getPositionY() - player.getFrameSizeY() / 2 > getPositionY() - 25) && (player.getPositionY() - player.getFrameSizeY() / 2 < getPositionX() + 50) && (player.getPositionX() < getPositionX() + 125) && (player.getPositionX() > getPositionX() - 125) && hit == false)
				{
					hit = true;
					player.setHealth(player.getHealth() - 4);
				}

				t1 = t2;
			}
		}

		else if (dashes == 0 && waiting == true)
		{
			if (!waitOnce)
			{
				waitOnce = true;
				wait1 = steady_clock::now();
			}

			t2 = steady_clock::now();
			dt = duration_cast<duration<double>>(t2 - wait1);

			if (dt.count() > 2)
			{
				dashes = 1;
				waiting = false;
				waitOnce = false;

				positionY = player.getPositionY() - player.getFrameSizeY() / 2;

				t1 = steady_clock::now();
			}

		}

		if (dashes == 1 && waiting == false)
		{
			if (getPositionX() > 1230)
			{
				hit = false;
				waiting = true;
			}

			else
			{
				t2 = steady_clock::now();
				dt = duration_cast<duration<double>>(t2 - t1);
				position.x = position.x + (velocity.x * dt.count());
				setPositionX(position.x);

				if ((player.getPositionY() - player.getFrameSizeY() / 2 > getPositionY() - 25) && (player.getPositionY() - player.getFrameSizeY() / 2 < getPositionX() + 50) && (player.getPositionX() < getPositionX() + 125) && (player.getPositionX() > getPositionX() - 125) && hit == false)
				{
					hit = true;
					player.setHealth(player.getHealth() - 4);
				}

				t1 = t2;
			}
		}

		else if (dashes == 1 && waiting == true)
		{
			if (!waitOnce)
			{
				waitOnce = true;
				wait1 = steady_clock::now();
			}

			t2 = steady_clock::now();
			dt = duration_cast<duration<double>>(t2 - wait1);

			if (dt.count() > 2)
			{
				dashes = 2;
				waiting = false;
				waitOnce = false;

				t1 = steady_clock::now();
			}

		}

		if (dashes == 2)
		{
			waiting = false;
			waitOnce = false;
			once = false;
			right = false;
			dashing = false;
			dashes = 0;

			walk(951, 161);
		}
		break;
	}
}

void Boss::walk(float x, float y)
{
	walking = true;
	Vector2 position(getPositionX(), getPositionY());
	Vector2 velocity;
	Vector2 copy;
	Vector2 direction;

	static steady_clock::time_point t1;
	steady_clock::time_point t2;
	duration<double> dt;
	static bool once = false;
	static float targetX;
	static float targetY;
	movementSpeed = 200;

	if (!once)
	{
		once = true;
		t1 = steady_clock::now();

		if (x != 0 && y != 0)
		{
			targetX = x;
			targetY = y;
		}
	}

	else
	{
		copy.x = (targetX - position.x);
		copy.y = (targetY - position.y);
		direction.x = copy.x / copy.mag();
		direction.y = copy.y / copy.mag();
		velocity = direction * movementSpeed;
		t2 = steady_clock::now();
		dt = duration_cast<duration<double>>(t2 - t1);

		position = position + (velocity * dt.count());

		positionX = position.x;
		positionY = position.y;

		if (velocity.x < 0 && positionX < targetX)
		{
			positionX = targetX;
			positionY = targetY;
			walking = false;
			once = false;
		}

		else if (velocity.x > 0 && positionX > targetX)
		{
			positionX = targetX;
			positionY = targetY;
			walking = false;
			once = false;
		}
		t1 = t2;
	}
}

bool Boss::checkJump() const
{
	return jumping;
}

bool Boss::checkDashing() const
{
	return dashing;
}

bool Boss::checkWalking() const
{
	return walking;
}

int Boss::getDashes() const
{
	return dashes;
}

bool Boss::checkGoingLeft() const
{
	return goingLeft;
}

bool Boss::checkGoingRight() const
{
	return goingRight;
}

bool Boss::checkSide() const
{
	return rightSide;
}

//virtual void behave(Player &p1, std::vector<Enemy*>& enemies, Projectile_E &pro, std::vector<Sprite*>& enemySprite) = 0;

void Boss::behave(Player &p1, vector<Enemy*> &enemies, vector<Sprite*>& enemySprite, vector<Projectile_E*> &pro, vector<Sprite*>& proSprite)
{
	static bool animation = false;
	static bool once = false;
	static int decision;
	static steady_clock::time_point t1;
	steady_clock::time_point t2;
	duration<double> dt;

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

	if (!animation)
	{
		goRight(p1);
		animation = true;
		srand(time(NULL));
	}

	if (checkJump())
	{
		jumpSmash(p1);
	}

	else if (checkDashing())
	{
		dashAttack(p1);
	}

	else if (checkWalking())
	{
		walk();
	}

	else if (checkGoingLeft())
	{
		goLeft(p1);
	}

	else if (checkGoingRight())
	{
		goRight(p1);
	}

	else
	{
		if (!once)
		{
			once = true;
			t1 = steady_clock::now();
			decision = (rand() % 3) + 1;
		}

		else
		{
			switch (decision)
			{
			case 1:
				t2 = steady_clock::now();
				dt = duration_cast<duration<double>>(t2 - t1);

				if (dt.count() > 5)
				{
					roar.play();

					if (dt.count() > 7)
					{
						once = false;
						dashAttack(p1);
					}
				}

				break;

			case 2:
				t2 = steady_clock::now();
				dt = duration_cast<duration<double>>(t2 - t1);

				if (dt.count() > 5)
				{
					if (positionX >= 540)
					{
						if (161 - positionY <= 10)
						{
							goLeft(p1);
							once = false;
						}

						else walk(925, 161);
					}

					else
					{
						if (161 - positionY <= 10)
						{
							goRight(p1);
							once = false;
						}

						else walk(160, 161);
					}
				}
				break;

			case 3:
				t2 = steady_clock::now();
				dt = duration_cast<duration<double>>(t2 - t1);

				if (dt.count() > 5)
				{
					if (dt.count() < 7.5)
					{
						if (abs(p1.getPositionX() - positionX) > 75)
						{
							if ((p1.getPositionY() - p1.getFrameSizeY() / 2) - positionY <= 10)
							{
								cout << "Going to player" << endl;
								jumpSmash(p1);
								once = false;
							}
						}
					}

					else
					{
						cout << "Player not in range" << endl;
						decision = 2;
					}
				}

				break;

			default:
				once = false;
			}
		}
	}
	
	health = newHealth;
}