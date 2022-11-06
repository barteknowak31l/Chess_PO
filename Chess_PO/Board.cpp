#include "Board.h"
#include "algorithm"
#include <iostream>
#include "Pawn.h"

void Board::init()
{
	_b[0][0] = b_rook;
	_b[0][1] = b_knight;
	_b[0][2] = b_bishop;
	_b[0][3] = b_queen;
	_b[0][4] = b_king;
	_b[0][5] = b_bishop;
	_b[0][6] = b_knight;
	_b[0][7] = b_rook;

	_b[0][0] = b_pawn;		
	_b[1][1] = b_pawn;		
	_b[2][2] = b_pawn;		
	_b[3][3] = b_pawn;		
	_b[4][4] = b_pawn;		
	_b[5][5] = b_pawn;		
	_b[6][6] = b_pawn;		
	_b[7][7] = b_pawn;		


	_b[7][0] = w_rook;
	_b[7][1] = w_knight;
	_b[7][2] = w_bishop;
	_b[7][3] = w_queen;
	_b[7][4] = w_king;
	_b[7][5] = w_bishop;
	_b[7][6] = w_knight;
	_b[7][7] = w_rook;

	_b[6][0] = w_pawn;
	_b[6][1] = w_pawn;
	_b[6][2] = w_pawn;
	_b[6][3] = w_pawn;
	_b[6][4] = w_pawn;
	_b[6][5] = w_pawn;
	_b[6][6] = w_pawn;
	_b[6][7] = w_pawn;

}

void Board::drawBoard(sf::RenderTarget& target)
{
	//find proper size of field
	float x = target.getSize().x *0.75;
	float y = target.getSize().y;
	float size = std::min(x, y)/8;



	for (int i = 0; i < 32; i++)
	{
		fields[i].setSize(sf::Vector2f(size, size));
		fields[i].setFillColor(sf::Color::White);
	}
	for (int i = 32; i < 64; i++)
	{
		fields[i].setSize(sf::Vector2f(size , size));
		fields[i].setFillColor(sf::Color(130,118,111,255));
	}

	x = 0;
	y = 0;

	for (int i = 0; i < 8; i++)
	{
		x = 0;
		for (int j = 0; j < 8; j++)
		{
			if (i % 2 == j % 2) // paint white
			{
				fields[i + j].setPosition(sf::Vector2f(x, y));


				target.draw(fields[i + j]);
				x += size;
			}
			else	//paint black
			{
				fields[i + j + 32].setPosition(sf::Vector2f(x, y));
				target.draw(fields[i + j + 32]);
				x += size;
			}

		}
		y += size;
	}


}