#include "mainCharacter.h"

using namespace std;
using namespace spritelib;
using namespace Input2;

//Sprite player;

Player::Player(int x, int y, int lA, int hA)
{
	spriteX = x;
	spriteY = y;
	lightAttackFrames = lA;
	heavyAttackFrames = hA;
	movementSpeed = 15;

	vX = 0;
	vY = 50;
	g = -9.8;

}

Player::~Player()
{

}

void Player::Update(Sprite &a_sprite, Sprite &earl, Sprite &earlPause, Sprite &earlDeath, Window &theGame, vector<Enemy*>& enemies, Projectile &Magic_Attack)
{
	position = a_sprite.get_position();
	rotation = a_sprite.get_rotataion();

	// ********************************************************************************************************* IT ALWAYS DETECTS A CONTROLLER NEED TO FIX
	/* ***************************************************REMOVE THE COMMENTS TO MAKE THE CONTROLLER WORK!!!!!!!
	if (XBoxController.GetConnected(0) == true)
	{
		cout << "Controller Connected!" << endl;
		controller = true;
		Move(a_sprite, earl, earlPause, earlDeath, theGame);

	}*/

	Process(a_sprite, enemies, Magic_Attack);

	a_sprite.set_position(position.x, position.y);
	a_sprite.set_rotation(rotation);
}

