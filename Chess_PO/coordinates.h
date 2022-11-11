#ifndef _coordinates
#define _coordinates
class Coordinates
{
private:
	int _x;
	int _y;
public:
	Coordinates();
	Coordinates(int, int);
	int getX();
	int getY();
	void setX(int);
	void setY(int);
	char xToLetters(int);

	bool operator == (Coordinates const c);
	bool operator != (Coordinates const c);

	void print();

};

#endif

