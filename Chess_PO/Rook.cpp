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

}

Rook::~Rook()
{
	std::cout << "RookDestructor\n";
	return;
}

bool Rook::isMoveLegal(Coordinates c)
{
	//ruch w pionie/poziomie -> rozne x i te same y i analogicznie
	//nie moze miec nic na drodze
	//jesli powyzsze warunki sa spelnione to
	//jesli na c cos stoi - bicie, else zwykly rych

	//check if vertical or horizontal move

	if ( (positionOnBoard.getX() != c.getX() && positionOnBoard.getY() == c.getY()) || (positionOnBoard.getY() != c.getY() && positionOnBoard.getX() == c.getX()))
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
				std::cout << "Rook captured a piece!\n";
				//Board::capture(c);
				
			}
			else
			{
				std::cout << "trying to capture your own piece\n";
				return false;
			}
		}


		//correct move (not capture)

		//check for capture
		//for now, considering all moves the same 
		return true;


	}



	return false;
}

void Rook::findFieldsUnderAttack()
{
	//sprawdz kazdy kierunek az do wyjscia poza plansza lub napotkania przeszkody i ustaw wszystkie mijane pola na under_attack, wlacznie z polem przeszkody

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