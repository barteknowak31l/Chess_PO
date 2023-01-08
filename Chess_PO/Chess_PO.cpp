#include <SFML/Graphics.hpp>
#include "include\Board.h"
#include "include\Piece.h"
#include "include\Pawn.h"

#include <iostream>
#include <fstream>
#include <string>


//initial window size
unsigned int windowInitSizeX = 1000;
unsigned int windowInitSizeY = 600;

//store window size
unsigned int sizeX;
unsigned int sizeY;


//config

//options
int white_field_R = 255;
int white_field_G = 255;
int white_field_B = 255;

int black_field_R = 0;
int black_field_G = 0;
int black_field_B = 0;

int message_R = 255;
int message_G = 255;
int message_B = 255;

int dbg = 0;

int num_of_fields_in_config = 10;
std::string options[10] =
{
"white_field_R:",
"white_field_G:",
"white_field_B:",
"black_field_R:",
"black_field_G:",
"black_field_B:",
"message_R:",
"message_G:",
"message_B:",
"debug:"
};

//load a configuration file
void config();
//


//pointer to board object
Board* board;

//main loop that runs until winodw is closed
void windowLoop(sf::RenderWindow&);

//handles window events
void eventHandler(sf::RenderWindow&);

//initialize game instance
void initGame();

//destroy old and create new game instance
void resetGame();

//debugging options
void debug(sf::RenderWindow&);

//update game instance and draw object to the window
void update(sf::RenderWindow&);



int main()
{
    //load config file
    config();

    //create a window
    sf::RenderWindow window(sf::VideoMode(windowInitSizeX, windowInitSizeY),"Chess!");

    //initialize a game instance
    initGame();


    //run window loop
    windowLoop(window);

    return 0;
}

void windowLoop(sf::RenderWindow& window)
{
    while (window.isOpen())
    {
        //window events
        eventHandler(window);

        //update game instance and draw to the window
        update(window);

        //debug
        if (dbg)
        debug(window);
    }
}

void eventHandler(sf::RenderWindow& window)
{
    sf::Event event;

    sizeX = window.getSize().x;
    sizeY = window.getSize().y;

    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::Resized)
        {
            //make sure new window size is not smaller than initial size
            if (window.getSize().x < windowInitSizeX || window.getSize().y < windowInitSizeY)
            {
                window.setSize(sf::Vector2u(sizeX, sizeY));
            }



            //for appropriate window scaling
            sf::FloatRect view(0, 0, event.size.width, event.size.height);
            window.setView(sf::View(view));
        }
    }
}

void initGame()
{
    board = new Board;

    //white field color
    sf::Color w_f_color((sf::Uint8)white_field_R, (sf::Uint8)white_field_G, (sf::Uint8)white_field_B, 255);

    //black field color
    sf::Color b_f_color((sf::Uint8)black_field_R, (sf::Uint8)black_field_G, (sf::Uint8)black_field_B, 255);

    //messagebox text color
    sf::Color message_color((sf::Uint8)message_R, (sf::Uint8)message_G, (sf::Uint8)message_B, 255);

    board->setColorsofBoard(w_f_color,b_f_color);
    board->setMessageTextColor(message_color);
    
    board->init();
}

void resetGame()
{
    delete board;
    initGame();
}

void config()
{
    //open config file
    
    std::ifstream cfg;
    cfg.open("config.txt");

    if (cfg.fail())
    {
        std::cout << "file config.txt does not exist - please, create file named config.txt in main folder, leave it empty if you want to use default options";
        exit(-1);
    }

    std::string line;

    int pos;

    bool optionSet = false;

    while(std::getline(cfg, line))
    {

        //find an option to set:
        optionSet = false;
        for (int j = 0; j < num_of_fields_in_config; j++)
        {
            if (optionSet)
            {
                break;
            }

            if ((pos = line.find(options[j])) != std::string::npos) //find returns npos when nothing found
            {
                line.erase(pos, options[j].length());


                //set appropriate option
                switch (j)
                {
                case 0:
                {
                    try
                    {
                        white_field_R = stoi(line);
                    }
                    catch (std::invalid_argument const& ex)
                    {
                        std::cout << "invalid argument of white_field_R in config.txt - change it to integer value\n";
                    }
                    optionSet = true;
                    break;
                }
                case 1:
                {
                    try
                    {
                        white_field_G = stoi(line);
                    }
                    catch (std::invalid_argument const& ex)
                    {
                        std::cout << "invalid argument of white_field_G in config.txt - change it to integer value\n";
                    }
                    optionSet = true;
                    break;
                }
                case 2:
                {
                    try
                    {
                        white_field_B = stoi(line);
                    }
                    catch (std::invalid_argument const& ex)
                    {
                        std::cout << "invalid argument of white_field_B in config.txt - change it to integer value\n";
                    }
                    optionSet = true;
                    break;
                }
                case 3:
                {
                    try
                    {
                        black_field_R = stoi(line);
                    }
                    catch (std::invalid_argument const& ex)
                    {
                        std::cout << "invalid argument of black_field_R in config.txt - change it to integer value\n";
                    }
                    optionSet = true;
                    break;
                }
                case 4:
                {
                    try
                    {
                        black_field_G = stoi(line);
                    }
                    catch (std::invalid_argument const& ex)
                    {
                        std::cout << "invalid argument of black_field_G in config.txt - change it to integer value\n";
                    }
                    optionSet = true;
                    break;
                }
                case 5:
                {
                    try
                    {
                        black_field_B = stoi(line);
                    }
                    catch (std::invalid_argument const& ex)
                    {
                        std::cout << "invalid argument of black_field_B in config.txt - change it to integer value\n";
                    }
                    optionSet = true;
                    break;
                }
                case 6:
                {
                    try
                    {
                        message_R = stoi(line);
                    }
                    catch (std::invalid_argument const& ex)
                    {
                        std::cout << "invalid argument of message_R in config.txt - change it to integer value\n";
                    }
                    optionSet = true;
                    break;
                }
                case 7:
                {
                    try
                    {
                        message_G = stoi(line);
                    }
                    catch (std::invalid_argument const& ex)
                    {
                        std::cout << "invalid argument of message_G in config.txt - change it to integer value\n";
                    }
                    message_G = stoi(line);
                    optionSet = true;
                    break;
                }
                case 8:
                {
                    try
                    {
                        message_B = stoi(line);
                    }
                    catch (std::invalid_argument const& ex)
                    {
                        std::cout << "invalid argument of message_B in config.txt - change it to integer value\n";
                    }
                    optionSet = true;
                    break;
                }
                case 9:
                {
                    try
                    {
                        dbg = stoi(line);
                    }
                    catch (std::invalid_argument const& ex)
                    {
                        std::cout << "invalid argument of debug in config.txt - change it to integer value (0 means no debugging)\n";
                    }
                    optionSet = true;
                    break;
                }
                default:
                {
                    break;
                }


                }

            }
        }


    }

    cfg.close();
}

void debug(sf::RenderWindow &window)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        Board::printBoard();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        window.setSize(sf::Vector2u(windowInitSizeX, windowInitSizeY));
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
}

void update(sf::RenderWindow& window)
{
    window.clear();
    board->update(window);
    Piece::update(window, *board);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
    {
        resetGame();
    }

    window.display();
}