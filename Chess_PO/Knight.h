#ifndef _knight
#define _Knight

#include "Piece.h"

class Knight : Piece
{
public:
	sf::Texture texture;
	Knight();
	Knight(int, int, int,int);
	~Knight();
	bool isMoveLegal(Coordinates);
	void setFieldsUnderAttack();

};
#endif

