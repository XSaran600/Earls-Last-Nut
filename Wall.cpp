#include "Wall.h"

Wall::Wall(float x1, float y1, float x2, float y2)
{
	p1.x = x1;
	p1.y = y1;
	p2.x = x2;
	p2.y = y2;
}

Vector2 Wall::getDirection(bool p1_to_p2)
{
	Vector2 temp;
	Vector2 direction;
	Vector2 inverse;

	temp = p1;
	direction.x = temp.x - p2.x;
	direction.y = temp.y - p2.y;

	if (p1_to_p2 == true)
		return direction * -1;
	else
		return direction;
}

Vector2 Wall::getNormal()
{
	Vector2 Para;
	Para = getDirection(true);
	Vector2 Perp;

	Perp.y = Para.x * -1;
	Perp.x = Para.y * +1;

	return Perp;
}

bool Wall::getSide(Vector2 point)
{
	Vector2 p1_to_player_normal;
	p1_to_player_normal = point - p1;
	Vector2 wallNormal;
	wallNormal = getNormal();

	float side = p1_to_player_normal.dot(wallNormal);

	bool wallSide = (side > 0) ? true : false;
	return wallSide;
}

Vector2 Wall::getP1() const
{
	return p1;
}

Vector2 Wall::getP2() const
{
	return p2;
}