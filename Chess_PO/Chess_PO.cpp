#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Piece.h"
#include "Pawn.h"


void initGame();
void resetGame();

Board* board;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Chess!");

    initGame();

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

        //update
        window.clear();
        board->update(window);
        Piece::update(window,*board);
        window.display();


        //debug
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            Board::printBoard();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
            Board::printUnderAttackWhite();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            Board::printUnderAttackBlack();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
        {
            Board::printCheckStatus();
        }


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
        {
            resetGame();
        }


    }

    return 0;
}


void initGame()
{
    board = new Board;
    board->setColorsofBoard(sf::Color::White, sf::Color(134, 79, 0, 255));
    board->init();
}

void resetGame()
{
    delete board;
    initGame();
}