void Player::Move(Sprite &a_sprite, Sprite &earl, Sprite &earlPause, Sprite &earlDeath, Window &theGame)
{

	XBoxController.DownloadPackets(1);

	Input2::Stick lStick, rStick;
	XBoxController.GetSticks(0, lStick, rStick);

	float lTrig, rTrig;
	XBoxController.GetTriggers(0, lTrig, rTrig);


	// Key Pressed
	if (game == true)
	{
		if (XBoxController.GetButton(0, Input2::Button::Start)) // Pause button
		{
			beep.play();
			game = false;
			pause = true;
		}

		if (lStick.xAxis > 0.3 && lStick.xAxis <= 1 && (currentstate == Run || currentstate == Idle)) // Right
		{
			right_run = true;
			isRunning = true;
			currentstate = Run;
		}
		else if (lStick.xAxis < -0.3 && lStick.yAxis >= -1 && (currentstate == Run || currentstate == Idle)) // Left
		{
			left_run = true;
			isRunning = true;
			currentstate = Run;
		}
		else if (currentstate == Run && right_run == true) // Stick Released
		{
			right_run = false;
			isRunning = false;
			done = false;
			currentstate = Idle;
			vX = 0;
		}
		else if (currentstate == Run && left_run == true) // Stick Released
		{
			left_run = false;
			isRunning = false;
			done = false;
			currentstate = Idle;
			vX = 0;
		}

		if (lStick.yAxis > 0.3 && lStick.yAxis <= 1 && (currentstate == Run || currentstate == Idle)) // Up
		{
			up_run = true;
			isRunning = true;
			currentstate = Run;
		}
		else if (lStick.yAxis >= -1 && lStick.yAxis < -0.3 && (currentstate == Run || currentstate == Idle)) // Down
		{
			down_run = true;
			isRunning = true;
			currentstate = Run;
		}
		else if (currentstate == Run && up_run == true)
		{
			up_run = false;
			isRunning = false;
			done = false;
			currentstate = Idle;
		}
		else if (currentstate == Run && down_run == true)
		{
			down_run = false;
			isRunning = false;
			done = false;
			currentstate = Idle;
		}

		if (XBoxController.GetButton(0, Input2::Button::X) && currentstate == Idle) // Light Attack
		{
			currentstate = LightA;
		}
		if (XBoxController.GetButton(0, Input2::Button::B) && currentstate == Idle) // Medium Attack
		{
			currentstate = MediumA;
		}
		if (XBoxController.GetButton(0, Input2::Button::Y) && currentstate == Idle) // Heavy Attack
		{
			currentstate = HeavyA;
		}
		if (rTrig > 0 && currentstate == Idle) // Magic
		{
			currentstate = Magic_Charge;
		}
		else if (rTrig <= 0 && currentstate == Magic_Charge) // Button Released
		{
			currentstate = Magic;
		}

	}
	// Main Menu
	else if (menu == true)
	{

		math::Vector3 earlPosition = earl.get_position();

		if (XBoxController.GetButton(0, Input2::Button::DPadUp) && controlsMenu == false) // Up on dpad
		{
			if (earlPosition.y == optionY)
			{
				earlPosition.y = playY;
				earlPosition.x = playX;
				Sleep(100);
			}
			else if (earlPosition.y == exitY)
			{
				earlPosition.y = optionY;
				earlPosition.x = optionX;
				Sleep(100);
			}
		}
		if (XBoxController.GetButton(0, Input2::Button::DPadDown) && controlsMenu == false) // Down on dpad
		{
			if (earlPosition.y == playY)
			{
				earlPosition.y = optionY;
				earlPosition.x = optionX;
				Sleep(100);
			}
			else if (earlPosition.y == optionY)
			{
				earlPosition.y = exitY;
				earlPosition.x = exitX;
				Sleep(100);
			}
		}
		if (XBoxController.GetButton(0, Input2::Button::A) && controlsMenu == false) // Selects X button on ps4 controller
		{
			if (earlPosition.y == optionY)
			{
				beep.play();
				controlsMenu = true;
				Sleep(100);
			}
			if (earlPosition.y == playY)
			{
				beep.play();
				menu = false;
				game = true;
				Sleep(100);
			}
			if (earlPosition.y == exitY)
			{
				beep.play();
				exit(0);
				Sleep(100);
			}
		}
		if (XBoxController.GetButton(0, Input2::Button::B) && controlsMenu == true) // Returns circle on ps4 controller
		{
			beep.play();
			controlsMenu = false;
			Sleep(100);

		}

		earl.set_position(earlPosition.x, earlPosition.y);
	}
	// Pause Menu
	else if (pause == true)
	{
		math::Vector3 earlPausePosition = earlPause.get_position();

		if (XBoxController.GetButton(0, Input2::Button::B) && controlsMenu == true) // Returns
		{
			beep.play();
			controlsMenu = false;
			Sleep(100);

		}
		if (XBoxController.GetButton(0, Input2::Button::B) && controlsMenu == false) // Resumes
		{
			beep.play();
			pause = false;
			game = true;
			Sleep(100);
		}
		if (XBoxController.GetButton(0, Input2::Button::DPadRight))
		{
			earlPausePosition.x = controlsX;
			earlPausePosition.y = controlsY;
			Sleep(100);
		}
		if (XBoxController.GetButton(0, Input2::Button::DPadLeft))
		{
			earlPausePosition.x = continueX;
			earlPausePosition.y = continueY;
			Sleep(100);
		}
		if (XBoxController.GetButton(0, Input2::Button::DPadDown))
		{
			earlPausePosition.x = quitX;
			earlPausePosition.y = quitY;
			Sleep(100);
		}
		if (XBoxController.GetButton(0, Input2::Button::DPadUp) && earlPausePosition.y == quitY)
		{
			earlPausePosition.x = continueX;
			earlPausePosition.y = continueY;
			Sleep(100);
		}
		if (XBoxController.GetButton(0, Input2::Button::A) && controlsMenu == false) // Selects
		{
			if (earlPausePosition.x == controlsX)
			{
				beep.play();
				controlsMenu = true;
				Sleep(100);
			}
			if (earlPausePosition.x == continueX)
			{
				beep.play();
				pause = false;
				game = true;
				Sleep(100);
			}
			if (earlPausePosition.y == quitY)
			{
				beep.play();
				exit(0);
				Sleep(100);
			}
		}
		earlPause.set_position(earlPausePosition.x, earlPausePosition.y);
	}
	else if (death == true)
	{
		math::Vector3 earlDeathPosition = earlDeath.get_position();

		if (XBoxController.GetButton(0, Input2::Button::A))
		{
			if (earlDeathPosition.y == retryY)
			{
				controller_reset = true;
				beep.play();
				death = false;
				game = true;
			}

			if (earlDeathPosition.y == deathExitY)
			{
				beep.play();
				exit(0);
			}
		}
		if (XBoxController.GetButton(0, Input2::Button::DPadDown))
		{
			//earlDeathPosition.x = mainCharacter.deathExitX;
			//earlDeathPosition.y = mainCharacter.deathExitY;
			earlDeathPosition.x = 270;
			earlDeathPosition.y = 50;
		}
		if (XBoxController.GetButton(0, Input2::Button::DPadUp))
		{
			earlDeathPosition.x = retryX;
			earlDeathPosition.y = retryY;
		}

		earlDeath.set_position(earlDeathPosition.x, earlDeathPosition.y);

	}
	else if (story == true)
	{
		if (story_slide >= story_slide_done)
		{
			story = false;
			game = true;
		}
		if (XBoxController.GetButton(0, Input2::Button::A))
		{
			story_slide = story_slide + 1;
		}

		if (XBoxController.GetButton(0, Input2::Button::Start))
		{
			story = false;
			game = true;
		}
	}
	else if (win == true)
	{
		if (XBoxController.GetButton(0, Input2::Button::A))
		{
			beep.play();
			exit(0);
		}
	}



	//Sleep(100);

}

