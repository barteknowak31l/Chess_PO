#ifndef _Queen
#define _Queen

#include "Piece.h"

class Queen : Piece
{
private:
	bool diagonalMove(Coordinates);
	bool horizontalVerticalMove(Coordinates);
	void diagonalUnderAttack();
	void horizontalVerticalUnderAttack();

public:
	sf::Texture texture;
	Queen();
	Queen(int, int, int,int);
	~Queen();
	bool isMoveLegal(Coordinates);
	void setFieldsUnderAttack();


};
#endif

