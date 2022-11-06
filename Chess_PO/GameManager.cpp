#include "GameManager.h"

int GameManager::piecesPositions[64];

GameManager::GameManager()
{
	return;
}
GameManager::~GameManager()
{
	return;
}

void GameManager::init()
{
	//init a board
	board = new Board;
	board->init();

	//init pieces
	pawns[0] = Pawn(0, 75, 1, 1);
	pawns[1] = Pawn(75, 75, 1, 2);
	pawns[2] = Pawn(150, 75, 1, 3);
	pawns[3] = Pawn(225, 75, 1, 4);
	pawns[4] = Pawn(300, 75, 1, 5);
	pawns[5] = Pawn(375, 75, 1, 6);
	pawns[6] = Pawn(450, 75, 1, 7);
	pawns[7] = Pawn(525, 75, 1, 8);

}

void GameManager::calculatePiecePositions(sf::RenderTarget& target)
{
	//find proper size of field
	float x = target.getSize().x * 0.75;
	float y = target.getSize().y;
	float size = std::min(x, y) / 8;

	//move origin of a piece to the center of a field

}


int* GameManager::getPiecesPositions()
{
	return piecesPositions;
}