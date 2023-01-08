#include "include\Pawn.h"
#include <iostream>
#include <cstdlib>
#include "include\Board.h"

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
	enPassantable = 0;
}

Pawn::~Pawn()
{
	return;
}

bool Pawn::isMoveLegal(Coordinates c)
{

	//pawn can move only upwards and only if nothing is blocking its way
	//first move can be +2 move
	//it can capture diagonally within one square in front of it 
	//special move - enPassant - can capture a pawn that last move was +2 move by capturing a field behind that pawn
	//special move - promotion - if a pawn reaches last field on opposite side of board, it turns into a queen



	//check if pawn should promote
	if (promote(c))
	{
		Board::pawnPromotion(positionOnBoard, c);
		return false;
	}

	//check if a pawn should perform enPassant
	int en = enPassant(c);
	if (en > 0)
	{
		Coordinates tmp = positionOnBoard;
		switch (en)
		{
		case 1:	//enPassant to the right
		{
			tmp.setX(positionOnBoard.getX() + 1);
			Board::enPassant(this, c, tmp);
			break;
		}
		case 2: //enPassant to the left
		{
			tmp.setX(positionOnBoard.getX() - 1);
			Board::enPassant(this, c, tmp);
			break;
		}
		}

	}

	//try to move if its black pawn
	if (type == b_pawn)
	{
		//if its first move of a pawn, additionpal +2 move should be checked
		if (firstMove)
		{

			//check +2 move
			Coordinates cc;
			cc.setX(c.getX());
			cc.setY(c.getY()-1);
			if (c.getY() - positionOnBoard.getY() == 2 && c.getX() - positionOnBoard.getX() == 0 && Board::getPieceTypeOnGivenCoords(c) == empty && Board::getPieceTypeOnGivenCoords(cc) == empty)
			{
				firstMove = false;
				enPassantable = 1;
				return true;
			}
			//check +1 move
			if (c.getY() - positionOnBoard.getY() == 1 && c.getX() - positionOnBoard.getX() == 0 && Board::getPieceTypeOnGivenCoords(c) == empty)
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
						return true;
					}
				}
			}
		}
		else
		{
			//check +1 move
			if (c.getY() - positionOnBoard.getY() == 1 && c.getX() - positionOnBoard.getX() == 0 && Board::getPieceTypeOnGivenCoords(c) == empty)
			{
				if (enPassantable == 1)
				{
					enPassantable = 0;
				}
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
						if (enPassantable == 1)
						{
							enPassantable = 0;
						}
						return true;
					}
				}
			}
		}
	}


	//same logic for white pawn
	if (type == w_pawn)
	{
		if (firstMove)
		{

			//check +2 move
			Coordinates cc;
			cc.setX(c.getX());
			cc.setY(c.getY() + 1);
			if (positionOnBoard.getY() - c.getY() == 2 && c.getX() - positionOnBoard.getX() == 0 && Board::getPieceTypeOnGivenCoords(c) == empty && Board::getPieceTypeOnGivenCoords(cc) == empty)
			{
				firstMove = false;
				enPassantable = 1;
				return true;
			}
			//check +1 move
			if (positionOnBoard.getY() - c.getY() == 1 && c.getX() - positionOnBoard.getX() == 0 && Board::getPieceTypeOnGivenCoords(c) == empty)
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
						//Board::capture(c);
						return true;
					}
				}
			}
		}
		else
		{
			//check +1 move
			if (positionOnBoard.getY() - c.getY() == 1 && c.getX() - positionOnBoard.getX() == 0 && Board::getPieceTypeOnGivenCoords(c) == empty)
			{
				if (enPassantable == 1)
				{
					enPassantable = 0;
				}
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
						if (enPassantable == 1)
						{
							enPassantable = 0;
						}
						return true;
					}
				}
			}
		}
	}

	

	//if all test have failed - move is incorrect 
	return false;
}

