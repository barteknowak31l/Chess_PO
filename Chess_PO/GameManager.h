#ifndef _GameManager
#define _GameManager

#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Pawn.h"

class GameManager
{
private:
	//GRAPHICS
	static int piecesPositions[];

	//GameObjects
	Board* board;
	Pawn pawns[8];



public:
	GameManager();
	~GameManager();

	void init();

	static void calculatePiecePositions(sf::RenderTarget&);
	static int* getPiecesPositions();


};
#endif


