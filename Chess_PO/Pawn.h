#ifndef _Pawn
#define _Pawn

#include "Piece.h"

class Board;

class Pawn : Piece
{
private:

	//utility - adds moving upwards to possible moves set
	void addRemainingPossibleMoves();

	//check if pawn should promote to a queen
	bool promote(Coordinates);

	//flag to check if this pawn can be captured by enPassanst move
	int enPassantable;

	//determines if enPassant move is legal - returns 1 if player tried enPassant capture to right side, 2 if to left side, 0 if move is not legal
	int enPassant(Coordinates);

	//texture of piece loaded from file
	sf::Texture texture;

	public:
	
	Pawn();
	
	//params: coord x, coord y, color, type 
	Pawn(int,int,int,int);
	~Pawn();

	//overrided virtual functions

	//returns true if move is legal, false if not or if any special move should be performed
	bool isMoveLegal(Coordinates);
	void findFieldsUnderAttack();
	void findAllPossibleMoves();


	//getter
	int getEnpassantable();


};

#endif
