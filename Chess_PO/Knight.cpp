#include "Knight.h"
#include <iostream>
#include "Board.h"

Knight::Knight()
{
	return;
}

Knight::Knight(int x, int y, int color,int t)
{
	type = t;
	positionOnBoard.setX(x);
	positionOnBoard.setY(y);
	if (color)
	{
		texture.loadFromFile("pieces/knight_b.png");
	}
	else
	{
		texture.loadFromFile("pieces/knight_w.png");
	}

	sprite.setTexture(texture);
	sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	instances.insert(this);
	std::cout << "KnightConstructor\n";
}

Knight::~Knight()
{
	std::cout << "KnightDestructor\n";
	return;
}

bool Knight::isMoveLegal(Coordinates c)
{
	//sprawdz czy na c nie stoi nasza figura
	//sprawdz wszystkie 8 kombinacji

	//check if theres none of our pieces on c

	int color1 = pieceTypeToColor(Board::getPieceTypeOnGivenCoords(positionOnBoard));
	int color2 = pieceTypeToColor(Board::getPieceTypeOnGivenCoords(c));
	if (color1 == color2)
	{
		return false;
	}


	//1. |'
	if (positionOnBoard.getY() - c.getY() == 2 && c.getX() - positionOnBoard.getX() == 1)
	{
		if (Board::getPieceTypeOnGivenCoords(c) != empty)
			Board::capture(c);

		return true;
	}

	//2. __-
	if (positionOnBoard.getY() - c.getY() == 1 && c.getX() - positionOnBoard.getX() == 2)
	{
		if (Board::getPieceTypeOnGivenCoords(c) != empty)
			Board::capture(c);

		return true;
	}

	//3. --_
	if (c.getY() - positionOnBoard.getY() == 1 && c.getX() - positionOnBoard.getX() == 2)
	{
		if (Board::getPieceTypeOnGivenCoords(c) != empty)
			Board::capture(c);

		return true;
	}

	//4. |_
	if (c.getY() - positionOnBoard.getY() == 2 && c.getX() - positionOnBoard.getX() == 1)
	{
		if (Board::getPieceTypeOnGivenCoords(c) != empty)
			Board::capture(c);

		return true;
	}

	//5. _|
	if (c.getY() - positionOnBoard.getY() == 2 && positionOnBoard.getX() - c.getX() == 1)
	{
		if (Board::getPieceTypeOnGivenCoords(c) != empty)
			Board::capture(c);

		return true;
	}
	
	//6. _--
	if (c.getY() - positionOnBoard.getY() == 1 && positionOnBoard.getX() - c.getX() == 2)
	{
		if (Board::getPieceTypeOnGivenCoords(c) != empty)
			Board::capture(c);

		return true;
	}

	//7. -__
	if (positionOnBoard.getY() - c.getY() == 1 && positionOnBoard.getX() - c.getX() == 2)
	{
		if (Board::getPieceTypeOnGivenCoords(c) != empty)
			Board::capture(c);

		return true;
	}

	//8. '|
	if (positionOnBoard.getY() - c.getY() == 2 && positionOnBoard.getX() - c.getX() == 1)
	{
		if (Board::getPieceTypeOnGivenCoords(c) != empty)
			Board::capture(c);

		return true;
	}





	return false;
}
