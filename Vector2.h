#ifndef VECTOR2_H
#define VECTOR2_H
#include <cmath>
#include <iostream>
using namespace std;

class Vector2
{

public:
	Vector2(float = 0, float = 0);

	Vector2& operator-(Vector2&);
	Vector2 operator+(Vector2);
	Vector2 operator*(float);

	Vector2& operator=(const Vector2& other);

	friend ostream& operator<<(ostream&, const Vector2&);

	float dot(Vector2);
	float mag();
	float magSq();

	float x;
	float y;
};

#endif