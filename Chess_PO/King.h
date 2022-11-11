#ifndef _King
#define _King

#include "Piece.h"

class King : Piece
{

private:
	int castle(Coordinates);
	bool firstMove;

public:
	sf::Texture texture;
	King();
	King(int, int, int,int);
	~King();
	bool isMoveLegal(Coordinates);
	void findFieldsUnderAttack();
	void findAllPossibleMoves();

};
#endif

