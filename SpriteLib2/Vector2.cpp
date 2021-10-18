#include "Vector2.h"

Vector2::Vector2(float a_x, float a_y)
{
	x = a_x;
	y = a_y;
}

Vector2& Vector2::operator-(Vector2& other)
{
	return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator+(Vector2 other)
{
	Vector2 sum;

	sum.x = x + other.x;
	sum.y = y + other.y;

	return sum;
}

Vector2 Vector2::operator*(float scalar)
{
	Vector2 product;

	product.x = x * scalar;
	product.y = y * scalar;

	return product;
}

Vector2& Vector2::operator=(const Vector2& other)
{
	x = other.x;
	y = other.y;

	return (*this);
}

ostream& operator<<(ostream& out, const Vector2& other)
{
	out << other.x << ", " << other.y;

	return out;
}

float Vector2::dot(Vector2 other)
{
	float fullX = x * other.x;
	float fullY = y * other.y;

	return (fullX + fullY);
}

float Vector2::mag()
{
	return sqrt(x * x + y * y);
}

float Vector2::magSq()
{
	return (x * x + y * y);
}