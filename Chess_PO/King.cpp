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
	if (positionOnBoard.getX() == c.getX() && positionOnBoard.getY() - c.getY() == 1 && Board::getFieldUnderAttack(c, !pieceTypeToColor(type)) == 0)
	{
		std::cout << "king up move\n";
		//if (Board::getPieceTypeOnGivenCoords(c) != empty)
			//Board::capture(c);

		return true;
	}

	//2. up  - right
	if (c.getX() - positionOnBoard.getX() == 1 && positionOnBoard.getY() - c.getY() == 1 && Board::getFieldUnderAttack(c, !pieceTypeToColor(type)) == 0)
	{
		std::cout << "king up-right move\n";
		//if (Board::getPieceTypeOnGivenCoords(c) != empty)
			//Board::capture(c);

		return true;
	}

	//3. right
	if (c.getX() - positionOnBoard.getX() == 1 && positionOnBoard.getY() == c.getY() && Board::getFieldUnderAttack(c, !pieceTypeToColor(type)) == 0)
	{
		std::cout << "king right move\n";
		//if (Board::getPieceTypeOnGivenCoords(c) != empty)
			//Board::capture(c);

		return true;
	}

	//4. down  - right
	if (c.getX() - positionOnBoard.getX() == 1 && c.getY() - positionOnBoard.getY() == 1 && Board::getFieldUnderAttack(c, !pieceTypeToColor(type)) == 0)
	{
		std::cout << "king down-right move\n";
		//if (Board::getPieceTypeOnGivenCoords(c) != empty)
			//Board::capture(c);

		return true;
	}

	//5. down
	if (c.getX() == positionOnBoard.getX() && c.getY() - positionOnBoard.getY() == 1 && Board::getFieldUnderAttack(c, !pieceTypeToColor(type)) == 0)
	{
		std::cout << "king down move\n";
		//if (Board::getPieceTypeOnGivenCoords(c) != empty)
			//Board::capture(c);

		return true;
	}

	//6. down  - left
	if (positionOnBoard.getX() - c.getX() == 1 && c.getY() - positionOnBoard.getY() == 1 && Board::getFieldUnderAttack(c, !pieceTypeToColor(type)) == 0)
	{
		std::cout << "king down-left move\n";
		//if (Board::getPieceTypeOnGivenCoords(c) != empty)
			//Board::capture(c);

		return true;
	}

	//7. left
	if (positionOnBoard.getX() - c.getX() == 1 && c.getY() == positionOnBoard.getY() == 1 && Board::getFieldUnderAttack(c, !pieceTypeToColor(type)) == 0)
	{
		std::cout << "king left move\n";
		//if (Board::getPieceTypeOnGivenCoords(c) != empty)
			//Board::capture(c);

		return true;
	}

	//8. up  - left
	if (positionOnBoard.getX() - c.getX() == 1 && positionOnBoard.getY() - c.getY() == 1 && Board::getFieldUnderAttack(c, !pieceTypeToColor(type)) == 0)
	{
		std::cout << "king up-left move\n";
		//if (Board::getPieceTypeOnGivenCoords(c) != empty)
			//Board::capture(c);

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