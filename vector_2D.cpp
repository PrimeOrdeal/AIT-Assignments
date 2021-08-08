#pragma once
#include "vector_2D.h"
#include <math.h>

Vector_2D::Vector_2D(float x, float y)
{
	_x = x;
	_y = y;
}

float Vector_2D::x()
{
	return _x;
}

float Vector_2D::y()
{
	return _y;
}

// This will allow us to use the = operator for the class
void Vector_2D::operator=(Vector_2D rhs)
{
	_x = rhs._x;
	_y = rhs._y;
}

void Vector_2D::operator+=(Vector_2D rhs)
{
	_x += rhs._x;
	_y += rhs._y;
}

/*
	Vector_2D a(3,3);
	Vector_2D b(5,5);
	a = b - a; // results is a equalling (2,2)
*/
Vector_2D Vector_2D::operator-(Vector_2D rhs)
{
	return Vector_2D(_x - rhs._x, _y - rhs._y);
}

Vector_2D Vector_2D::operator+(Vector_2D rhs)
{
	return Vector_2D(_x + rhs._x, _y + rhs._y);

}

// Magnitude is also referred to as length
// Use Pythagoras theorem to calculate.
float Vector_2D::magnitude()
{
	return sqrtf((_x * _x) + (_y * _y));
}

void Vector_2D::normalise() 
{
	float mag = magnitude();

	if (mag > 0.0f)
	{
		_x /= mag;
		_y /= mag;
	}
}

/* Scale will change the magnitude(length) of a vector.
e.g. if we want a player to move 3 units we will scale a vector to be 3 units long(have a magnitude of 3).
*/
void Vector_2D::scale(float scalar)
{
	_x *= scalar;
	_y *= scalar;
}


/*
This method will tell us the angle of the vector in radians from the x axis (between 0 and 1 PI radians). 
We can use that to change our facing direction.
*/
float Vector_2D::angle()
{
	return -atan2f(_y, _x);
}
