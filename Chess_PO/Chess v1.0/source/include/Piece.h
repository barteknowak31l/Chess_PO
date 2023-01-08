#ifndef _Piece
#define _Piece

#include "coordinates.h"
#include "SFML\Graphics.hpp"
#include <set>
#include "utils.h"

class Board;


class Piece : sf::Drawable
{
private:

	//PRIVATE FIELDS
	
	//determines if any piece is dragged with mouse cursor
	static bool isSomethingActive;

	//flag to determine if piece is clicked with mouse
	bool isActive;

	//PRIVATE METHODS
	
	//checks if piece is overlapped by mouse cursor
	bool isCollidingWithCursor(sf::Vector2f);

protected:
	
	//PROTECTED FIELDS
	
	//set of all instances of Piece objects
	static std::set<Piece*> instances;

	//stores logical position of a piece on board
	Coordinates positionOnBoard;
	
	//stores piece sprite
	sf::Sprite sprite;

	//type of piece: pawn etc... (types are defined in utils.h)
	int type;

	//temporary position when moving a piece with mouse
	sf::Vector2f temporaryPosition;

	//set of all possible moves by a piece, including captures, and castle
	std::set<Coordinates*> possibleMoves;

	//flag to determine if this piece is captured during simulation of next move (if so, it won't be taken into account during calculation of fieldsUnderAttack)
	bool capturedInSimulation;

	//used for kings,rooks and pawns only - according to chess rules - those pieces have special moves if weren't already moved
	bool firstMove;


	//PROTECTED VIRTUAL METHODS
	
	//override for each piece - determines fields that are attacked by this piece, according to chess rules
	virtual void findFieldsUnderAttack() = 0;



	//PROTECTED STATIC METHODS
	
	//function to draw ALL pieces on a screen - should be invoked in update function
	static void drawPieces(sf::RenderWindow&, Board&);


	//PROTECTED METHODS
	
	//function to enable drawing in scene for this class - required by SFML
	void draw(sf::RenderTarget&, sf::RenderStates) const override;

	//utility function to add coordinates of new possible move to possibleMoves set
	void addCoordsToSet(Coordinates);

	//utility function to cleat set of possible moves
	void clearSetofCoords();

	//handles dragging a piece with a mouse cursor
	void onClickAndHold(sf::RenderWindow&);

	//handles releasing a piece with a mouse cursor
	void onMouseRelease(sf::RenderWindow&);

public:
	Piece();
	~Piece();
	


	//PUBLIC VIRTUAL METHODS
	
	//override for each piece - checks if given move (destinated coordinates) is legal according to chess rules
	virtual bool isMoveLegal(Coordinates) = 0;
	
	//override for each piece - creates a set of possible moves - according to chess rules
	virtual void findAllPossibleMoves() = 0;



	//PUBLIC STATIC METHODS
	
	//gets set of all pieces - for iterating over all pieces
	static const std::set<Piece*>& getInstances();

	//called once each frame - draws pieces and handles mouse input on pieces
	static void update(sf::RenderWindow&,Board&);

	//calls findFieldsUnderAttack on each piece
	static void setFieldsUnderAttack();
	


	//PUBLIC METHODS
	
	//utility function - returns a color id by given piece type
	int pieceTypeToColor(int);



	//GETTERS
	
	//returns coordinates of logical position of a piece on board
	Coordinates getPositionOnBoard();

	//returns a type of a piece
	int getType();

	//finds a piece on given coordinates - returns pointer to a piece or nullptr if there is no piece on given coordinates
	static Piece* getPieceByCoords(Coordinates);

	//returns a set of possible moves of a piece
	std::set<Coordinates*> getPossibleMoves();

	//returns a firstMove flag
	bool getFirstMove();



	//SETTERS
	//
	//sets positionOnBoard to given coordinates
	void setPositionOnboard(Coordinates);

	//used in simulation - set capturedInSim flag
	void setCapturedInSim();

	//used in simulation - unset capturedInSim flag
	void unsetCapturedInSim();
};

#endif