#ifndef _GameManager
#define _GameManager

#include <SFML/Graphics.hpp>
#include "include\Board.h"
#include "include\Pawn.h"


class GameManager
{
private:


	//GameObjects
	Board* board;
	Pawn* pawns[8];



public:
	static GameManager* instance;
	GameManager();
	~GameManager();
	void init();

	//getters
	Board& getBoard();

};
#endif


