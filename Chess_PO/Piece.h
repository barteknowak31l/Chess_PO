#ifndef _Piece
#define _Piece

#include "coordinates.h"
#include <SFML\Graphics.hpp>
#include <set>

class Piece : sf::Drawable
{
private:


protected:
	static std::set<Piece*> instances;
	Coordinates position;
	sf::Sprite sprite;

	void draw(sf::RenderTarget&, sf::RenderStates) const override;

public:
	Piece();

	~Piece();
	
	virtual void move(Coordinates) = 0;

	static const std::set<Piece*>& getInstances();
	static void drawPieces(sf::RenderTarget&);



};

#endif