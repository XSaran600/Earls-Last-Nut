#ifndef WALL_H
#define WALL_H
#include "Vector2.h"

using namespace std;

class Wall
{
public:
	Wall(float, float, float, float);

	Vector2 getDirection(bool);
	Vector2 getNormal();
	bool getSide(Vector2);

	Vector2 getP1() const;
	Vector2 getP2() const;

private:
	Vector2 p1;
	Vector2 p2;
	float side;
};

#endif
