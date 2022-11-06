#include "Pawn.h"
#include <iostream>

Pawn::Pawn()
{
	return;
}

Pawn::Pawn(int x, int y, int color, int i) 
{

	position.setX(x);
	position.setY(y);
	if (color)
	{
		texture.loadFromFile("pieces/pawn_b.png");
	}
	else
	{
		texture.loadFromFile("pieces/pawn_w.png");
	}

	sprite.setTexture(texture);
	sprite.setPosition(sf::Vector2f(position.getX(), position.getY()));


	instances.insert(this);
}

Pawn::~Pawn()
{
	return;
}

void Pawn::move(Coordinates c)
{
	return;
}
