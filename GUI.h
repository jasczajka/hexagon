#ifndef HEXXAGON_GUI_H
#define HEXXAGON_GUI_H
#include "Board.h"
#include <SFML/Graphics.hpp>

class GUI {
public:
    GUI(sf::RenderWindow& window, Board& board);
/**
 * \brief Renders the game board.
 *
 * This function takes the board of the game and prints its current state in the window
 */
     void renderBoard();
/**
* \brief Handles game events
*
* This function handles events during the game - clicks on the board
*/
     void handleGameEvents();
/**
* \brief Displays game over screen.
*
* This function shows a game over text colored depending on the winner and a New game text allowing to start a new game right away.
 * returns true until new game button is clicked
* \return boolean - true until a new game button is clicked, then false
*/
     bool displayGameOverScreen();

/**
* \brief Displays starting screen
*
* This function displays the starting screen and returns a <false,false> pair until a game is started
     * when the game is started, it returns <true,true> to start a game with computer and <true,false> to start a game with other player on the same screen
*
* \return Pair of booleans.
*/
     std::pair<bool,bool> displayStartingScreen();
/**
* \brief Shows available destinations during a game.
*
* This function displays the board and highlights available destinations from selected cell.
*/
     void showAvailableDestinations();
/**
* \brief Gets a cell on the board.
*
* This function gets the selected cell on the board during a game, it returns an incorrect cell with coordinates (-10,-10) if no valid cell was selected
* \return Selected HexCell
*/
     HexCell getSelectedCell();
/**
* \brief Gets a cell on the board.
*
* This function draws current score for each player on the board
*/
     void drawScores();

private:
    HexCell selectedCell;
    HexCell destinationCell;
    sf::RenderWindow& window;
    Board& board;
    const float hexagonSize;
    sf::Texture redHexagon;
    sf::Texture blueHexagon;
    sf::Texture emptyHexagon;
    sf::Texture emptyHexagonRange1;
    sf::Texture emptyHexagonRange2;
    sf::Texture redHexagonHighlighted;
    sf::Texture blueHexagonHighlighted;
    std::map<std::pair<int, int>, sf::Sprite> hexagonMap;
    bool showingDestinations;
    sf::Font font;
    sf::Color redColor;
    sf::Color blueColor;

};


#endif //HEXXAGON_GUI_H
