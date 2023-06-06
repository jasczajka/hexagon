#ifndef HEXXAGON_BOARD_H
#define HEXXAGON_BOARD_H
#include <vector>
#include "HexCell.h"
class Board{
public:
    Board();
/**
 * \brief Gets current player
 *
 * \return Integer - 1 for red player, 2 for blue player
 */
    int getCurrentPlayer() const;
/**
 * \brief Gets cell with coordinates
 *
 * This function takes two numbers, returns a cell with those coordinates, use this function if you want to change the cell as its a reference
 *
 * \param q q coordinate of the cell
 * \param r r coordinate of the cell
 * \return Reference to HexCell object
 */
    HexCell& getCell(int q, int r) ;
/**
 * \brief Gets cell with coordinates
 *
 * This function takes two numbers, returns a cell with those coordinates, use this function if you want to change the cell as its a reference
 *
 * \param q q coordinate of the cell
 * \param r r coordinate of the cell
 * \return  HexCell object
 */
    HexCell getCell(int q, int r) const;
/**
 * \brief Checks if cell if within the board
 *
 * This function takes two numbers, returns a bool value true if there's a cell with these coordinates on the board, false in other case
 *
 * \param q q coordinate of the cell
 * \param r r coordinate of the cell
 * \return  Bool true if cell is within the board, false otherwise
 */
    bool isCellWithinBoard(int q, int r) const;
/**
 * \brief Gets neighbors of a cell
 *
 * This function takes a HexCell objects and returns valid neighbors within a HexCell std::vector on the board, neighbors as in within range one
 *
 * \param cell HexCell object whose neighbors to return
 * \return  vector of HexCells - neighbors
 */
    std::vector<HexCell> getNeighbors(const HexCell& cell) const;
/**
 * \brief Makes a move on the board
 *
 * This function makes the move on the board, but doesnt check if its a valid move, it just makes the move and changes neigbors accordingly to current player
 * for each move by the player it checks if the current game is with computer and immediately makes a computer move if so, if a move is
 * made successfully, true is returned, false otherwise
 *
 * \param selectedCell  HexCell reference of a cell from which we're starting the move
 * \param destinationCell  HexCell reference of a cell to where we're doing the move
 *
 *  \return  boolean value - true if a player move is successfully made, false otherwise
 */
    bool makePlayerMove(HexCell& selectedCell, HexCell& destinationCell);
/**
 * \brief Computer makes a move on the board
 *
 * This function calculated the move that scores most of enemy cells in one move and makes it
 *
 */
    void makeComputerMove();
/**
 * \brief Gets a reference to all cells on the board
 *
 * \return  reference to vector of HexCells on the board
 */
    const std::vector<std::vector<HexCell>> &getCells() const;
/**
 * \brief Gets movable pieces of a player
 *
 * \param currentPlayer 1 for red 2 for blue -> currentPlayer
 * \return  vector of HexCells - movable by this playes
 */
    std::vector<HexCell> getMovablePieces(int currentPlayer) const ;
/**
 * \brief Gets available pieces to move to from this cell in range one by the current player
 *
 * \param cell reference to a cell that we want to get available destinations within range one
 * \return vector of HexCells - available destinations in range one
 */
    std::vector<HexCell> getAvailableDestPiecesInRangeOne(HexCell& cell) const;
/**
 * \brief Gets available pieces to move to from this cell in range two by the current player
 *
 * \param cell reference to a cell that we want to get available destinations within range two
 * \return vector of HexCells - available destinations in range two
 */
    std::vector<HexCell> getAvailableDestPiecesInRangeTwo(HexCell& cell) const ;
/**
 * \brief Checks if the cell is within range one of the other cell
 *
 * This function takes two parameters, returns a boolean value true if startingCell is within range one to destinationCell, false otherwise
 *
 * \param startingCell reference to HexCell object from which we're checking the distance
 * \param destinationCell reference to HexCell object to which we're checking the distance
 * \return  bool value
 */
    bool isDestWithinOne (HexCell& startingCell,HexCell& destinationCell) const;
/**
 * \brief Checks if the cell is within range two of the other cell
 *
 * This function takes two parameters, returns a boolean value true if startingCell is within range two to destinationCell, false otherwise
 *
 * \param startingCell reference to HexCell object from which we're checking the distance
 * \param destinationCell reference to HexCell object to which we're checking the distance
 * \return  bool value
 */
    bool isDestWithinTwo (HexCell& startingCell,HexCell& destinationCell) const;
/**
 * \brief Gets the score of the specified player
 *
 * This function takes one parameter - 1 for red player, 2 for blue and returns current score of the chosen player
 *
 * \param player integer of a player we want to get the score of - 1 for red, 2 for blue
 * \param destinationCell reference to HexCell object to which we're checking the distance
 * \return  integer value - sum of current fields occupied by specified player
 */
    int getScoreOfPlayer(int player) const;
/**
 * \brief Checks the board if the game is over
 *
 * This function checks on the board if there are any players that have no moves left available, if so, return true, otherwise false
 *
 * \return  boolean - true if the game is over, false otherwise
 */
    bool isGameOver() const;
    bool playWithComputer;
private:
    std::vector<std::vector<HexCell>> cells;
    int currentPlayer;
};

#endif //HEXXAGON_BOARD_H