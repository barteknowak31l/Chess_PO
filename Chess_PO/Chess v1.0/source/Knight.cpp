#include "include\Knight.h"
#include <iostream>
#include "include\Board.h"

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
}

Knight::~Knight()
{
	return;
}

bool Knight::isMoveLegal(Coordinates c)
{
	//knight has 8 possible moves
	// can move only if there's no piece or enemy piece on destinated field

	//check if theres none of our pieces on c
	int color1 = pieceTypeToColor(Board::getPieceTypeOnGivenCoords(positionOnBoard));
	int color2 = pieceTypeToColor(Board::getPieceTypeOnGivenCoords(c));
	if (color1 == color2)
	{
		return false;
	}

	//all combinations of moves:

	//1. |'
	if (positionOnBoard.getY() - c.getY() == 2 && c.getX() - positionOnBoard.getX() == 1)
	{
		return true;
	}

	//2. __-
	if (positionOnBoard.getY() - c.getY() == 1 && c.getX() - positionOnBoard.getX() == 2)
	{
		return true;
	}

	//3. --_
	if (c.getY() - positionOnBoard.getY() == 1 && c.getX() - positionOnBoard.getX() == 2)
	{
		return true;
	}

	//4. |_
	if (c.getY() - positionOnBoard.getY() == 2 && c.getX() - positionOnBoard.getX() == 1)
	{
		return true;
	}

	//5. _|
	if (c.getY() - positionOnBoard.getY() == 2 && positionOnBoard.getX() - c.getX() == 1)
	{
		return true;
	}
	
	//6. _--
	if (c.getY() - positionOnBoard.getY() == 1 && positionOnBoard.getX() - c.getX() == 2)
	{
		return true;
	}

	//7. -__
	if (positionOnBoard.getY() - c.getY() == 1 && positionOnBoard.getX() - c.getX() == 2)
	{
		return true;
	}

	//8. '|
	if (positionOnBoard.getY() - c.getY() == 2 && positionOnBoard.getX() - c.getX() == 1)
	{
		return true;
	}




	//tried to do other move than allowed
	return false;
}

void Knight::findFieldsUnderAttack()
{

	//checks all 8 combinations if they are still on the board - if so, add these coordinates to fieldsUnderAttack
	Coordinates tmp = positionOnBoard;
	if (capturedInSimulation)
	{
		return;
	}

	
	//1. |'
	if (positionOnBoard.getX() + 1 <= 7 && positionOnBoard.getY() - 2 >= 0)
	{
		tmp.setX(positionOnBoard.getX() + 1);
		tmp.setY(positionOnBoard.getY() - 2);
		Board::setFieldUnderAttack(tmp, pieceTypeToColor(type), type);
	}


	//2. __-
	if (positionOnBoard.getX() + 2 <= 7 && positionOnBoard.getY() - 1 >= 0)
	{
		tmp.setX(positionOnBoard.getX() + 2);
		tmp.setY(positionOnBoard.getY() - 1);
		Board::setFieldUnderAttack(tmp, pieceTypeToColor(type), type);
	}


	//3. --_
	if (positionOnBoard.getX() + 2 <= 7 && positionOnBoard.getY() + 1 <= 7)
	{
		tmp.setX(positionOnBoard.getX() + 2);
		tmp.setY(positionOnBoard.getY() + 1);
		Board::setFieldUnderAttack(tmp, pieceTypeToColor(type), type);
	}


	//4. |_
	if (positionOnBoard.getX() + 1 <= 7 && positionOnBoard.getY() + 2 <= 7)
	{
		tmp.setX(positionOnBoard.getX() + 1);
		tmp.setY(positionOnBoard.getY() + 2);
		Board::setFieldUnderAttack(tmp, pieceTypeToColor(type), type);
	}

	//5. _|
	if (positionOnBoard.getX() - 1 >= 0 && positionOnBoard.getY() + 2 <= 7)
	{
		tmp.setX(positionOnBoard.getX() - 1);
		tmp.setY(positionOnBoard.getY() + 2);
		Board::setFieldUnderAttack(tmp, pieceTypeToColor(type), type);
	}

	//6. _--
	if (positionOnBoard.getX() - 2 >= 0 && positionOnBoard.getY() + 1 <= 7)
	{
		tmp.setX(positionOnBoard.getX() - 2);
		tmp.setY(positionOnBoard.getY() + 1);
		Board::setFieldUnderAttack(tmp, pieceTypeToColor(type), type);
	}

	//7. -__
	if (positionOnBoard.getX() - 2 >= 0 && positionOnBoard.getY() - 1 >= 0)
	{
		tmp.setX(positionOnBoard.getX() - 2);
		tmp.setY(positionOnBoard.getY() - 1);
		Board::setFieldUnderAttack(tmp, pieceTypeToColor(type), type);
	}

	//8. '|
	if (positionOnBoard.getX() - 1 >= 0 && positionOnBoard.getY() - 2 >= 0)
	{
		tmp.setX(positionOnBoard.getX() - 1);
		tmp.setY(positionOnBoard.getY() - 2);
		Board::setFieldUnderAttack(tmp, pieceTypeToColor(type), type);
	}


}

void Knight::findAllPossibleMoves()
{
	//try to move knight to each of it's possible move combinations that are still on board. If it finds another piece: if it's colors piece - dont add to possible moves, else do add.

	clearSetofCoords();
	Coordinates tmp = positionOnBoard;


	//1. |'
	if (positionOnBoard.getX() + 1 <= 7 && positionOnBoard.getY() - 2 >= 0)
	{
		tmp.setX(positionOnBoard.getX() + 1);
		tmp.setY(positionOnBoard.getY() - 2);
		
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
	}


	//2. __-
	if (positionOnBoard.getX() + 2 <= 7 && positionOnBoard.getY() - 1 >= 0)
	{
		tmp.setX(positionOnBoard.getX() + 2);
		tmp.setY(positionOnBoard.getY() - 1);

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
	}


	//3. --_
	if (positionOnBoard.getX() + 2 <= 7 && positionOnBoard.getY() + 1 <= 7)
	{
		tmp.setX(positionOnBoard.getX() + 2);
		tmp.setY(positionOnBoard.getY() + 1);

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
	}


	//4. |_
	if (positionOnBoard.getX() + 1 <= 7 && positionOnBoard.getY() + 2 <= 7)
	{
		tmp.setX(positionOnBoard.getX() + 1);
		tmp.setY(positionOnBoard.getY() + 2);

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
	}

	//5. _|
	if (positionOnBoard.getX() - 1 >= 0 && positionOnBoard.getY() + 2 <= 7)
	{
		tmp.setX(positionOnBoard.getX() - 1);
		tmp.setY(positionOnBoard.getY() + 2);

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
	}

	//6. _--
	if (positionOnBoard.getX() - 2 >= 0 && positionOnBoard.getY() + 1 <= 7)
	{
		tmp.setX(positionOnBoard.getX() - 2);
		tmp.setY(positionOnBoard.getY() + 1);

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
	}

	//7. -__
	if (positionOnBoard.getX() - 2 >= 0 && positionOnBoard.getY() - 1 >= 0)
	{
		tmp.setX(positionOnBoard.getX() - 2);
		tmp.setY(positionOnBoard.getY() - 1);

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
	}

	//8. '|
	if (positionOnBoard.getX() - 1 >= 0 && positionOnBoard.getY() - 2 >= 0)
	{
		tmp.setX(positionOnBoard.getX() - 1);
		tmp.setY(positionOnBoard.getY() - 2);

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
	}
}