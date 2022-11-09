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
	float x = target.getSize().x * 0.75;
	float y = target.getSize().y;
	float size = std::min(x, y) / 8;


	//set fields positions and size
	x = 0;
	y = 0;
	for(int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			fields[i][j].setSize(sf::Vector2f(size, size));
			fields[i][j].setPosition(sf::Vector2f(x, y));
			x += size;
		}
		x = 0;
		y += size;
	}


	//set proper colors
	x = 0;
	y = 0;
	int col = 1;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (col)
			{
				fields[i][j].setFillColor(sf::Color::White);
			}
			else
			{
				fields[i][j].setFillColor(sf::Color::Black);
			}
			col = !col;
			target.draw(fields[i][j]);
		}
		col = !col;


	}
}

sf::Vector2f Board::boardToScreenPos(int x, int y)
{
	return fields[x][y].getPosition();
}

void Board::calculatePiecesPositions()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			piecesPositions[i][j] = sf::Vector2f(fields[i][j].getPosition().y + fields[i][j].getSize().y/2,
												fields[i][j].getPosition().x + fields[i][j].getSize().x/2);

		}
	}
}






//getters
sf::Vector2f Board::getPiecesPositions(int x, int y)
{
	std::cout << "getPiecesPositions " << x << " " << y << " results: " << piecesPositions[x][y].x<<" "<< piecesPositions[x][y].y<< std::endl;
	return piecesPositions[x][y];
}