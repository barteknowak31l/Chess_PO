#include "include\King.h"
#include <iostream>
#include "include\Board.h"

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

	firstMove = true;

}

King::~King()
{
	return;
}

bool King::isMoveLegal(Coordinates c)
{
	//king has 8 possible combinations of movement
	//king has special move - castle - special conditions has to be met - it is checked in castle(Coordinates) function
	//there can't be piece of the same color on destinated field
	//king cannot move to field under attack - this is checked in simulation step - see Board::simulateNextMove(Piece*, Coordinates)


	//try castle
	int cas = castle(c);
	
	if (cas> 0 && firstMove && Board::check_white== 0 && Board::check_black ==0)
	{
		firstMove = false;

		//pass the control to Board class to perform a castle move
		Board::castle(this, c, cas);

		//castle move was done by Board class, no further actions needed
		return false;
	}


	int color1 = pieceTypeToColor(Board::getPieceTypeOnGivenCoords(c));
	int color2 = pieceTypeToColor(type);
	if (color1 == color2)
	{
		return false;
	}
	

	//all possible combinations:

	//1. up
	if (positionOnBoard.getX() == c.getX() && positionOnBoard.getY() - c.getY() == 1 && Board::getFieldUnderAttack(c, !pieceTypeToColor(type)) == 0)
	{
		if (firstMove)
		{
			firstMove = false;
		}

		return true;
	}

	//2. up  - right
	if (c.getX() - positionOnBoard.getX() == 1 && positionOnBoard.getY() - c.getY() == 1 && Board::getFieldUnderAttack(c, !pieceTypeToColor(type)) == 0)
	{
		if (firstMove)
		{
			firstMove = false;
		}

		return true;
	}

	//3. right
	if (c.getX() - positionOnBoard.getX() == 1 && positionOnBoard.getY() == c.getY() && Board::getFieldUnderAttack(c, !pieceTypeToColor(type)) == 0)
	{
		if (firstMove)
		{
			firstMove = false;
		}

		return true;
	}

	//4. down  - right
	if (c.getX() - positionOnBoard.getX() == 1 && c.getY() - positionOnBoard.getY() == 1 && Board::getFieldUnderAttack(c, !pieceTypeToColor(type)) == 0)
	{
		if (firstMove)
		{
			firstMove = false;
		}

		return true;
	}

	//5. down
	if (c.getX() == positionOnBoard.getX() && c.getY() - positionOnBoard.getY() == 1 && Board::getFieldUnderAttack(c, !pieceTypeToColor(type)) == 0)
	{
		if (firstMove)
		{
			firstMove = false;
		}

		return true;
	}

	//6. down  - left
	if (positionOnBoard.getX() - c.getX() == 1 && c.getY() - positionOnBoard.getY() == 1 && Board::getFieldUnderAttack(c, !pieceTypeToColor(type)) == 0)
	{
		if (firstMove)
		{
			firstMove = false;
		}

		return true;
	}

	//7. left
	if (positionOnBoard.getX() - c.getX() == 1 && c.getY() == positionOnBoard.getY() == 1 && Board::getFieldUnderAttack(c, !pieceTypeToColor(type)) == 0)
	{
		if (firstMove)
		{
			firstMove = false;
		}

		return true;
	}

	//8. up  - left
	if (positionOnBoard.getX() - c.getX() == 1 && positionOnBoard.getY() - c.getY() == 1 && Board::getFieldUnderAttack(c, !pieceTypeToColor(type)) == 0)
	{
		if (firstMove)
		{
			firstMove = false;
		}

		return true;
	}

	//not legal move
	return false;
}

