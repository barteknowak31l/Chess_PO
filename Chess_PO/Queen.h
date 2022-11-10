#ifndef _Queen
#define _Queen

#include "Piece.h"

class Queen : Piece
{
private:
	bool diagonalMove(Coordinates);
	bool horizontalMove(Coordinates);

public:
	sf::Texture texture;
	Queen();
	Queen(int, int, int,int);
	~Queen();
	bool isMoveLegal(Coordinates);
	void setFieldsUnderAttack();


};
#endif