bool Pawn::promote(Coordinates c)
{
	//logic for black panw
	if (type == b_pawn)
	{
		//if a pawn moved to last field and that field is empty
		if (c.getY() - positionOnBoard.getY() == 1 && c.getX() - positionOnBoard.getX() == 0 && Board::getPieceTypeOnGivenCoords(c) == empty)
		{
			if (c.getY() == 7)
			{
				return true;
			}
		}
		//check capture - can move to last field by capturing an enemy piece
		if (c.getY() - positionOnBoard.getY() == 1 && abs(c.getX() - positionOnBoard.getX()) == 1)
		{
			if (Board::getPieceTypeOnGivenCoords(c) != empty)
			{
				int color1 = pieceTypeToColor(Board::getPieceTypeOnGivenCoords(positionOnBoard));
				int color2 = pieceTypeToColor(Board::getPieceTypeOnGivenCoords(c));
				if (color1 != color2)
				{
					if (c.getY() == 7)
					{
						return true;
					}
				}
			}
		}
	}

	//same logic for white pawns
	if (type == w_pawn)
	{
		if (positionOnBoard.getY() - c.getY() == 1 && c.getX() - positionOnBoard.getX() == 0 && Board::getPieceTypeOnGivenCoords(c) == empty)
		{
			if (c.getY() == 0)
			{
				return true;
			}
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
					if (c.getY() == 0)
					{
						return true;
					}
				}
			}
		}
	}

	return false;

}

