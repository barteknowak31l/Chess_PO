#include "Piece.h"
#include <iostream>
#include "Board.h"
#include "utils.h"

std::set<Piece*> Piece::instances;
bool Piece::isSomethingActive;

Piece::Piece()
{
	if (getInstances().size() == 0)
	{
		instances = std::set<Piece*>();
		isSomethingActive = false;
	}

	isActive = false;

}

void Piece::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->sprite, states);
}
Piece::~Piece()
{
	instances.erase(this);
}


const std::set<Piece*>& Piece::getInstances()
{
	return instances;
}


void Piece::drawPieces(sf::RenderWindow& target, Board &b)
{

	for(Piece* p : Piece::getInstances())
	{
		if (p->isActive)
		{
			p->sprite.setPosition(p->temporaryPosition);
		}
		else
		{
			p->sprite.setPosition(b.getPiecesPositions(p->positionOnBoard.getX(), p->positionOnBoard.getY()));
		}
		
		target.draw(p->sprite);
	}
}

void Piece::update(sf::RenderWindow& target, Board& b)
{
	for (Piece* p : Piece::getInstances())
	{
		//set fields under attack
		//if(p->type == w_king || p->type == b_king)

		//check for mouse input
		if (p->isActive || Piece::isSomethingActive == 0)
		{
			//it's this color's turn
			if (Board::getTurn() == p->pieceTypeToColor(p->type))
			{
				p->onClickAndHold(target);
				p->onMouseRelease(target);
			}
		}
	}
	Piece::drawPieces(target, b);

}

void Piece::setFieldsUnderAttack()
{
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
		//std::cout << mousePos.x << " " << mousePos.y<<std::endl;

		//check collision
		if (isCollidingWithCursor(mousePos) == 0)
		{
			return;
		}

		isActive = true;
		isSomethingActive = true;

		//set new position on board
		temporaryPosition = mousePos;
		
		//piece should follow cursor;
		//std::cout << "clicked on: "<<positionOnBoard.getX()<<" "<<positionOnBoard.getY()<<std::endl;
		
		//sprite.setPosition(mousePos);
	}
}

void Piece::onMouseRelease(sf::RenderWindow& window)
{
	if (isActive && sf::Mouse::isButtonPressed(sf::Mouse::Left) == 0)
	{

		//mouse position
		sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

		isActive = false;
		isSomethingActive = false;

		int* newPos = nullptr;
		newPos = Board::screenToBoardPos(mousePos);
		if (newPos == nullptr)
		{
			return;
		}
		
		Coordinates newCoords;
		newCoords.setX(newPos[0]);
		newCoords.setY(newPos[1]);

		Board::move(this, newCoords);

		//THIS SECTION IS MOVED TO CLASS BOARD - move()
		// 
		//std::cout << "newPos: " << newPos[0] << " " << newPos[1] << std::endl;

		//set old logical position to empty state
		//Board::_b[positionOnBoard.getX()][positionOnBoard.getY()] = empty;
		
		//set new position to piece object
		//positionOnBoard.setX(newPos[0]);
		//positionOnBoard.setY(newPos[1]);
		
		//set new position of piece in logical representation of board
		//Board::_b[newPos[0]][newPos[1]] = type;



	}
}

int* Piece::getOverlappingField(sf::Vector2f mousePos)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j, 8; j++)
		{
			if (Board::fields[i][j].getGlobalBounds().contains(mousePos))
			{
				int* ans = new int[2];
				ans[0] = i;
				ans[1] = j;
				return ans;
			}
		}
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


//setters
void Piece::setPositionOnboard(Coordinates c)
{
	positionOnBoard = c;
}

