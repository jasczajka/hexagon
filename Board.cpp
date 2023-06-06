#include <iostream>
#include "Board.h"
#include "HexCell.h"
#include <map>

Board::Board(): currentPlayer(1), playWithComputer(false){
    std::vector<HexCell> newColumn;
    for(int q = 0; q<5; q++){
        newColumn.push_back((HexCell(-4,q)));

    }
    this->cells.push_back(newColumn);
    newColumn.erase(newColumn.begin(),newColumn.end());
    for(int q = -1; q<5; q++){
        newColumn.push_back((HexCell(-3,q)));
    }
    this->cells.push_back(newColumn);
    newColumn.erase(newColumn.begin(),newColumn.end());

    for(int q = -2; q<5; q++){
        newColumn.push_back((HexCell(-2,q)));
    }
    this->cells.push_back(newColumn);
    newColumn.erase(newColumn.begin(),newColumn.end());

    for(int q = -3; q<5; q++){
        newColumn.push_back((HexCell(-1,q)));
    }
    this->cells.push_back(newColumn);
    newColumn.erase(newColumn.begin(),newColumn.end());

    for(int q = -4; q<5; q++){
        newColumn.push_back((HexCell(0,q)));

    }
    this->cells.push_back(newColumn);
    newColumn.erase(newColumn.begin(),newColumn.end());

    for(int q = -4; q<4; q++){
        newColumn.push_back((HexCell(1,q)));
    }
    this->cells.push_back(newColumn);
    newColumn.erase(newColumn.begin(),newColumn.end());

    for(int q = -4; q<3; q++){
        newColumn.push_back((HexCell(2,q)));
    }
    this->cells.push_back(newColumn);
    newColumn.erase(newColumn.begin(),newColumn.end());

    for(int q = -4; q<2; q++){
        newColumn.push_back((HexCell(3,q)));
    }
    this->cells.push_back(newColumn);
    newColumn.erase(newColumn.begin(),newColumn.end());

    for(int q = -4; q<1; q++){
        newColumn.push_back((HexCell(4,q)));

    }
    this->cells.push_back(newColumn);
    newColumn.erase(newColumn.begin(),newColumn.end());
    getCell(-4,0).setState(1);
    getCell(-4,4).setState(2);
    getCell(0,-4).setState(2);
    getCell(0,4).setState(1);
    getCell(4,-4).setState(1);
    getCell(4,0).setState(2);
    getCell(0,-1).setState(3);
    getCell(-1,1).setState(3);
    getCell(1,0).setState(3);


}

bool Board::makePlayerMove( HexCell& selectedCell, HexCell& destinationCell) {
    int enemyPlayer = currentPlayer == 1?2:1;

    auto availablePieces = getMovablePieces(currentPlayer);
    std::vector<HexCell> availableDestPiecesInRangeOne = getAvailableDestPiecesInRangeOne(selectedCell);
    std::vector<HexCell> availableDestPiecesInRangeTwo = getAvailableDestPiecesInRangeTwo(selectedCell);


    bool isWithinOne = isDestWithinOne(selectedCell,destinationCell);
    bool isWithinTwo = isDestWithinTwo(selectedCell,destinationCell);


    if(isWithinOne && destinationCell.getState() == 0){
        destinationCell.setState(currentPlayer);
        for(auto& neighbor : getNeighbors(destinationCell)){
            if(neighbor.getState() == enemyPlayer) {
                HexCell& enemyneighbor = getCell(neighbor.getQ(),neighbor.getR());
                enemyneighbor.setState(currentPlayer);

            }
        }
        this->currentPlayer = currentPlayer==1?2:1;
        if(playWithComputer && !isGameOver()){
            makeComputerMove();
        }
        std::cout<<"move made in range 1"<<"\n";
        return true;
    }
    else if(isWithinTwo && destinationCell.getState() == 0){
        destinationCell.setState(currentPlayer);
        selectedCell.setState(0);
        for(auto& neighbor : getNeighbors(destinationCell)){
            if(neighbor.getState() == enemyPlayer) {
                HexCell& enemyneighbor = getCell(neighbor.getQ(),neighbor.getR());
                enemyneighbor.setState(currentPlayer);
            }
        }
        this->currentPlayer = currentPlayer==1?2:1;
        if(playWithComputer && !isGameOver()){
            makeComputerMove();
        }
        std::cout<<"move made in range 2"<<"\n";
        return true;
    }
    return false;
}

