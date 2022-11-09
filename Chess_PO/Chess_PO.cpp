#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include "Board.h"
#include "Piece.h"
#include "Pawn.h"


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Chess!");

    GameManager gm;
    GameManager* gameManager = &gm;
    
    gm.init();


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::Resized)
            {
                sf::FloatRect view(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(view));
            }
        }

        //draw step
        window.clear();
        gm.getBoard().drawBoard(window);
        gm.getBoard().calculatePiecesPositions();
        
        Piece::drawPieces(window,gm.getBoard());

        window.display();
    }

    return 0;
}