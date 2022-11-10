#include "King.h"
#include <iostream>
#include "Board.h"

King::King()
{
	return;
}

King::King(int x, int y, int color,int t)
{
	type = t;
	positionOnBoard.setX(x);
	positionOnBoard.setY(y);
	if (color)
	{
		texture.loadFromFile("pieces/king_b.png");
	}
	else
	{
		texture.loadFromFile("pieces/king_w.png");
	}

	sprite.setTexture(texture);
	sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	instances.insert(this);
	std::cout << "KingConstructor\n";
}

King::~King()
{
	std::cout << "KingDestructor\n";
	return;
}

bool King::isMoveLegal(Coordinates c)
{
	//sprawdz czy na nowym polu nie ma naszej figury
	//8 kombinacji pole musi byc wolne albo zajete przez przeciwnika

	int color1 = pieceTypeToColor(Board::getPieceTypeOnGivenCoords(c));
	int color2 = pieceTypeToColor(type);
	if (color1 == color2)
	{
		std::cout << "krol probuje zbic swoja figure\n";
		return false;
	}

	//1. up
	if (positionOnBoard.getX() == c.getX() && positionOnBoard.getY() - c.getY() == 1)
	{
		std::cout << "king up move\n";
		if (Board::getPieceTypeOnGivenCoords(c) != empty)
			Board::capture(c);

		return true;
	}

	//2. up  - right
	if (c.getX() - positionOnBoard.getX() == 1 && positionOnBoard.getY() - c.getY() == 1)
	{
		std::cout << "king up-right move\n";
		if (Board::getPieceTypeOnGivenCoords(c) != empty)
			Board::capture(c);

		return true;
	}

	//3. right
	if (c.getX() - positionOnBoard.getX() == 1 && positionOnBoard.getY() == c.getY())
	{
		std::cout << "king right move\n";
		if (Board::getPieceTypeOnGivenCoords(c) != empty)
			Board::capture(c);

		return true;
	}

	//4. down  - right
	if (c.getX() - positionOnBoard.getX() == 1 && c.getY() - positionOnBoard.getY() == 1)
	{
		std::cout << "king down-right move\n";
		if (Board::getPieceTypeOnGivenCoords(c) != empty)
			Board::capture(c);

		return true;
	}

	//5. down
	if (c.getX() == positionOnBoard.getX() && c.getY() - positionOnBoard.getY() == 1)
	{
		std::cout << "king down move\n";
		if (Board::getPieceTypeOnGivenCoords(c) != empty)
			Board::capture(c);

		return true;
	}

	//6. down  - left
	if (positionOnBoard.getX() - c.getX() == 1 && c.getY() - positionOnBoard.getY() == 1)
	{
		std::cout << "king down-left move\n";
		if (Board::getPieceTypeOnGivenCoords(c) != empty)
			Board::capture(c);

		return true;
	}

	//7. left
	if (positionOnBoard.getX() - c.getX() == 1 && c.getY() == positionOnBoard.getY() == 1)
	{
		std::cout << "king left move\n";
		if (Board::getPieceTypeOnGivenCoords(c) != empty)
			Board::capture(c);

		return true;
	}

	//8. up  - left
	if (positionOnBoard.getX() - c.getX() == 1 && positionOnBoard.getY() - c.getY() == 1)
	{
		std::cout << "king up-left move\n";
		if (Board::getPieceTypeOnGivenCoords(c) != empty)
			Board::capture(c);

		return true;
	}






	//not legal move
	return false;
}

void King::setFieldsUnderAttack()
{
	;
}
