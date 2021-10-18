#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "spritelib/spritelib.h"
#include "mainCharacter.h"
#include "Enemy.h"



using namespace spritelib;
using namespace std;
using namespace std::chrono;

class Enemy;
class Player;

class Projectile
{
public:
	Projectile(float frameSizeX, float frameSizey); // Gets the frame sizes
	~Projectile();

	bool One_Dimensional_Check(float x1, float x2, float x3, float x4); // Collision Check

	bool Collision_AABB(Enemy &other); // Collision Check

	void Update(Player &player, Sprite &a_sprite, vector<Enemy*>&); // Updates the projectile and deals damage

	float getPositionX() const;
	void setPositionX(float posX);

	float getPositionY() const;
	void setPositionY(float posY);

	float getVX() const;
	void setVX(float posX);

	float getVY() const;
	void setVY(float posX);

	bool getIsAttacking() const;
	void setIsAttacking(bool Att);

	friend void Process();


private:
	math::Vector3 position; // Position of Projectile
	math::Vector3 start; // Start position of Projectile
	math::Vector3 frameSize; // Frame size
	float vX = 0; // Velocity X
	float vY = 0; // Velocity Y
	double g = -9.8; // Gravity
	bool timer = false; // Checks if the start timer has been started
	bool isAttacking = false; // Checks if the player attacked
	float damage = 1; // The damage multiplier

	steady_clock::time_point t1; // Start time
	steady_clock::time_point t2; // End time
};

#endif