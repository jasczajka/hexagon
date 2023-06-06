#include "Game.h"
#include "iostream"
#include "GUI.h"

Game::Game() :
        board(Board()),
        window(sf::VideoMode({1600, 1600}), "Hexagon"),
        gui(GUI(window, board))
{}


bool Game::isWindowOpen() const {
    return window.isOpen();
}

void Game::play() {
    board = Board();
    std::pair<bool, bool> gameMode = std::make_pair(false, false);
    while (!gameMode.first && window.isOpen()) {
        gameMode = gui.displayStartingScreen();
    }
    board.playWithComputer = gameMode.second;
    window.clear();
    gui.renderBoard();
    gui.handleGameEvents();
    while (window.isOpen() && !board.isGameOver()) {
        gui.handleGameEvents();
    }
    while (window.isOpen() && gui.displayGameOverScreen()) {
        gui.displayGameOverScreen();
    }
    window.clear();
}







