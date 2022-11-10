#include "coordinates.h"


Coordinates::Coordinates()
{
	return;
}
Coordinates::Coordinates(int x, int y) : _x(x), _y(y) {};


bool Coordinates::operator==(Coordinates c)
{
	return (getX() == c.getX() && getY() == c.getY());
}
bool Coordinates::operator!=(Coordinates c)
{
	return !operator==(c);
}

int Coordinates::getX()
{
	return _x;
}
int Coordinates::getY()
{
	return _y;
}
void Coordinates::setX(int x)
{
	_x = x;
}
void Coordinates::setY(int y)
{
	_y = y;
}
char Coordinates::xToLetters(int x)
{
	return x + 17;	//offset w ASCII
}