void King::findFieldsUnderAttack()
{
	//check all 8 combinations and check if that field is still on board

	Coordinates tmp = positionOnBoard;
	if (capturedInSimulation)
	{
		return;
	}

	//1. up
	if (positionOnBoard.getY() - 1 >= 0)
	{
		tmp.setX(positionOnBoard.getX());
		tmp.setY(positionOnBoard.getY() -1);

		Board::setFieldUnderAttack(tmp, pieceTypeToColor(type), type);
	}

	//2. up  - right
	if (positionOnBoard.getX() + 1 <= 7 && positionOnBoard.getY() - 1 >= 0)
	{
		tmp.setX(positionOnBoard.getX() + 1);
		tmp.setY(positionOnBoard.getY() - 1);

		Board::setFieldUnderAttack(tmp, pieceTypeToColor(type), type);
	}

	//3. right
	if (positionOnBoard.getX() + 1 <= 7)
	{
		tmp.setX(positionOnBoard.getX() + 1);
		tmp.setY(positionOnBoard.getY());

		Board::setFieldUnderAttack(tmp, pieceTypeToColor(type), type);
	}

	//4. down  - right
	if (positionOnBoard.getX() + 1 <= 7 && positionOnBoard.getY() + 1 <= 7)
	{
		tmp.setX(positionOnBoard.getX() + 1);
		tmp.setY(positionOnBoard.getY() + 1);

		Board::setFieldUnderAttack(tmp, pieceTypeToColor(type), type);
	}


	//5. down
	if (positionOnBoard.getY() + 1 <= 7)
	{
		tmp.setX(positionOnBoard.getX());
		tmp.setY(positionOnBoard.getY() + 1);

		Board::setFieldUnderAttack(tmp, pieceTypeToColor(type), type);
	}

	//6. down  - left
	if (positionOnBoard.getX() - 1 >= 0 && positionOnBoard.getY() + 1 <= 7)
	{
		tmp.setX(positionOnBoard.getX() - 1);
		tmp.setY(positionOnBoard.getY() + 1);

		Board::setFieldUnderAttack(tmp, pieceTypeToColor(type), type);
	}

	//7. left
	if (positionOnBoard.getX() - 1 >= 0)
	{
		tmp.setX(positionOnBoard.getX() - 1);
		tmp.setY(positionOnBoard.getY());

		Board::setFieldUnderAttack(tmp, pieceTypeToColor(type), type);
	}

	//8. up  - left
	if (positionOnBoard.getX() - 1 >= 0 && positionOnBoard.getY() - 1 >= 0)
	{
		tmp.setX(positionOnBoard.getX() - 1);
		tmp.setY(positionOnBoard.getY() - 1);

		Board::setFieldUnderAttack(tmp, pieceTypeToColor(type), type);
	}



}

