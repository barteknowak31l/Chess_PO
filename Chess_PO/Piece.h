#ifndef _Piece
#define _Piece

#include "coordinates.h"
#include <SFML\Graphics.hpp>
#include <set>
#include "utils.h"

class Board;


class Piece : sf::Drawable
{
private:
	static bool isSomethingActive;
	bool isCollidingWithCursor(sf::Vector2f);

	

protected:
	Coordinates positionOnBoard;
	sf::Sprite sprite;

	//type of piece: pawn etc...
	int type;

	//position when moving with mouse
	sf::Vector2f temporaryPosition;

	static std::set<Piece*> instances;
	void draw(sf::RenderTarget&, sf::RenderStates) const override;

	//used in simulation step
	bool capturedInSimulation;


public:
	Piece();
	~Piece();
	
	//is piece clicked with mouse?
	bool isActive;

	//virtual methods
	virtual bool isMoveLegal(Coordinates) = 0;
	virtual void findFieldsUnderAttack() = 0;

	static const std::set<Piece*>& getInstances();
	static void drawPieces(sf::RenderWindow&,Board&);
	static void update(sf::RenderWindow&,Board&);
	static void setFieldsUnderAttack();

	void onClickAndHold(sf::RenderWindow&);
	void onMouseRelease(sf::RenderWindow&);

	int* getOverlappingField(sf::Vector2f);


	int pieceTypeToColor(int);


	//getters
	Coordinates getPositionOnBoard();
	int getType();
	static Piece* getPieceByCoords(Coordinates);

	//setters
	void setPositionOnboard(Coordinates);

	void setCapturedInSim();
	void unsetCapturedInSim();
};

#endif