#ifndef _Bishop
#define _Bishop

#include "Piece.h"

class Bishop : Piece
{
public:
	sf::Texture texture;
	Bishop();
	Bishop(int, int, int,int);
	~Bishop();
	bool isMoveLegal(Coordinates);
	void findFieldsUnderAttack();
	void findAllPossibleMoves();

};
#endif

