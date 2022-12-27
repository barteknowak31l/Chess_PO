#include "Rook.h"
#include<iostream>
#include <algorithm>
#include "Board.h"

Rook::Rook()
{
	;
}

Rook::Rook(int x, int y, int color,int t)
{

	type = t;

	positionOnBoard.setX(x);
	positionOnBoard.setY(y);

	if (color)
	{
		texture.loadFromFile("pieces/rook_b.png");
	}
	else
	{
		texture.loadFromFile("pieces/rook_w.png");
	}


	sprite.setTexture(texture);
	sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	instances.insert(this);

	firstMove = true;

}

Rook::~Rook()
{
	return;
}

bool Rook::isMoveLegal(Coordinates c)
{
	//can move horizontally or vertically
	//can't move through other pieces
	//if there's an enemy piece on destinated field, it can be captured


	//check if vertical or horizontal move
	if ( (positionOnBoard.getX() != c.getX() && positionOnBoard.getY() == c.getY()) || (positionOnBoard.getY() != c.getY() && positionOnBoard.getX() == c.getX()))
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
					if (Board::getPieceTypeOnGivenCoords(tmp) != empty && tmp != positionOnBoard && i != positionOnBoard.getX() )
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

		if (firstMove)
		{
			firstMove = false;
		}

		return true;


	}

	//not horizontal or vertical move
	return false;
}

void Rook::findFieldsUnderAttack()
{
	//iterate through each direction horizontally and vertically until piece goes off board or finds another piece, set those fields as under attack (including field with another piece
	//if found).

	Coordinates tmp = positionOnBoard;
	if (capturedInSimulation)
	{
		return;
	}

	//up
	int i = 1;
	while (positionOnBoard.getY() - i >= 0)
	{
		tmp.setX(positionOnBoard.getX());
		tmp.setY(positionOnBoard.getY() - i);

		Board::setFieldUnderAttack(tmp,pieceTypeToColor(type), type);

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

		Board::setFieldUnderAttack(tmp,pieceTypeToColor(type), type);

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

void Rook::findAllPossibleMoves()
{

	//try to move a rook each direction horizontally and vertically until it goes off board or finds another piece: if it's colors piece - dont add to possible moves, else do add.

	clearSetofCoords();
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