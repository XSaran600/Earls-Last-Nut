#include "Enemy.h"


Enemy::Enemy(string n, float ms, float pX, float pY, int fSX, int fSY, float cd, float ft, int hp, int rng, int dmg, bool R)
{
	name = n;
	movementSpeed = ms;
	positionX = pX;
	positionY = pY;
	cooldown = cd;
	flinchTime = ft;
	maxHealth = hp;
	health = hp;
	newHealth = health;
	range = rng;
	damage = dmg;
	frameSizeX = fSX;
	frameSizeY = fSY;
	wandering = false;
	attacking = false;
	followed = false;
	aggro = false;
	facingRight = R;
	dummy = false;
	flinching = false;
	knockback = false;

}

Enemy::~Enemy()
{
}

float Enemy::getMovementSpeed() const
{
	return movementSpeed;
}

float Enemy::getPositionX() const
{
	return positionX;
}

float Enemy::getPositionY() const
{
	return positionY;
}

float Enemy::getCooldown() const
{
	return cooldown;
}

int Enemy::getHealth() const
{
	return health;
}

int Enemy::getRange() const
{
	return range;
}

int Enemy::getDamage() const
{
	return damage;
}

int Enemy::getFrameSizeX() const
{
	return frameSizeX;
}

int Enemy::getFrameSizeY() const
{
	return frameSizeY;
}

bool Enemy::checkAttacking() const
{
	return attacking;
}

void Enemy::setMovementSpeed(float ms)
{
	movementSpeed = ms;
}

void Enemy::setPositionX(float pX)
{
	positionX = pX;
}

void Enemy::setPositionY(float pY)
{
	positionY = pY;
}

void Enemy::setCooldown(float cd)
{
	cooldown = cd;
}

void Enemy::setHealth(int hp)
{
	newHealth = hp;
}

void Enemy::setRange(int rng)
{
	range = rng;
}

void Enemy::setDamage(int dmg)
{
	damage = dmg;
}

void Enemy::setKnockback(bool kb)
{
	knockback = kb;
}

void Enemy::makeDummy()
{
	dummy = true;
}

void Enemy::follow(Player p1, vector<Enemy*> enemies)
{
	if (aggro == true)
	{
		float X = 0;
		float Y = 0;
		float length = 0;

		X = p1.getPositionX() - getPositionX();
		Y = p1.getPositionY() - getPositionY();
		length = sqrt(X * X + Y * Y);

		if (length >= 75)
		{
			float directionX = X / length;
			float directionY = Y / length;

			if (enemies.size() >= 2)
			{
				X = getPositionX() + ((directionX * getMovementSpeed()));
				Y = getPositionY() + ((directionY * getMovementSpeed()));
			}

			else
			{
				X = getPositionX() + ((directionX * getMovementSpeed()));
				Y = getPositionY() + ((directionY * getMovementSpeed()));
			}

			setPositionX(X);
			setPositionY(Y);

		}
	}
}

void Enemy::attack(Player &p1)
{
	if (aggro == true)
	{
		static steady_clock::time_point t1;
		steady_clock::time_point t2;
		duration<double> dt;

		if (attacking == false)
		{
			t1 = steady_clock::now();
			attacking = true;
		}

		t2 = steady_clock::now();
		dt = duration_cast<duration<double>> (t2 - t1);

		if (attacking == true && dt.count() > getCooldown())
		{
			if (p1.getPositionX() - getPositionX() < 75 && p1.getPositionX() - getPositionX() > -75 && p1.getPositionY() - getPositionY() < 50 && p1.getPositionY() - getPositionY() > -50)
			{
				int current = p1.getHealth();
				int dmg = getDamage();

				int HP = current - dmg;
				p1.setHealth(HP);

				std::cout << p1.getHealth() << ", ";

				attacking = false;
				return;
			}

			else attacking = false;

		}
	}
}

void Enemy::wander(Player p1, float dirX, float dirY)
{
	float startX = getPositionX();
	float startY = getPositionY();
	float targetX = startX + 30;
	float targetY = startY + 30;

	/*float diffX = p1.getPositionX() - getPositionX();

	if (diffX > 0)
	right = true;*/

	float tempDir = direction2PlayerX(p1);
}

void Enemy::wander(Player p1, int X, int Y)
{

}

