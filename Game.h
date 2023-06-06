#ifndef HEXXAGON_GAME_H
#define HEXXAGON_GAME_H
#include "HexCell.h"
#include "GUI.h"
#include <SFML/Graphics.hpp>



class Game {
private:
    sf::RenderWindow window;
    Board board;
    GUI gui;
public:
    Game();
    /**
 * \brief runs the game
 *
 * This function runs the program until the window is closed
 *
 */
    void play();
    bool isWindowOpen() const;
};


#endif //HEXXAGON_GAME_H
