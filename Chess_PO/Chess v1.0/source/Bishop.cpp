#include "include\Bishop.h"
#include <iostream>
#include "include\Board.h"
#include <cstdlib>


Bishop::Bishop()
{
	return;
}

Bishop::Bishop(int x, int y, int color,int t)
{
	type = t;
	positionOnBoard.setX(x);
	positionOnBoard.setY(y);
	if (color)
	{
		texture.loadFromFile("pieces/bishop_b.png");
	}
	else
	{
		texture.loadFromFile("pieces/bishop_w.png");
	}

	sprite.setTexture(texture);
	sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	instances.insert(this);
}

Bishop::~Bishop()
{
	return;
}

bool Bishop::isMoveLegal(Coordinates c)
{

	//bishop can move diagonally
	//can't move through other pieces
	//function checks of following condition is met: abs(dx) == abs(dy) - means if the difference of horizontal and vertical shift (i.e newPosition.x - currentPosition.x) are equal - 
	//then the move is a diagonal move
	//also need to check if there isn't a piece of the same color on destinated field



	int color1 = pieceTypeToColor(Board::getPieceTypeOnGivenCoords(c));
	int color2 = pieceTypeToColor(type);
	if (color1 == color2)
	{
		return false;
	}

	//correct move
	if (std::abs(c.getX() - positionOnBoard.getX()) == std::abs(c.getY() - positionOnBoard.getY()))
	{
		Coordinates tmp = positionOnBoard;

		//check for obstacles
		//up right
		if (c.getX() > positionOnBoard.getX() && positionOnBoard.getY() > c.getY())
		{
			for (int i = 1; i < c.getX() - positionOnBoard.getX(); i++)
			{
				tmp.setX(tmp.getX() + 1);
				tmp.setY(tmp.getY() - 1);

				if (Board::getPieceTypeOnGivenCoords(tmp) != empty)
				{
					return false;
				}

			}
		}

		//down right
		if (c.getX() > positionOnBoard.getX() && c.getY() > positionOnBoard.getY())
		{
			for (int i = 1; i < c.getX() - positionOnBoard.getX(); i++)
			{
				tmp.setX(tmp.getX() + 1);
				tmp.setY(tmp.getY() + 1);
				if (Board::getPieceTypeOnGivenCoords(tmp) != empty)
				{
					return false;
				}

			}
		}

		//down left
		if (positionOnBoard.getX() > c.getX() && c.getY() > positionOnBoard.getY())
		{
			for (int i = 1; i < c.getY() - positionOnBoard.getY(); i++)
			{
				tmp.setX(tmp.getX() - 1);
				tmp.setY(tmp.getY() + 1);

				if (Board::getPieceTypeOnGivenCoords(tmp) != empty)
				{
					return false;
				}

			}
		}

		//up left
		if (positionOnBoard.getX() > c.getX() && positionOnBoard.getY() > c.getY())
		{
			for (int i = 1; i < positionOnBoard.getY() - c.getY(); i++)
			{
				tmp.setX(tmp.getX() - 1);
				tmp.setY(tmp.getY() - 1);

				if (Board::getPieceTypeOnGivenCoords(tmp) != empty)
				{
					return false;
				}

			}
		}


		//correct move
		return true;
	}

	//not a diagonal move
	return false;
}