void Enemy::flinch()
{
	aggro = true;
	static steady_clock::time_point t1;
	steady_clock::time_point t2;
	duration<double> dt;

	if (flinching == false)
	{
		t1 = steady_clock::now();
		flinching = true;
	}

	t2 = steady_clock::now();
	dt = duration_cast<duration<double>> (t2 - t1);

	if (dt.count() > flinchTime)
	{
		cout << "Done flinching" << endl;
		flinching = false;
	}
}

void Enemy::knockedback(Player  &p1, float pwr, steady_clock::time_point start)
{
	aggro = true;
	if (!knockback)
	{
		knockback = true;
		knockbackT1 = steady_clock::now();
		knockbackTIME = start;
	}

	knockbackT2 = steady_clock::now();

	knockbackDT = duration_cast<duration<double>> (knockbackT2 - knockbackTIME);
	duration<double> tempDT = duration_cast<duration<double>> (knockbackT2 - knockbackT1) * 5;


	if (knockbackDT.count() >= 0.25)
	{
		knockback = false;
	}

	else
	{
		float X = getPositionX() - direction2PlayerX(p1) * pwr * tempDT.count();
		float Y = getPositionY() - direction2PlayerY(p1) * pwr * tempDT.count();

		//cout << X << "\t" << Y << endl;

		setPositionX(X);
		setPositionY(Y);
	}

	knockbackT1 = steady_clock::now();
}

float Enemy::direction2PlayerX(Player &p1)
{
	float X = 0;
	float Y = 0;
	float length = 0;

	X = p1.getPositionX() - getPositionX();
	Y = p1.getPositionY() - getPositionY();
	length = sqrt(X * X + Y * Y);

	return X / length;
}

float Enemy::direction2PlayerY(Player &p1)
{
	float X = 0;
	float Y = 0;
	float length = 0;

	X = p1.getPositionX() - getPositionX();
	Y = p1.getPositionY() - getPositionY();
	length = sqrt(X * X + Y * Y);

	return Y / length;
}

float Enemy::checkFriends(Enemy* enemies)
{
	float X = 0;
	float Y = 0;
	float length = 0;

	X = enemies->getPositionX() - getPositionX();
	Y = enemies->getPositionY() - getPositionY();
	length = sqrt(X * X + Y * Y);

	return length;
}

float Enemy::dist2Player(Player &p1)
{
	float X = 0;
	float Y = 0;
	float length = 0;

	X = p1.getPositionX() - getPositionX();
	Y = p1.getPositionY() - getPositionY();
	length = sqrt(X * X + Y * Y);

	return length;
}

bool Enemy::operator==(Enemy* other)
{
	if (positionX == other->positionX && positionY == other->positionY)
		return true;

	else return false;
}

bool Enemy::checkRight() const
{
	if (facingRight == true)
		return true;
	else return false;
}

void Enemy::setRight(bool R)
{
	facingRight = R;
}

void Enemy::setAggro(bool A)
{
	aggro = A;
}

bool Enemy::getAggro() const
{
	return aggro;
}
int Enemy::getMaxHealth() const
{
	return maxHealth;
}



/*
void Enemy::behave(Player &p1, vector<Enemy*>& enemies)
{
/*for (unsigned int i = 0; i < enemies.size(); i++)
{
if ((*this) == enemies[i])
continue;

if (checkFriends(enemies[i]) > 20)
{
follow(p1, enemies);
}

else if (checkFriends(enemies[i]) <= 20 || wandering == true)
{
wandering = true;
float copyMS = enemies[i]->getMovementSpeed();
float tempMS = enemies[i]->getMovementSpeed() / 3;

float direction = direction2Player(p1);

setMovementSpeed(tempMS);
wander(p1, direction);
}
}

if (newHealth != health)
{
flinch();
}

if (dummy == false && flinching == false && knockback == false)
{
if (aggro == true)
{
if (attacking == false)
follow(p1, enemies);
if ((p1.getPositionX() - getPositionX() < 75 && p1.getPositionX() - getPositionX() > -75 && p1.getPositionY() - getPositionY() < 50 && p1.getPositionY() - getPositionY() > -50) || attacking == true)
attack(p1);

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
}*/

string Enemy::getName() const
{
	return name;
}

void Enemy::setName(string n)
{
	name = n;
}