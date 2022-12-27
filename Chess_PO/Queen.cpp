#include "Queen.h"
#include <iostream>
#include "Board.h"

Queen::Queen()
{
	return;
}

Queen::Queen(int x, int y, int color,int t)
{
	type = t;
	positionOnBoard.setX(x);
	positionOnBoard.setY(y);
	if (color)
	{
		texture.loadFromFile("pieces/queen_b.png");
	}
	else
	{
		texture.loadFromFile("pieces/queen_w.png");
	}

	sprite.setTexture(texture);

	//idk czy to zadziala
	sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);


	instances.insert(this);

}

Queen::~Queen()
{
	return;
}

bool Queen::isMoveLegal(Coordinates c)
{
	//Queen can perform moves as rook and bishop do:

	return diagonalMove(c) || horizontalVerticalMove(c);
}


bool Queen::diagonalMove(Coordinates c)
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

bool Queen::horizontalVerticalMove(Coordinates c)
{
	//can move horizontally or vertically
	//can't move through other pieces
	//if there's an enemy piece on destinated field, it can be captured


	//check if vertical or horizontal move
	if ((positionOnBoard.getX() != c.getX() && positionOnBoard.getY() == c.getY()) || (positionOnBoard.getY() != c.getY() && positionOnBoard.getX() == c.getX()))
	{

		//check for obstacles
		Coordinates tmp;
		//horizontal
		if (c.getX() - positionOnBoard.getX() != 0)
		{
			tmp.setY(positionOnBoard.getY());

			int dir = c.getX() - positionOnBoard.getX(); // dir > 0 means piece moves right

			if (dir > 0)
			{
				//piece moves right
				for (int i = positionOnBoard.getX(); i < c.getX(); i++)
				{
					tmp.setX(i);

					//if there is a colliding piece
					if (Board::getPieceTypeOnGivenCoords(tmp) != empty && tmp != positionOnBoard)
					{
						return false;
					}

				}
			}
			else
			{
				//piece moves left
				for (int i = positionOnBoard.getX(); i > c.getX(); i--)
				{
					tmp.setX(i);

					//if there is a colliding piece
					if (Board::getPieceTypeOnGivenCoords(tmp) != empty && tmp != positionOnBoard && i != positionOnBoard.getX())
					{
						return false;
					}

				}
			}
		}

		//vertical
		if (c.getY() - positionOnBoard.getY() != 0)
		{
			tmp.setX(positionOnBoard.getX());

			int dir = c.getY() - positionOnBoard.getY(); // dir > 0 means piece moves down

			if (dir > 0)
			{
				//piece moves down
				for (int i = positionOnBoard.getY(); i < c.getY(); i++)
				{
					tmp.setY(i);

					//if there is a colliding piece
					if (Board::getPieceTypeOnGivenCoords(tmp) != empty && tmp != positionOnBoard && i != c.getY())
					{
						return false;
					}

				}
			}
			else
			{
				//piece moves up
				for (int i = positionOnBoard.getY(); i > c.getY(); i--)
				{
					tmp.setY(i);

					//if there is a colliding piece
					if (Board::getPieceTypeOnGivenCoords(tmp) != empty && tmp != positionOnBoard && i != positionOnBoard.getY())
					{
						return false;
					}

				}
			}
		}

		//check for capture
		if (Board::getPieceTypeOnGivenCoords(c) != empty)
		{
			//check if if it's an enemy piece
			int color1 = pieceTypeToColor(Board::getPieceTypeOnGivenCoords(positionOnBoard));
			int color2 = pieceTypeToColor(Board::getPieceTypeOnGivenCoords(c));
			
			//trying to capture own piece - incorrect
			if (color1 == color2)
			{
				return false;
			}
		}


		//correct move
		return true;


	}


	//not horizontal or vertical move
	return false;
}

void Queen::findFieldsUnderAttack()
{
	//Queen can perform moves as rook and bishop do:

	if (capturedInSimulation)
	{
		return;
	}

	diagonalUnderAttack();
	horizontalVerticalUnderAttack();
}

void Queen::diagonalUnderAttack()
{

	//check all fields on diagonals until a piece is found or went off the board

	Coordinates tmp = positionOnBoard;
	int i = 1;

	//up right
	while (positionOnBoard.getX() + i <= 7 && positionOnBoard.getY() - i >= 0)
	{
		tmp.setX(positionOnBoard.getX() + i);
		tmp.setY(positionOnBoard.getY() - i);


		Board::setFieldUnderAttack(tmp, pieceTypeToColor(type), type);

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


		Board::setFieldUnderAttack(tmp, pieceTypeToColor(type), type);

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

void Queen::horizontalVerticalUnderAttack()
{
	//iterate through each direction horizontally and vertically until piece goes off board or finds another piece, set those fields as under attack (including field with another piece
	//if found).

	Coordinates tmp = positionOnBoard;

	//up
	int i = 1;
	while (positionOnBoard.getY() - i >= 0)
	{
		tmp.setX(positionOnBoard.getX());
		tmp.setY(positionOnBoard.getY() - i);


		Board::setFieldUnderAttack(tmp, pieceTypeToColor(type), type);

		i++;

		if (Board::getPieceTypeOnGivenCoords(tmp) != empty)
			break;
	}

	//down
	i = 1;
	while (positionOnBoard.getY() + i <= 7)
	{
		tmp.setX(positionOnBoard.getX());
		tmp.setY(positionOnBoard.getY() + i);


		Board::setFieldUnderAttack(tmp, pieceTypeToColor(type), type);

		i++;

		if (Board::getPieceTypeOnGivenCoords(tmp) != empty)
			break;
	}

	//right
	i = 1;
	while (positionOnBoard.getX() + i <= 7)
	{
		tmp.setX(positionOnBoard.getX() + i);
		tmp.setY(positionOnBoard.getY());


		Board::setFieldUnderAttack(tmp, pieceTypeToColor(type), type);

		i++;

		if (Board::getPieceTypeOnGivenCoords(tmp) != empty)
			break;
	}

	//left
	i = 1;
	while (positionOnBoard.getX() - i >= 0)
	{
		tmp.setX(positionOnBoard.getX() - i);
		tmp.setY(positionOnBoard.getY());


		Board::setFieldUnderAttack(tmp, pieceTypeToColor(type), type);

		i++;

		if (Board::getPieceTypeOnGivenCoords(tmp) != empty)
			break;
	}
}

void Queen::findAllPossibleMoves()
{
	//Queen can perform moves as rook and bishop do:

	clearSetofCoords();
	bishopMoves();
	rookMoves();
}

void Queen::bishopMoves()
{
	//try to move a bishop each of its diagonals until it goes off board or finds another piece: if it's colors piece - dont add to possible moves, else do add.

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

void Queen::rookMoves()
{
	//try to move a rook each direction horizontally and vertically until it goes off board or finds another piece: if it's colors piece - dont add to possible moves, else do add.

	Coordinates tmp;

	//up
	int i = 1;
	while (positionOnBoard.getY() - i >= 0)
	{
		tmp.setX(positionOnBoard.getX());
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

	//down
	i = 1;
	while (positionOnBoard.getY() + i <= 7)
	{
		tmp.setX(positionOnBoard.getX());
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

	//right
	i = 1;
	while (positionOnBoard.getX() + i <= 7)
	{
		tmp.setX(positionOnBoard.getX() + i);
		tmp.setY(positionOnBoard.getY());

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

	//left
	i = 1;
	while (positionOnBoard.getX() - i >= 0)
	{
		tmp.setX(positionOnBoard.getX() - i);
		tmp.setY(positionOnBoard.getY());

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