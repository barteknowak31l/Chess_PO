#ifndef _coordinates
#define _coordinates


//this class defines logical coordinates on the chessboard

class Coordinates
{
private:
	int _x;
	int _y;

public:
	Coordinates();
	
	//params: coord x, coord y
	Coordinates(int, int);

	//getters

	int getX();
	int getY();
	
	//setters
	void setX(int);
	void setY(int);

	//utility - returns character associated with given field (like on chessboard)
	char xToLetters(int);


	//custom operators

	bool operator == (Coordinates const c);
	bool operator != (Coordinates const c);

	
	void print();

};

#endif

