#ifndef _Pawn
#define _Pawn

#include "Piece.h"

class Board;

class Pawn : Piece
{
private:
	bool firstMove;

	public:
	sf::Texture texture;
	Pawn();
	Pawn(int,int,int,int);
	~Pawn();

	bool isMoveLegal(Coordinates);
	void findFieldsUnderAttack();

};

#endif