bool Player::One_Dimensional_Check(float x1, float x2, float x3, float x4)
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

bool Player::Collision_AABB(Enemy &other, bool checkDirection)
{
	float otherLeft = (other.getPositionX() - (other.getFrameSizeX() / 2));
	float otherRight = (other.getPositionX() + (other.getFrameSizeX() / 2));
	float otherDown = (other.getPositionY() - (other.getFrameSizeY() / 2));
	float otherUp = (other.getPositionY() + (other.getFrameSizeY() / 2));


	if (checkDirection == true) // Right
	{
		//cout << "Left side collision check" << endl;
		float left = position.x;
		float right = (position.x + (spriteX / 2));
		float down = (position.y - (spriteY / 2));
		float up = (position.y + (spriteY / 2));

		//cout << "Player X: " << left << ", " << right << endl;
		//cout << "Player Y: " << down << ", " << up << endl;
		//cout << "Enemy X: " << otherLeft << ", " << otherRight << endl;
		//cout << "Enemy Y: " << otherDown << ", " << otherUp << endl;

		bool check_x = One_Dimensional_Check(left, right, otherLeft, otherRight);
		bool check_y = One_Dimensional_Check(down, up, otherDown, otherUp);

		//cout << check_x << ", " << check_y << endl;

		if (check_x == true && check_y == true)
		{
			//cout << "Collision is true" << endl;
			return true;
		}
		else
		{
			//cout << "Collision is false" << endl;
			return false;
		}
	}
	else // Left
	{
		//cout << "Right side collision check" << endl;
		float left = (position.x - (spriteX / 2));
		float right = position.x;
		float down = (position.y - (spriteY / 2));
		float up = (position.y + (spriteY / 2));

		//cout << "Player X: " << left << ", " << right << endl;
		//cout << "Player Y: " << down << ", " << up << endl;
		//cout << "Enemy X: " << otherLeft << ", " << otherRight << endl;
		//cout << "Enemy Y: " << otherDown << ", " << otherUp << endl;

		bool check_x = One_Dimensional_Check(left, right, otherLeft, otherRight);
		bool check_y = One_Dimensional_Check(down, up, otherDown, otherUp);

		//cout << check_x << ", " << check_y << endl;

		if (check_x == true && check_y == true)
		{
			//cout << "Collision is true" << endl;
			return true;
		}
		else
		{
			//cout << "Collision is false" << endl;
			return false;
		}
	}
}

void Player::Attack(vector<Enemy*>& enemies)
{
	for (int i = 0; i < enemies.size(); i++)
	{
		if (facingLeft == true)
		{
			if (Collision_AABB(*enemies[i], facingRight) == true)
			{
				setHunger(getHunger() + 2);
				slash.play();
				if (lightAttack == true)
				{
					steady_clock::time_point tempTime = steady_clock::now();
					enemies[i]->setHealth(enemies[i]->getHealth() - lightDamage);
				}
				else if (mediumAttack == true)
				{
					steady_clock::time_point tempTime = steady_clock::now();
					enemies[i]->setHealth(enemies[i]->getHealth() - mediumDamage);
				}
				else if (heavyAttack == true)
				{
					steady_clock::time_point tempTime = steady_clock::now();
					enemies[i]->setHealth(enemies[i]->getHealth() - heavyDamage);
				}
			}

		}
		else if (facingRight == true)
		{
			if (Collision_AABB(*enemies[i], facingRight) == true)
			{
				setHunger(getHunger() + 2);
				slash.play();
				if (lightAttack == true)
				{
					steady_clock::time_point tempTime = steady_clock::now();
					enemies[i]->setHealth(enemies[i]->getHealth() - lightDamage);
				}
				else if (mediumAttack == true)
				{
					steady_clock::time_point tempTime = steady_clock::now();
					enemies[i]->setHealth(enemies[i]->getHealth() - mediumDamage);
				}
				else if (heavyAttack == true)
				{
					steady_clock::time_point tempTime = steady_clock::now();
					enemies[i]->setHealth(enemies[i]->getHealth() - heavyDamage);
				}
			}

		}
	}
}

float Player::getMovementSpeed() const
{
	return movementSpeed;
}

void Player::setMovementSpeed(float movSpd)
{
	movementSpeed = movSpd;
}

