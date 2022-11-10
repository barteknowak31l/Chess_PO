#include "Bishop.h"
#include <iostream>
#include "Board.h"
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
	std::cout << "BishopConstructor\n";
}

Bishop::~Bishop()
{
	std::cout << "BishopDestructor\n";
	return;
}

bool Bishop::isMoveLegal(Coordinates c)
{
	//sprawdz czy na polu docelowym nie ma figury tego samego koloru
	//sprawdz czy nowe pole spelnia warunek abs(dx) == abs(dy) - ruch na ukos
	//sprawdz czy nie ma przeszkod
	std::cout << "POSITION ON BOARD: " << positionOnBoard.getX() << " " << positionOnBoard.getY() << std::endl;
	std::cout << "c: " << c.getX() << " " << c.getY() << std::endl;


	int color1 = pieceTypeToColor(Board::getPieceTypeOnGivenCoords(c));
	int color2 = pieceTypeToColor(type);

	if (color1 == color2)
	{
		std::cout << "niepoprawny ruch albo proba zbicia wlasniej figury\n";
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
				//std::cout << i << std::endl;
				tmp.setX(tmp.getX() + 1);
				tmp.setY(tmp.getY() - 1);
				std::cout << tmp.getX() << " " << tmp.getY()<< std::endl;

				if (Board::getPieceTypeOnGivenCoords(tmp) != empty)
				{
					std::cout << "bishop up-right collision\n";
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
				std::cout << tmp.getX() << " " << tmp.getY() << std::endl;
				if (Board::getPieceTypeOnGivenCoords(tmp) != empty)
				{
					std::cout << "bishop down-right collision\n";
					return false;
				}

			}
		}

		//down left
		if (positionOnBoard.getX() > c.getX() && c.getY() > positionOnBoard.getY())
		{
			for (int i = 1; i < c.getY() - positionOnBoard.getY(); i++)
			{
				//std::cout << i << std::endl;
				tmp.setX(tmp.getX() - 1);
				tmp.setY(tmp.getY() + 1);
				std::cout << tmp.getX() << " " << tmp.getY() << std::endl;

				if (Board::getPieceTypeOnGivenCoords(tmp) != empty)
				{
					std::cout << "bishop down-left collision\n";
					return false;
				}

			}
		}

		//up left
		if (positionOnBoard.getX() > c.getX() && positionOnBoard.getY() > c.getY())
		{
			for (int i = 1; i < positionOnBoard.getY() - c.getY(); i++)
			{
				//std::cout << i << std::endl;
				tmp.setX(tmp.getX() - 1);
				tmp.setY(tmp.getY() - 1);
				std::cout << tmp.getX() << " " << tmp.getY() << std::endl;

				if (Board::getPieceTypeOnGivenCoords(tmp) != empty)
				{
					std::cout << "bishop up-left collision\n";
					return false;
				}

			}
		}

		//capture
		if (Board::getPieceTypeOnGivenCoords(c) != empty)
			Board::capture(c);

		return true;
	}


	return false;
}

void Bishop::setFieldsUnderAttack()
{
	//sprawdzaj w 4 kierunkach az do wyjscia z planszy albo napotkania przeszkody
	Coordinates tmp = positionOnBoard;
	int i = 1;

	//up right
	while (positionOnBoard.getX() + i <= 7 && positionOnBoard.getY() - i >= 0)
	{
		tmp.setX(positionOnBoard.getX() + i);
		tmp.setY(positionOnBoard.getY() - i);

		Board::setFieldUnderAttack(tmp, pieceTypeToColor(type));

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

		Board::setFieldUnderAttack(tmp, pieceTypeToColor(type));

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

		Board::setFieldUnderAttack(tmp, pieceTypeToColor(type));

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

		Board::setFieldUnderAttack(tmp, pieceTypeToColor(type));

		i++;

		if (Board::getPieceTypeOnGivenCoords(tmp) != empty)
			break;
	}



}