void Bishop::findFieldsUnderAttack()
{

	//check all fields on diagonals until a piece is found or went off the board


	Coordinates tmp = positionOnBoard;
	if (capturedInSimulation)
	{
		return;
	}

	int i = 1;

	//up right
	while (positionOnBoard.getX() + i <= 7 && positionOnBoard.getY() - i >= 0)
	{
		tmp.setX(positionOnBoard.getX() + i);
		tmp.setY(positionOnBoard.getY() - i);


		Board::setFieldUnderAttack(tmp, pieceTypeToColor(type),type);

		i++;

		if (Board::getPieceTypeOnGivenCoords(tmp) != empty)
			break;
	}

	//up left
	i = 1;
	while (positionOnBoard.getX() - i >= 0 && positionOnBoard.getY() - i >= 0)
	{
		tmp.setX(positionOnBoard.getX() - i);
		tmp.setY(positionOnBoard.getY() - i);

		Board::setFieldUnderAttack(tmp, pieceTypeToColor(type),type);

		i++;

		if (Board::getPieceTypeOnGivenCoords(tmp) != empty)
			break;
	}

	//down right
	i = 1;
	while (positionOnBoard.getX() + i <= 7 && positionOnBoard.getY() + i <= 7)
	{
		tmp.setX(positionOnBoard.getX() + i);
		tmp.setY(positionOnBoard.getY() + i);

		Board::setFieldUnderAttack(tmp, pieceTypeToColor(type), type);

		i++;

		if (Board::getPieceTypeOnGivenCoords(tmp) != empty)
			break;
	}

	//down left
	i = 1;
	while (positionOnBoard.getX() - i >= 0 && positionOnBoard.getY() + i <= 7)
	{
		tmp.setX(positionOnBoard.getX() - i);
		tmp.setY(positionOnBoard.getY() + i);

		Board::setFieldUnderAttack(tmp, pieceTypeToColor(type), type);

		i++;

		if (Board::getPieceTypeOnGivenCoords(tmp) != empty)
			break;
	}



}

void Bishop::findAllPossibleMoves()
{
	//try to move a bishop each of its diagonals until it goes off board or finds another piece: if it's colors piece - dont add to possible moves, else do add.

	clearSetofCoords();

	Coordinates tmp = positionOnBoard;

	int i = 1;
	//up right
	while (positionOnBoard.getX() + i <= 7 && positionOnBoard.getY() - i >= 0)
	{
		tmp.setX(positionOnBoard.getX() + i);
		tmp.setY(positionOnBoard.getY() - i);


		if (Board::getPieceTypeOnGivenCoords(tmp) != empty)
		{
			if (pieceTypeToColor(type) != pieceTypeToColor(Board::getPieceTypeOnGivenCoords(tmp)))
			{
				addCoordsToSet(tmp);
			}
		}
		else
		{
			addCoordsToSet(tmp);
		}

		i++;

		if (Board::getPieceTypeOnGivenCoords(tmp) != empty)
			break;
	}

	//up left
	i = 1;
	while (positionOnBoard.getX() - i >= 0 && positionOnBoard.getY() - i >= 0)
	{
		tmp.setX(positionOnBoard.getX() - i);
		tmp.setY(positionOnBoard.getY() - i);

		if (Board::getPieceTypeOnGivenCoords(tmp) != empty)
		{
			if (pieceTypeToColor(type) != pieceTypeToColor(Board::getPieceTypeOnGivenCoords(tmp)))
			{
				addCoordsToSet(tmp);
			}
		}
		else
		{
			addCoordsToSet(tmp);
		}

		i++;

		if (Board::getPieceTypeOnGivenCoords(tmp) != empty)
			break;
	}

	//down right
	i = 1;
	while (positionOnBoard.getX() + i <= 7 && positionOnBoard.getY() + i <= 7)
	{
		tmp.setX(positionOnBoard.getX() + i);
		tmp.setY(positionOnBoard.getY() + i);

		if (Board::getPieceTypeOnGivenCoords(tmp) != empty)
		{
			if (pieceTypeToColor(type) != pieceTypeToColor(Board::getPieceTypeOnGivenCoords(tmp)))
			{
				addCoordsToSet(tmp);
			}
		}
		else
		{
			addCoordsToSet(tmp);
		}

		i++;

		if (Board::getPieceTypeOnGivenCoords(tmp) != empty)
			break;
	}

	//down left
	i = 1;
	while (positionOnBoard.getX() - i >= 0 && positionOnBoard.getY() + i <= 7)
	{
		tmp.setX(positionOnBoard.getX() - i);
		tmp.setY(positionOnBoard.getY() + i);

		if (Board::getPieceTypeOnGivenCoords(tmp) != empty)
		{
			if (pieceTypeToColor(type) != pieceTypeToColor(Board::getPieceTypeOnGivenCoords(tmp)))
			{
				addCoordsToSet(tmp);
			}
		}
		else
		{
			addCoordsToSet(tmp);
		}

		i++;

		if (Board::getPieceTypeOnGivenCoords(tmp) != empty)
			break;
	}

}

