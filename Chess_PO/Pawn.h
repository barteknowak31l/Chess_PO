#ifndef _Pawn
#define _Pawn

#include "Piece.h"

class Board;

class Pawn : Piece
{
private:
	bool firstMove;
	void addRemainingPossibleMoves();

	bool promote(Coordinates);

	int enPassantable;
	int enPassant(Coordinates);

	public:
	sf::Texture texture;
	Pawn();
	Pawn(int,int,int,int);
	~Pawn();

	bool isMoveLegal(Coordinates);
	void findFieldsUnderAttack();
	void findAllPossibleMoves();


	//getter
	int getEnpassantable();


};

#endif
