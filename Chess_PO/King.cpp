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

	firstMove = true;

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

	//try castle
	int cas = castle(c);

	if (cas> 0 && firstMove && Board::check_white== 0 && Board::check_black ==0)
	{
		firstMove = false;
		Board::castle(this, c, cas);
		return false;
	}


	int color1 = pieceTypeToColor(Board::getPieceTypeOnGivenCoords(c));
	int color2 = pieceTypeToColor(type);
	if (color1 == color2)
	{
		std::cout << "krol probuje zbic swoja figure\n";
		return false;
	}

	//1. up
	if (positionOnBoard.getX() == c.getX() && positionOnBoard.getY() - c.getY() == 1 && Board::getFieldUnderAttack(c, !pieceTypeToColor(type)) == 0)
	{
		std::cout << "king up move\n";
		//if (Board::getPieceTypeOnGivenCoords(c) != empty)
			//Board::capture(c);
		if (firstMove)
		{
			firstMove = false;
		}
		return true;
	}

	//2. up  - right
	if (c.getX() - positionOnBoard.getX() == 1 && positionOnBoard.getY() - c.getY() == 1 && Board::getFieldUnderAttack(c, !pieceTypeToColor(type)) == 0)
	{
		std::cout << "king up-right move\n";
		//if (Board::getPieceTypeOnGivenCoords(c) != empty)
			//Board::capture(c);

		if (firstMove)
		{
			firstMove = false;
		}
		return true;
	}

	//3. right
	if (c.getX() - positionOnBoard.getX() == 1 && positionOnBoard.getY() == c.getY() && Board::getFieldUnderAttack(c, !pieceTypeToColor(type)) == 0)
	{
		std::cout << "king right move\n";
		//if (Board::getPieceTypeOnGivenCoords(c) != empty)
			//Board::capture(c);

		if (firstMove)
		{
			firstMove = false;
		}
		return true;
	}

	//4. down  - right
	if (c.getX() - positionOnBoard.getX() == 1 && c.getY() - positionOnBoard.getY() == 1 && Board::getFieldUnderAttack(c, !pieceTypeToColor(type)) == 0)
	{
		std::cout << "king down-right move\n";
		//if (Board::getPieceTypeOnGivenCoords(c) != empty)
			//Board::capture(c);
		if (firstMove)
		{
			firstMove = false;
		}

		return true;
	}

	//5. down
	if (c.getX() == positionOnBoard.getX() && c.getY() - positionOnBoard.getY() == 1 && Board::getFieldUnderAttack(c, !pieceTypeToColor(type)) == 0)
	{
		std::cout << "king down move\n";
		//if (Board::getPieceTypeOnGivenCoords(c) != empty)
			//Board::capture(c);
		if (firstMove)
		{
			firstMove = false;
		}

		return true;
	}

	//6. down  - left
	if (positionOnBoard.getX() - c.getX() == 1 && c.getY() - positionOnBoard.getY() == 1 && Board::getFieldUnderAttack(c, !pieceTypeToColor(type)) == 0)
	{
		std::cout << "king down-left move\n";
		//if (Board::getPieceTypeOnGivenCoords(c) != empty)
			//Board::capture(c);
		if (firstMove)
		{
			firstMove = false;
		}

		return true;
	}

	//7. left
	if (positionOnBoard.getX() - c.getX() == 1 && c.getY() == positionOnBoard.getY() == 1 && Board::getFieldUnderAttack(c, !pieceTypeToColor(type)) == 0)
	{
		std::cout << "king left move\n";
		//if (Board::getPieceTypeOnGivenCoords(c) != empty)
			//Board::capture(c);

		if (firstMove)
		{
			firstMove = false;
		}

		return true;
	}

	//8. up  - left
	if (positionOnBoard.getX() - c.getX() == 1 && positionOnBoard.getY() - c.getY() == 1 && Board::getFieldUnderAttack(c, !pieceTypeToColor(type)) == 0)
	{
		std::cout << "king up-left move\n";
		//if (Board::getPieceTypeOnGivenCoords(c) != empty)
			//Board::capture(c);

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


	//8 kombinacji + sprawdzenie czy nie wychodzimy poza szachownice
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
	//sprawdz czy c to koordynaty wiezy naszego koloru, sprawdz czy wieza nie byla ruszana, sprawdz czy na drodze nic nie stoi, sprawdz czy finalowe pole jest atakowane

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