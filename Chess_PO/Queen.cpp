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

	std::cout << "QueenConstructor\n";
}

Queen::~Queen()
{
	std::cout << "QueenDestructor\n";
	return;
}

bool Queen::isMoveLegal(Coordinates c)
{
	return diagonalMove(c) || horizontalMove(c);
}


bool Queen::diagonalMove(Coordinates c)
{
	//sprawdz czy na polu docelowym nie ma figury tego samego koloru
	//sprawdz czy nowe pole spelnia warunek abs(dx) == abs(dy) - ruch na ukos
	//sprawdz czy nie ma przeszkod


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
				std::cout << tmp.getX() << " " << tmp.getY() << std::endl;

				if (Board::getPieceTypeOnGivenCoords(tmp) != empty)
				{
					std::cout << "queen up-right collision\n";
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
					std::cout << "queen down-right collision\n";
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
					std::cout << "queen down-left collision\n";
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
					std::cout << "queen up-left collision\n";
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

bool Queen::horizontalMove(Coordinates c)
{
	//ruch w pionie/poziomie -> rozne x i te same y i analogicznie
	//nie moze miec nic na drodze
	//jesli powyzsze warunki sa spelnione to
	//jesli na c cos stoi - bicie, else zwykly rych

	//check if vertical or horizontal move

	if ((positionOnBoard.getX() != c.getX() && positionOnBoard.getY() == c.getY()) || (positionOnBoard.getY() != c.getY() && positionOnBoard.getX() == c.getX()))
	{

		//check for obstacles
		Coordinates tmp;
		//horizontal
		if (c.getX() - positionOnBoard.getX() != 0)
		{
			tmp.setY(positionOnBoard.getY());

			int dir = c.getX() - positionOnBoard.getX(); // < 0 means piece moves left

			if (dir > 0)
			{
				//piece moves right
				for (int i = positionOnBoard.getX(); i < c.getX(); i++)
				{
					std::cout << i << std::endl;
					tmp.setX(i);
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
					std::cout << i << std::endl;
					tmp.setX(i);
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

			int dir = c.getY() - positionOnBoard.getY(); // < 0 means piece moves up

			if (dir > 0)
			{
				//piece moves down
				for (int i = positionOnBoard.getY(); i < c.getY(); i++)
				{
					tmp.setY(i);
					std::cout << i << std::endl;
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
					std::cout << i << std::endl;
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
			//sprawdz czy bijemy figure przeciwnego koloru
			int color1 = pieceTypeToColor(Board::getPieceTypeOnGivenCoords(positionOnBoard));
			int color2 = pieceTypeToColor(Board::getPieceTypeOnGivenCoords(c));
			//capture
			if (color1 != color2)
			{
				std::cout << "Queen captured a piece!\n";
				Board::capture(c);

			}
			else
			{
				std::cout << "trying to capture your own piece\n";
				return false;
			}
		}


		//correct move (not capture)
		return true;


	}



	return false;
}

void Queen::setFieldsUnderAttack()
{
	;
}