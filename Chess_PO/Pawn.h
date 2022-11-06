#ifndef _Pawn
#define _Pawn

#include "Piece.h"

class Pawn : Piece
{
	public:
	
	sf::Texture texture;
	Pawn();
	Pawn(int,int,int,int);
	~Pawn();
	void move(Coordinates);

};

#endif