float Player::getPositionX() const
{
	return position.x;
}

void Player::setPositionX(float posX)
{
	position.x = posX;
}

float Player::getPositionY() const
{
	return position.y;
}

void Player::setPositionY(float posY)
{
	position.y = posY;
}

float Player::getFrameSizeX() const
{
	return spriteX;
}

void Player::setFrameSizeX(float posX)
{
	spriteX = posX;
}

float Player::getFrameSizeY() const
{
	return spriteY;
}

void Player::setFrameSizeY(float posY)
{
	spriteY = posY;
}

int Player::getHealth() const
{
	return health;
}

void Player::setHealth(int hp)
{
	health = hp;
	if (health > maxHealth)
	{
		health = maxHealth;
	}
	if (health < 0)
	{
		health = 0;
	}
}

int Player::getMaxHealth() const
{
	return maxHealth;
}

void Player::setMaxHealth(int Mhp)
{
	maxHealth = Mhp;
}

double Player::getMana() const
{
	return mana;
}

void Player::setMana(double mp)
{
	mana = mp;
	if (mana > maxMana)
	{
		mana = maxMana;
	}
	if (mana < 0)
	{
		mana = 0;
	}
}

int Player::getMaxMana() const
{
	return maxMana;
}

void Player::setMaxMana(int Mhp)
{
	maxMana = Mhp;
}

int Player::getHunger() const
{
	return hunger;
}

void Player::setHunger(int hg)
{
	hunger = hg;
	if (hunger > maxHunger)
	{
		hunger = maxHunger;
	}
	if (hunger < 0)
	{
		hunger = 0;
	}
}

int Player::getMaxHunger() const
{
	return maxHunger;
}
void Player::setMaxHunger(int Mhg)
{
	maxHunger = Mhg;
}

int Player::getLightDamage() const
{
	return lightDamage;
}

void Player::setLightDamage(int lD)
{
	lightDamage = lD;
}

int Player::getHeavyDamage() const
{
	return heavyDamage;
}

void Player::setHeavyDamage(int hD)
{
	heavyDamage = hD;
}

int Player::getMagicDamage() const
{
	return magicDamage;
}

void Player::setMagicDamage(int mD)
{
	magicDamage = mD;
}

bool Player::getFacingLeft() const
{
	return facingLeft;
}

void Player::setFacingLeft(bool left)
{
	facingLeft = left;
}

bool Player::getFacingRight() const
{
	return facingRight;
}

void Player::setFacingRight(bool right)
{
	facingRight = right;
}

