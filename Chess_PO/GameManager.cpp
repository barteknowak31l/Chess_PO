#include "include\GameManager.h"


GameManager* GameManager::instance;


GameManager::GameManager()
{
	if (instance == NULL)
	{
		instance = this;
	}
	else {
		delete this;
	}

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
	//pawns[0] = new Pawn(0, 1, 1);
	//pawns[1] = new Pawn(1, 1, 1);
	//pawns[2] = new Pawn(2, 1, 1);
	//pawns[3] = new Pawn(3, 1, 1);
	//pawns[4] = new Pawn(4, 1, 1);
	//pawns[5] = new Pawn(5, 1, 1);
	//pawns[6] = new Pawn(6, 1, 1);
	//pawns[7] = new Pawn(7, 1, 1);

}



//getters
Board& GameManager::getBoard()
{
	return *board;
}