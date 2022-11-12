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
	enPassantable = 0;

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


	if (promote(c))
	{
		std::cout << "PROMOCJA\n";
		Board::pawnPromotion(positionOnBoard, c);
		return false;
	}

	int en = enPassant(c);
	if (en > 0)
	{
		Coordinates tmp = positionOnBoard;
		std::cout << "EN PASSANT\n";
		switch (en)
		{
		case 1:
		{
			tmp.setX(positionOnBoard.getX() + 1);
			Board::enPassant(this, c, tmp);
			break;
		}
		case 2:
		{
			tmp.setX(positionOnBoard.getX() - 1);
			Board::enPassant(this, c, tmp);
			break;
		}
		}

	}


	if (type == b_pawn)
	{
		if (firstMove)
		{

			//check +2 move
			if (c.getY() - positionOnBoard.getY() == 2 && c.getX() - positionOnBoard.getX() == 0 && Board::getPieceTypeOnGivenCoords(c) == empty)
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
						//Board::capture(c);
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


	if (type == w_pawn)
	{
		if (firstMove)
		{

			//check +2 move
			if (positionOnBoard.getY() - c.getY() == 2 && c.getX() - positionOnBoard.getX() == 0 && Board::getPieceTypeOnGivenCoords(c) == empty)
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

	

	std::cout << "INCORRECT PAWN MOVE :( enpassantable: "<<enPassantable<<std::endl;
	return false;
}

bool Pawn::promote(Coordinates c)
{
	if (type == b_pawn)
	{
		if (c.getY() - positionOnBoard.getY() == 1 && c.getX() - positionOnBoard.getX() == 0 && Board::getPieceTypeOnGivenCoords(c) == empty)
		{
			if (c.getY() == 7)
			{
				return true;
			}
		}
	}

	if (type == w_pawn)
	{
		if (positionOnBoard.getY() - c.getY() == 1 && c.getX() - positionOnBoard.getX() == 0 && Board::getPieceTypeOnGivenCoords(c) == empty)
		{
			if (c.getY() == 0)
			{
				return true;
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
			if (Board::getPieceTypeOnGivenCoords(tmp) == empty)
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
			tmp.setY(positionOnBoard.getY() - 2);
			if (Board::getPieceTypeOnGivenCoords(tmp) == empty)
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
	if (type == b_pawn)
	{
		//find out on which we try to en passant
		//to right
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
					//EN PASSANT
					return 1;
				}
			}
		}
		//to left
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
					//EN PASSANT
					return 2;
				}

			}
		}

	}

	if (type == w_pawn)
	{
		//find out on which we try to en passant
		//to right
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
					//EN PASSANT
					return 1;
				}
			}
		}
		//to left
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
					//EN PASSANT
					return 2;
				}

			}
		}

	}



	return 0;
}


//getters
int Pawn::getEnpassantable()
{
	return enPassantable;
}