void Player::Process(Sprite &player, vector<Enemy*>& enemyList, Projectile &Magic_Attack)
{
	position = player.get_position();

	switch (currentstate)
	{
	case Run:
		if (right_run == true)
		{
			if (isRunning == true && done == false)
			{
				t1 = steady_clock::now();
				done = true;
			}
			position.x += getMovementSpeed();
			facingLeft = false;
			facingRight = true;
			player.set_flipped();
			player.set_animation("run");
			vX = getMovementSpeed();
		}

		if (left_run == true)
		{
			if (isRunning == true && done == false)
			{
				t1 = steady_clock::now();
				done = true;
			}
			position.x -= getMovementSpeed();
			facingLeft = true;
			facingRight = false;
			player.set_flipped(true);
			player.set_animation("run");
			vX = getMovementSpeed();

		}

		if (up_run == true)
		{
			if (isRunning == true && done == false)
			{
				t1 = steady_clock::now();
				done = true;
			}
			position.y += getMovementSpeed();
			if (facingRight)
			{
				facingRight = true;
				facingLeft = false;
				player.set_flipped();
				player.set_animation("run");
			}
			else
			{
				facingRight = false;
				facingLeft = true;
				player.set_flipped(true);
				player.set_animation("run");
			}
		}

		if (down_run == true)
		{
			if (isRunning == true && done == false)
			{
				t1 = steady_clock::now();
				done = true;
			}
			position.y -= getMovementSpeed();
			if (facingRight)
			{
				facingRight = true;
				facingLeft = false;
				player.set_flipped();
				player.set_animation("run");
			}
			else
			{
				facingRight = false;
				facingLeft = true;
				player.set_flipped(true);
				player.set_animation("run");
			}
		}
		break;

	case Idle:
		vX = 0;
		player.set_animation("idle");

		break;

	case LightA:
		lightAttack = true;
		if (attacked == false)
		{
			t1 = steady_clock::now();
			attacked = true;
		}
		player.set_animation("lightAttack");
		if (player.get_current_frame() == 7)
		{
			Attack(enemyList);
		}
		if (player.get_current_frame() == 10)
		{
			attacked = false;
			lightAttack = false;
			currentstate = Idle;
		}
		break;

	case MediumA:
		mediumAttack = true;
		if (attacked == false)
		{
			t1 = steady_clock::now();
			attacked = true;
		}
		player.set_animation("mediumAttack");
		if (player.get_current_frame() == 7)
		{
			Attack(enemyList);
		}
		if (player.get_current_frame() == 10)
		{
			Attack(enemyList);
		}
		if (player.get_current_frame() == 11)
		{
			attacked = false;
			mediumAttack = false;
			currentstate = Idle;
		}
		break;

	case HeavyA:
		heavyAttack = true;
		if (attacked == false)
		{
			t1 = steady_clock::now();
			attacked = true;
		}
		player.set_animation("heavyAttack");
		if (player.get_current_frame() == 9)
		{
			Attack(enemyList);
		}
		if (player.get_current_frame() == 10)
		{
			attacked = false;
			heavyAttack = false;
			currentstate = Idle;
		}
		break;

	case Magic_Charge:
		magicAttack = true;
		
		if (once_Magic == false)
		{
			tempMana = getMana();
			cout << tempMana << endl;
			once_Magic = true;
		}
		Magic_Attack.setVX(Magic_Attack.getVX() + 5);
		if (Magic_Attack.getVX() >= 250)
		{
			Magic_Attack.setVX(250);
		}
		if (tempMana <= (Magic_Attack.getVX() / 5))
		{
			Magic_Attack.setVX(tempMana * 5);
		}
		setMana(tempMana - (Magic_Attack.getVX() / 5));

		player.set_animation("magicAttack");
		break;

	case Magic:
		if (getMana() != 0)
		{
			Magic_Attack.setIsAttacking(true);
			magic.play();
		}
		else
		{
			cout << "Not enough mana" << endl;
		}
		magicAttack = false;
		once_Magic = false;
		currentstate = Idle;
		break;

	}


	t2 = steady_clock::now();
	duration<double> dt = duration_cast<duration<double>> (t2 - t1);
	if (isRunning == true)
	{
		if (dt.count() > 0.0825) // 12 frames a second
		{
			player.next_frame();
			t1 = t2;
		}
	}
	else if (lightAttack == true)
	{
		if (dt.count() > 0.04) // Fast speed
		{
			player.next_frame();
			t1 = t2;
		}
	}
	else if (mediumAttack == true)
	{
		if (dt.count() > 0.0825) // Normal speed
		{
			player.next_frame();
			t1 = t2;
		}
	}
	else if (heavyAttack == true)
	{
		if (dt.count() > 0.15) // Slow speed
		{
			player.next_frame();
			t1 = t2;
		}
	}
	else if (magicAttack == true)
	{
		if (dt.count() > 0.0925)
		{
			if (player.get_current_frame() != 7)
			{
				player.next_frame();
				t1 = t2;
			}
		}
	}

	setMana(getMana() + 0.0001);

	// Stops you from going out of the map
	if ((position.x + (spriteX / 2)) >= 1080) // Right Side
	{
		position.x = 1079 - (spriteX / 2);
	}
	if ((position.x - (spriteX / 2)) <= 0) // Left Side
	{
		position.x = 1 + (spriteX / 2);
	}
	if ((position.y + (spriteY / 2)) >= (465 + spriteY)) // Up side
	{
		position.y = (464 + spriteY) - (spriteY / 2);
	}

	if ((position.y - (spriteY / 2)) <= 0) // Down side
	{
		position.y = (1 + (spriteY / 2));
	}

	player.set_position(position.x, position.y);

}

bool Player::getLightAttack() const
{
	return lightAttack;
}

bool Player::getMediumAttack() const
{
	return mediumAttack;
}

bool Player::getHeavyAttack() const
{
	return heavyAttack;
}

bool Player::getPowerLight() const
{
	return power_light;
}

bool Player::getPowerMedium() const
{
	return power_medium;
}

bool Player::getPowerHeavy() const
{
	return power_heavy;
}

void Player::checkHunger()
{
	if (hunger == maxHunger)
	{
		Super_Hunger = true;
	}
}

bool Player::getSuperHunger() const
{
	return Super_Hunger;
}

bool Player::getRight() const
{
	return right_run;
}

bool Player::getLeft() const
{
	return left_run;
}

bool Player::getUp() const
{
	return up_run;
}

bool Player::getDown() const
{
	return down_run;
}
