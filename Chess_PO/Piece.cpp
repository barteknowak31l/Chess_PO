#include "Piece.h"
#include <iostream>
#include "Board.h"
#include "utils.h"

std::set<Piece*> Piece::instances;
bool Piece::isSomethingActive;

Piece::Piece()
{
	//if a set of pieces doesn't exist - create one
	if (getInstances().size() == 0)
	{
		instances = std::set<Piece*>();
		isSomethingActive = false;
	}

	isActive = false;
	capturedInSimulation = false;
	firstMove = true;

}

//function required by SFML
void Piece::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->sprite, states);
}

Piece::~Piece()
{
	//delete a piece from set of instances
	instances.erase(this);
}

const std::set<Piece*>& Piece::getInstances()
{
	return instances;
}

void Piece::drawPieces(sf::RenderWindow& target, Board &b)
{
	//scale pieces with window size
	float x = target.getSize().x * 0.75;
	float y = target.getSize().y;
	float size = std::min(x, y) / 8;

	//for all pieces
	for(Piece* p : Piece::getInstances())
	{
		//find apropriate position of a sprite
		if (p->isActive)
		{
			p->sprite.setPosition(p->temporaryPosition);
		}
		else
		{
			p->sprite.setPosition(b.getPiecesPositions(p->positionOnBoard.getX(), p->positionOnBoard.getY()));
		}
		
		//and scale sprite with window size
		p->sprite.setScale(size/90,size/90);


		//draw sprite to a screen
		target.draw(p->sprite);
	}
}

void Piece::update(sf::RenderWindow& target, Board& b)
{

	//mouse input for all pieces
	for (Piece* p : Piece::getInstances())
	{
		//check for mouse input
		if (p->isActive || Piece::isSomethingActive == 0)
		{
			//determine if it's this color's turn - to avoid moving piece of a wrong color 
			if (Board::getTurn() == p->pieceTypeToColor(p->type))
			{
				p->onClickAndHold(target);
				p->onMouseRelease(target);
			}
		}
	}

	//pieces are updated, draw them to a screen
	Piece::drawPieces(target, b);

}

void Piece::setFieldsUnderAttack()
{
	//for all pieces call findFieldsUnderAttack
	for (Piece* p : getInstances())
	{
		p->findFieldsUnderAttack();
	}
}


void Piece::onClickAndHold(sf::RenderWindow& target)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		//mouse position
		sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(target).x, sf::Mouse::getPosition(target).y);

		//check if mouse cursor collides with piece sprite
		if (isCollidingWithCursor(mousePos) == 0)
		{
			return;
		}

		isActive = true;
		isSomethingActive = true;

		//set temporary position on board - for effect of piece following a mouse cursor - coordinates of a piece will be changed or rejected (incorrect move) when mouse is released
		temporaryPosition = mousePos;
		
	}
}

void Piece::onMouseRelease(sf::RenderWindow& window)
{
	if (isActive && sf::Mouse::isButtonPressed(sf::Mouse::Left) == 0)
	{

		//mouse position
		sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);


		//unset active flags
		isActive = false;
		isSomethingActive = false;

		//find new coordinates by given mouse position
		int* newPos = nullptr;
		newPos = Board::screenToBoardPos(mousePos);
		if (newPos == nullptr)
		{
			return;
		}
		
		Coordinates newCoords;
		newCoords.setX(newPos[0]);
		newCoords.setY(newPos[1]);


		//perform a move - check if it is legal, if not - return to old position on screen (sprite) and old coordinates
		Board::move(this, newCoords);





	}
}

bool Piece::isCollidingWithCursor(sf::Vector2f mousePos)
{
	return sprite.getGlobalBounds().contains(mousePos);
}

int Piece::pieceTypeToColor(int t)
{
	switch (t)
	{
		case w_pawn:
		case w_rook:
		case w_knight:
		case w_bishop:
		case w_queen:
		case w_king: 
		{
			return 0;
		}
		case b_pawn:
		case b_rook:
		case b_knight:
		case b_bishop:
		case b_queen:
		case b_king:
		{
			return 1;
		}

		default: return -1;
	}
}


//getters
Coordinates Piece::getPositionOnBoard()
{
	return positionOnBoard;
}

int Piece::getType()
{
	return type;
}

Piece* Piece::getPieceByCoords(Coordinates c)
{
	//return piece pointer to piece on given coords
	for (Piece* p : getInstances())
	{
		if (p->positionOnBoard == c)
		{
			return p;
		}
	}

	return nullptr;
}

std::set<Coordinates*> Piece::getPossibleMoves()
{
	return possibleMoves;
}

void Piece::addCoordsToSet(Coordinates c)
{
	Coordinates* n = new Coordinates;
	n->setX(c.getX());
	n->setY(c.getY());

	possibleMoves.insert(n);

}

void Piece::clearSetofCoords()
{
	for (Coordinates* c : possibleMoves)
	{
		delete c;
	}

	possibleMoves.clear();
}

bool Piece::getFirstMove()
{
	return firstMove;
}

//setters
void Piece::setPositionOnboard(Coordinates c)
{
	positionOnBoard = c;
}

void Piece::setCapturedInSim()
{
	capturedInSimulation = true;
}

void Piece::unsetCapturedInSim()
{
	capturedInSimulation = false;
}
