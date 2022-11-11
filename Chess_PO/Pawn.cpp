#include "Pawn.h"
#include <iostream>
#include <cstdlib>
#include "Board.h"

Pawn::Pawn()
{
	return;
}

Pawn::Pawn(int x, int y, int color,int t) 
{

	type = t;

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
	sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	instances.insert(this);

	firstMove = true;

	std::cout << "PawnConstructor\n";
}

Pawn::~Pawn()
{
	std::cout << "PawnDestructor\n";
	return;
}

bool Pawn::isMoveLegal(Coordinates c)
{
	//pierwszy ruch moze byc o dwa pola -sprawdz czy ruch nr1
	//moze ruszyc sie tylko do przodu i  tylko jesli przed nim nic nie stoi
	//moze ruszyc sie na bok jesli stoi tam przeciwnik - BICIE

	if (type == b_pawn)
	{
		if (firstMove)
		{

			//check +2 move
			if (c.getY() - positionOnBoard.getY() == 2 && c.getX() - positionOnBoard.getX() == 0)
			{
				firstMove = false;
				return true;
			}
			//check +1 move
			if (c.getY() - positionOnBoard.getY() == 1 && c.getX() - positionOnBoard.getX() == 0)
			{
				firstMove = false;
				return true;
			}
			//check capture
			if (c.getY() - positionOnBoard.getY() == 1 && abs(c.getX() - positionOnBoard.getX()) == 1)
			{
				if (Board::getPieceTypeOnGivenCoords(c) != empty)
				{
					int color1 = pieceTypeToColor(Board::getPieceTypeOnGivenCoords(positionOnBoard));
					int color2 = pieceTypeToColor(Board::getPieceTypeOnGivenCoords(c));
					if (color1 != color2)
					{
						firstMove = false;
						Board::capture(c);
						return true;
					}
				}
			}
		}
		else
		{
			//check +1 move
			if (c.getY() - positionOnBoard.getY() == 1 && c.getX() - positionOnBoard.getX() == 0)
			{

				return true;
			}
			//check capture
			if (c.getY() - positionOnBoard.getY() == 1 && abs(c.getX() - positionOnBoard.getX()) == 1)
			{
				if (Board::getPieceTypeOnGivenCoords(c) != empty)
				{
					int color1 = pieceTypeToColor(Board::getPieceTypeOnGivenCoords(positionOnBoard));
					int color2 = pieceTypeToColor(Board::getPieceTypeOnGivenCoords(c));
					if (color1 != color2)
					{
						Board::capture(c);
						return true;
					}
				}
			}
		}
	}


	if (type == w_pawn)
	{
		if (firstMove)
		{

			//check +2 move
			if (positionOnBoard.getY() - c.getY() == 2 && c.getX() - positionOnBoard.getX() == 0)
			{
				firstMove = false;
				return true;
			}
			//check +1 move
			if (positionOnBoard.getY() - c.getY() == 1 && c.getX() - positionOnBoard.getX() == 0)
			{
				firstMove = false;
				return true;
			}
			//check capture
			if (positionOnBoard.getY() - c.getY() == 1 && abs(c.getX() - positionOnBoard.getX()) == 1)
			{
				if (Board::getPieceTypeOnGivenCoords(c) != empty)
				{
					int color1 = pieceTypeToColor(Board::getPieceTypeOnGivenCoords(positionOnBoard));
					int color2 = pieceTypeToColor(Board::getPieceTypeOnGivenCoords(c));
					if (color1 != color2)
					{
						firstMove = false;
						Board::capture(c);
						return true;
					}
				}
			}
		}
		else
		{
			//check +1 move
			if (positionOnBoard.getY() - c.getY() == 1 && c.getX() - positionOnBoard.getX() == 0)
			{

				return true;
			}
			//check capture
			if (positionOnBoard.getY() - c.getY() == 1 && abs(c.getX() - positionOnBoard.getX()) == 1)
			{
				if (Board::getPieceTypeOnGivenCoords(c) != empty)
				{
					int color1 = pieceTypeToColor(Board::getPieceTypeOnGivenCoords(positionOnBoard));
					int color2 = pieceTypeToColor(Board::getPieceTypeOnGivenCoords(c));
					if (color1 != color2)
					{
						Board::capture(c);
						return true;
					}
				}
			}
		}
	}

	

	std::cout << "INCORRECT PAWN MOVE :(\n";
	return false;
}

void Pawn::findFieldsUnderAttack()
{
	Coordinates tmp = positionOnBoard;

	//white
	if (type == w_pawn)
	{
		//left attack
		if (positionOnBoard.getX() - 1 >= 0 && positionOnBoard.getY() - 1 >= 0)
		{
			tmp.setX(positionOnBoard.getX() - 1);
			tmp.setY(positionOnBoard.getY() - 1);
			Board::setFieldUnderAttack(tmp,0, type);
		}

		//right attack
		if (positionOnBoard.getX() + 1 <= 7 && positionOnBoard.getY() - 1 >= 0)
		{
			tmp.setX(positionOnBoard.getX() + 1);
			tmp.setY(positionOnBoard.getY() - 1);
			Board::setFieldUnderAttack(tmp,0, type);
		}

	}


	//black
	if (type == b_pawn)
	{
		//left attack
		if (positionOnBoard.getX() - 1 >= 0 && positionOnBoard.getY() + 1 <= 7)
		{
			tmp.setX(positionOnBoard.getX() - 1);
			tmp.setY(positionOnBoard.getY() + 1);
			Board::setFieldUnderAttack(tmp,1, type);
		}

		//right attack
		if (positionOnBoard.getX() + 1 <= 7 && positionOnBoard.getY() + 1 <= 7)
		{
			tmp.setX(positionOnBoard.getX() + 1);
			tmp.setY(positionOnBoard.getY() + 1);
			Board::setFieldUnderAttack(tmp,1, type);
		}

	}



}