void King::findAllPossibleMoves()
{
	//try to move a king each possible combination that is on the board. If it finds another piece: if it's colors piece - dont add to possible moves, else do add.

	clearSetofCoords();
	Coordinates tmp = positionOnBoard;

	//1. up
	if (positionOnBoard.getY() - 1 >= 0)
	{
		tmp.setX(positionOnBoard.getX());
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

	//2. up  - right
	if (positionOnBoard.getX() + 1 <= 7 && positionOnBoard.getY() - 1 >= 0)
	{
		tmp.setX(positionOnBoard.getX() + 1);
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

	//3. right
	if (positionOnBoard.getX() + 1 <= 7)
	{
		tmp.setX(positionOnBoard.getX() + 1);
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
	}

	//4. down  - right
	if (positionOnBoard.getX() + 1 <= 7 && positionOnBoard.getY() + 1 <= 7)
	{
		tmp.setX(positionOnBoard.getX() + 1);
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


	//5. down
	if (positionOnBoard.getY() + 1 <= 7)
	{
		tmp.setX(positionOnBoard.getX());
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

	//6. down  - left
	if (positionOnBoard.getX() - 1 >= 0 && positionOnBoard.getY() + 1 <= 7)
	{
		tmp.setX(positionOnBoard.getX() - 1);
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

	//7. left
	if (positionOnBoard.getX() - 1 >= 0)
	{
		tmp.setX(positionOnBoard.getX() - 1);
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
	}

	//8. up  - left
	if (positionOnBoard.getX() - 1 >= 0 && positionOnBoard.getY() - 1 >= 0)
	{
		tmp.setX(positionOnBoard.getX() - 1);
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

}

int King::castle(Coordinates c)
{

	//check if c are the coordinates of the same color as the king
	//check if king and chosen rook was not moved arleady
	//check if there are no other pieces blocking movement of the king and the rook
	//check if king's destinated field is not under attack
	//if all those conditions are met - return a castle type:
	//1 - white left rook (white long castle)
	//2 - white right rook (white short castle)
	//3 - black left rook (black long castle)
	//4 - black right rook (black short castle)
	//return 0 otherwise


	Coordinates tmp1;
	Coordinates tmp2;
	Coordinates tmp3;

	if (firstMove)
	{
		//white
		if (pieceTypeToColor(type) == 0)
		{
			//left rook
			if (c.getX() == 0 && c.getY() == 7)
			{
				//check if rook on that field was arleady moved
				if (Piece::getPieceByCoords(c)->getType() == w_rook && Piece::getPieceByCoords(c)->getFirstMove() == true)
				{
					tmp1.setX(1);
					tmp1.setY(7);
					tmp2.setX(2);
					tmp2.setY(7);
					tmp3.setX(3);
					tmp3.setY(7);

					//check for obstacles
					if (Board::getPieceTypeOnGivenCoords(tmp1) == empty && Board::getPieceTypeOnGivenCoords(tmp2) == empty && Board::getPieceTypeOnGivenCoords(tmp3) == empty)
					{
						//check if desination field is under attack
						if (Board::getFieldUnderAttack(tmp2, 1) == 0)
						{
							return 1;
						}
					}
				}
			}

			//right rook
			if (c.getX() == 7 && c.getY() == 7)
			{
				//check if rook on that field was arleady moved
				if (Piece::getPieceByCoords(c)->getType() == w_rook && Piece::getPieceByCoords(c)->getFirstMove() == true)
				{
					tmp1.setX(5);
					tmp1.setY(7);
					tmp2.setX(6);
					tmp2.setY(7);

					//check for obstacles
					if (Board::getPieceTypeOnGivenCoords(tmp1) == empty && Board::getPieceTypeOnGivenCoords(tmp2) == empty)
					{
						//check if desination field is under attack
						if (Board::getFieldUnderAttack(tmp1, 1) == 0)
						{
							return 2;
						}
					}
				}
			}
		}


		//black
		if (pieceTypeToColor(type) == 1)
		{
			//left rook
			if (c.getX() == 0 && c.getY() == 0)
			{
				//check if rook on that field was arleady moved
				if (Piece::getPieceByCoords(c)->getType() == b_rook && Piece::getPieceByCoords(c)->getFirstMove() == true)
				{
					tmp1.setX(1);
					tmp1.setY(0);
					tmp2.setX(2);
					tmp2.setY(0);
					tmp3.setX(3);
					tmp3.setY(0);

					//check for obstacles
					if (Board::getPieceTypeOnGivenCoords(tmp1) == empty && Board::getPieceTypeOnGivenCoords(tmp2) == empty && Board::getPieceTypeOnGivenCoords(tmp3) == empty)
					{
						//check if desination field is under attack
						if (Board::getFieldUnderAttack(tmp2, 0) == 0)
						{
							return 3;
						}
					}
				}
			}

			//right rook
			if (c.getX() == 7 && c.getY() == 0)
			{
				//check if rook on that field was arleady moved
				if (Piece::getPieceByCoords(c)->getType() == b_rook && Piece::getPieceByCoords(c)->getFirstMove() == true)
				{
					tmp1.setX(5);
					tmp1.setY(0);
					tmp2.setX(6);
					tmp2.setY(0);

					//check for obstacles
					if (Board::getPieceTypeOnGivenCoords(tmp1) == empty && Board::getPieceTypeOnGivenCoords(tmp2) == empty)
					{
						//check if desination field is under attack
						if (Board::getFieldUnderAttack(tmp1, 0) == 0)
						{
							return 4;
						}
					}
				}
			}
		}


	}

	return 0;

}