void Pawn::findFieldsUnderAttack()
{
	

	Coordinates tmp = positionOnBoard;
	
	if (capturedInSimulation)
	{
		return;
	}

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

void Pawn::findAllPossibleMoves()
{
	clearSetofCoords();

	Coordinates tmp;

	//white
	if (type == w_pawn)
	{
		//left attack
		if (positionOnBoard.getX() - 1 >= 0 && positionOnBoard.getY() - 1 >= 0)
		{
			tmp.setX(positionOnBoard.getX() - 1);
			tmp.setY(positionOnBoard.getY() - 1);
			
			if(Board::getPieceTypeOnGivenCoords(tmp) != empty && pieceTypeToColor(Board::getPieceTypeOnGivenCoords(tmp)) == 1)
				addCoordsToSet(tmp);
		}

		//right attack
		if (positionOnBoard.getX() + 1 <= 7 && positionOnBoard.getY() - 1 >= 0)
		{
			tmp.setX(positionOnBoard.getX() + 1);
			tmp.setY(positionOnBoard.getY() - 1);

			if (Board::getPieceTypeOnGivenCoords(tmp) != empty && pieceTypeToColor(Board::getPieceTypeOnGivenCoords(tmp)) == 1)
				addCoordsToSet(tmp);
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
			if (Board::getPieceTypeOnGivenCoords(tmp) != empty && pieceTypeToColor(Board::getPieceTypeOnGivenCoords(tmp)) == 0)
				addCoordsToSet(tmp);
		}

		//right attack
		if (positionOnBoard.getX() + 1 <= 7 && positionOnBoard.getY() + 1 <= 7)
		{
			tmp.setX(positionOnBoard.getX() + 1);
			tmp.setY(positionOnBoard.getY() + 1);
			if (Board::getPieceTypeOnGivenCoords(tmp) != empty && pieceTypeToColor(Board::getPieceTypeOnGivenCoords(tmp)) == 1)
				addCoordsToSet(tmp);
		}

	}

	addRemainingPossibleMoves();

}

void Pawn::addRemainingPossibleMoves()
{
	Coordinates tmp = positionOnBoard;


	if (type == b_pawn)
	{
		if (firstMove)
		{

			//check +2 move
			tmp.setY(positionOnBoard.getY() + 2);
			Coordinates cc;
			cc.setX(tmp.getX());
			cc.setY(tmp.getY() - 1);
			if (Board::getPieceTypeOnGivenCoords(tmp) == empty && Board::getPieceTypeOnGivenCoords(cc) == empty)
			{
				addCoordsToSet(tmp);
			}

		}

		//check +1 move
		tmp.setY(positionOnBoard.getY() + 1);
		if (Board::getPieceTypeOnGivenCoords(tmp) == empty)
		{
			addCoordsToSet(tmp);
		}

		
	}


	if (type == w_pawn)
	{
		if (firstMove)
		{

			//check +2 move
			Coordinates cc;
			cc.setX(tmp.getX());
			cc.setY(tmp.getY() + 1);
			tmp.setY(positionOnBoard.getY() - 2);
			if (Board::getPieceTypeOnGivenCoords(tmp) == empty && Board::getPieceTypeOnGivenCoords(cc) == empty)
			{
				addCoordsToSet(tmp);
			}

		}

		//check +1 move
		tmp.setY(positionOnBoard.getY() - 1);
		if (Board::getPieceTypeOnGivenCoords(tmp) == empty)
		{
			addCoordsToSet(tmp);
		}
	}
}

int Pawn::enPassant(Coordinates c)
{
	Coordinates tmp;

	//logic for black pawns
	if (type == b_pawn)
	{
		//find out on which side we try to en passant
		//to the right
		if (c.getX() - positionOnBoard.getX() == 1 && c.getY() - positionOnBoard.getY() == 1)
		{
			//check if theres w_pawn on the right
			tmp.setX(positionOnBoard.getX() + 1);
			tmp.setY(positionOnBoard.getY());
			if (Board::getPieceTypeOnGivenCoords(tmp) == w_pawn)
			{
				//check if that w_pawn is enPassantable
				if (((Pawn*)getPieceByCoords(tmp))->getEnpassantable() == 1)
				{
					//EN PASSANT TO RIGHT
					return 1;
				}
			}
		}
		//to the left
		if (positionOnBoard.getX() - c.getX() == 1 && c.getY() - positionOnBoard.getY() == 1)
		{
			//check if theres w_pawn on the left
			tmp.setX(positionOnBoard.getX() - 1);
			tmp.setY(positionOnBoard.getY());
			if (Board::getPieceTypeOnGivenCoords(tmp) == w_pawn)
			{
				//check if that w_pawn is enPassantable
				if (((Pawn*)getPieceByCoords(tmp))->getEnpassantable() == 1)
				{
					//EN PASSANT TO THE
					return 2;
				}

			}
		}

	}

	//same logic for white pawns
	if (type == w_pawn)
	{
		//find out on which we try to en passant
		//to the right
		if (c.getX() - positionOnBoard.getX() == 1 && positionOnBoard.getY() - c.getY() == 1)
		{
			//check if theres b_pawn on the right
			tmp.setX(positionOnBoard.getX() + 1);
			tmp.setY(positionOnBoard.getY());
			if (Board::getPieceTypeOnGivenCoords(tmp) == b_pawn)
			{
				//check if that b_pawn is enPassantable
				if (((Pawn*)getPieceByCoords(tmp))->getEnpassantable() == 1)
				{
					//EN PASSANT TO THE RIGHT
					return 1;
				}
			}
		}
		//to the left
		if (positionOnBoard.getX() - c.getX() == 1 && positionOnBoard.getY() - c.getY() == 1)
		{
			//check if theres b_pawn on the left
			tmp.setX(positionOnBoard.getX() - 1);
			tmp.setY(positionOnBoard.getY());
			if (Board::getPieceTypeOnGivenCoords(tmp) == b_pawn)
			{
				//check if that b_pawn is enPassantable
				if (((Pawn*)getPieceByCoords(tmp))->getEnpassantable() == 1)
				{
					//EN PASSANT TO THE LEFT
					return 2;
				}

			}
		}

	}

	//tests have failed - player did not try enPassant or its not legal

	return 0;
}

//getters
int Pawn::getEnpassantable()
{
	return enPassantable;
}