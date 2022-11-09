#include "Piece.h"
#include <iostream>


std::set<Piece*> Piece::instances;

Piece::Piece()
{
	if (getInstances().size() == 0)
	{
		instances = std::set<Piece*>();
	}

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


void Piece::drawPieces(sf::RenderTarget& target, Board &b)
{

	for(Piece* p : Piece::getInstances())
	{
		p->sprite.setPosition(b.getPiecesPositions(p->positionOnBoard.getX(),p->positionOnBoard.getY()));
		target.draw(p->sprite);
	}
}