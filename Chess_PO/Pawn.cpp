#include "Pawn.h"
#include <iostream>

Pawn::Pawn()
{
	return;
}

Pawn::Pawn(int x, int y, int color) 
{

	positionOnBoard.setX(x);
	positionOnBoard.setY(y);
	if (color)
	{
		texture.loadFromFile("pieces/pawn_b.png");
	}
	else
	{
		texture.loadFromFile("pieces/pawn_w.png");
	}

	sprite.setTexture(texture);
	
	//idk czy to zadziala
	sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);


	instances.insert(this);

	std::cout << "PawnConstructor\n";
}

Pawn::~Pawn()
{
	std::cout << "PawnDestructor\n";
	return;
}

void Pawn::move(Coordinates c)
{
	return;
}
