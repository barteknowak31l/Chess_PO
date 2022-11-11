#ifndef _Rook
#define _Rook
#include "Piece.h"

class Rook : Piece
{
private:
	bool firstMove;

public:
	sf::Texture texture;
	Rook();
	Rook(int, int, int,int);
	~Rook();
	bool isMoveLegal(Coordinates);
	void findFieldsUnderAttack();
	void findAllPossibleMoves();

};

#endif