HexCell& Board::getCell(int q, int r)  {
    if(isCellWithinBoard(q,r)) {
        for (auto &column: cells) {
            for (auto &cell: column) {
                if (cell.getQ() == q && cell.getR() == r) {
                    return cell;
                }
            }
        }
    }
}

HexCell Board::getCell(int q, int r) const  {
    if(isCellWithinBoard(q,r)) {
        for (auto &column: cells) {
            for (auto &cell: column) {
                if (cell.getQ() == q && cell.getR() == r) {
                    return cell;
                }
            }
        }
    }
}


bool Board::isCellWithinBoard(int q, int r) const{

    for(const auto& column : cells){
        for (auto& cell : column){
            if(cell.getQ() == q && cell.getR() == r && cell.getState() != 3){
                return true;
            }
        }
    }
    return  false;
}

std::vector<HexCell> Board::getNeighbors(const HexCell& cell) const {
    std::vector<HexCell> neighbors;
    int q = cell.getQ();
    int r = cell.getR();
    if (isCellWithinBoard(q-1, r)) {
        neighbors.push_back(getCell(q-1, r));
    }
    if (isCellWithinBoard(q+1, r)) {
        neighbors.push_back(getCell(q+1, r));
    }
    if (isCellWithinBoard(q, r-1)) {
        neighbors.push_back(getCell(q, r-1));
    }
    if (isCellWithinBoard(q, r+1)) {
        neighbors.push_back(getCell(q, r+1));
    }
    if (isCellWithinBoard(q-1, r+1)) {
        neighbors.push_back(getCell(q-1, r+1));
    }
    if (isCellWithinBoard(q+1, r-1)) {
        neighbors.push_back(getCell(q+1, r-1));
    }
    return neighbors;
}


const std::vector<std::vector<HexCell>> &Board::getCells() const {
    return cells;
}

std::vector<HexCell> Board::getMovablePieces(int currentPlayer) const {
    std::vector<HexCell> availablePieces;
    for (auto& column: cells) {
        for (auto cell: column) {
            if ( (!(getAvailableDestPiecesInRangeOne(cell).empty()) ||
                !(getAvailableDestPiecesInRangeTwo(cell).empty())
                ) && cell.getState() == currentPlayer)  {
                availablePieces.push_back(cell);
            }
        }
    }
    return availablePieces;
}
std::vector<HexCell> Board::getAvailableDestPiecesInRangeOne(HexCell& cell) const{
    std::vector<HexCell> availableDestPiecesInRangeOne;
    for(auto neighbor : getNeighbors(cell)){
        if(neighbor.getState() == 0){
            availableDestPiecesInRangeOne.push_back(neighbor);
        }
    }
    return  availableDestPiecesInRangeOne;
}

std::vector<HexCell> Board::getAvailableDestPiecesInRangeTwo(HexCell& cell) const{
    std::vector<HexCell> availableDestPiecesInRangeOne = getAvailableDestPiecesInRangeOne(cell);
    std::vector<HexCell> availableDestPiecesInRangeTwo;
    for(auto neighbor : getNeighbors(cell)) {
        for (auto neighbor_of_neighbor: getNeighbors(neighbor)) {
            if (neighbor_of_neighbor.getState() == 0) {
                if (std::find(availableDestPiecesInRangeOne.begin(), availableDestPiecesInRangeOne.end(),neighbor_of_neighbor) == availableDestPiecesInRangeOne.end() &&
                    std::find(availableDestPiecesInRangeTwo.begin(), availableDestPiecesInRangeTwo.end(),neighbor_of_neighbor) == availableDestPiecesInRangeTwo.end()) {
                    availableDestPiecesInRangeTwo.push_back(neighbor_of_neighbor);
                }
            }
        }
    }
    return  availableDestPiecesInRangeTwo;
}



bool Board::isDestWithinOne (HexCell& startingCell,HexCell& destinationCell) const{
    bool isWithinOne = false;
    for(auto& neighbor : getNeighbors(startingCell)){
        if(neighbor == destinationCell){
            isWithinOne = true;
        }
    }
    return isWithinOne;
}

bool Board::isDestWithinTwo (HexCell& startingCell,HexCell& destinationCell) const{
    bool isWithinTwo = false;
    if(!isDestWithinOne(startingCell,destinationCell)) {
        for (auto &neighbor: getNeighbors(startingCell)) {
            for (auto &neighbor_of_neighbor: getNeighbors(neighbor)) {
                if (neighbor_of_neighbor == destinationCell){
                    isWithinTwo = true;
                }
            }
        }
    }
    return isWithinTwo;
}

int Board::getCurrentPlayer() const {
    return currentPlayer;
}

void Board::makeComputerMove(){

    int enemyPlayer = currentPlayer == 1?2:1;
    auto availablePieces = getMovablePieces(currentPlayer);
    std::map<int,std::pair<HexCell,HexCell>> possibleScores;
    for(auto& startingCell : availablePieces){
        for(auto& destCell : getAvailableDestPiecesInRangeOne(startingCell)){
            int possibleScore = 0;
            for (auto& neighbor: getNeighbors(destCell)){
                if(neighbor.getState() == enemyPlayer){
                    possibleScore++;
                }
            }
            auto cellPair = std::make_pair(startingCell,destCell);
            possibleScores.insert({possibleScore,cellPair});
        }
        for(auto& destCell : getAvailableDestPiecesInRangeTwo(startingCell)){
            int possibleScore = 0;
            for (auto& neighbor: getNeighbors(destCell)){
                if(neighbor.getState() == enemyPlayer){
                    possibleScore++;
                }
            }
            auto cellPair = std::make_pair(startingCell,destCell);
            possibleScores.insert({possibleScore,cellPair});
        }
    }


    HexCell& selectedCell = getCell(possibleScores.rbegin()->second.first.getQ(),possibleScores.rbegin()->second.first.getR());
    HexCell& destCell = getCell(possibleScores.rbegin()->second.second.getQ(),possibleScores.rbegin()->second.second.getR());

    std::cout<<selectedCell.getQ()<< " " << selectedCell.getR() << "\n";
    std::cout<<destCell.getQ()<< " " << destCell.getR() << "\n";

    bool isWithinOne = isDestWithinOne(selectedCell,destCell);
    bool isWithinTwo = isDestWithinTwo(selectedCell,destCell);
    if(isWithinOne && destCell.getState() == 0){
        destCell.setState(currentPlayer);
        for(auto& neighbor : getNeighbors(destCell)){
            if(neighbor.getState() == enemyPlayer) {
                HexCell& enemyneighbor = getCell(neighbor.getQ(),neighbor.getR());
                enemyneighbor.setState(currentPlayer);
            }
        }
    }
    else if(isWithinTwo && destCell.getState() == 0){
        destCell.setState(currentPlayer);
        selectedCell.setState(0);
        for(auto& neighbor : getNeighbors(destCell)){
            if(neighbor.getState() == enemyPlayer) {
                HexCell& enemyneighbor = getCell(neighbor.getQ(),neighbor.getR());
                enemyneighbor.setState(currentPlayer);
            }
        }
    }
    this->currentPlayer = currentPlayer==1?2:1;
}

int Board::getScoreOfPlayer(int player) const{
    int score = 0;
    for(auto& column : cells){
        for(auto& cell : column){
            if(cell.getState() == player){
                score++;
            }
        }
    }
    return score;
}

bool Board::isGameOver() const  {
    if (getMovablePieces(1).empty() || getMovablePieces(2).empty() ) {
        return true;
    }
    return false;
}


