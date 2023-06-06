#include "GUI.h"
#include <SFML/Graphics.hpp>
#include "Board.h"
#include <iostream>

GUI::GUI(sf::RenderWindow& window, Board& board) : window(window), board(board), hexagonSize (80.f), showingDestinations(false){
    //load the textures
    if(!redHexagon.loadFromFile("/Users/jasczajka/CLionProjects/hexxagon/Textures/red_hexagon.png")){
        window.close();
    }
    if(!redHexagonHighlighted.loadFromFile("/Users/jasczajka/CLionProjects/hexxagon/Textures/red_hexagon_highlighted.png")){
        window.close();
    }
    if(!blueHexagon.loadFromFile("/Users/jasczajka/CLionProjects/hexxagon/Textures/blue_hexagon.png")){
        window.close();
    }
    if(!blueHexagonHighlighted.loadFromFile("/Users/jasczajka/CLionProjects/hexxagon/Textures/blue_hexagon_highlighted.png")){
        window.close();
    }
    if(!emptyHexagon.loadFromFile("/Users/jasczajka/CLionProjects/hexxagon/Textures/empty_hexagon.png")){
        window.close();
    }
    if(!emptyHexagonRange1.loadFromFile("/Users/jasczajka/CLionProjects/hexxagon/Textures/empty_hexagon_range1.png")){
        window.close();
    }
    if(!emptyHexagonRange2.loadFromFile("/Users/jasczajka/CLionProjects/hexxagon/Textures/empty_hexagon_range2.png")){
        window.close();
    }
    std::map<std::pair<int, int>, sf::Sprite> map = this->hexagonMap;
    //load the font
    if(!font.loadFromFile("/Users/jasczajka/CLionProjects/hexxagon/Textures/pixelFont.ttf")){
        std::cout<<"failed to load font";
    }
    //set colors matching to the textures
    redColor = sf::Color(183,77,110);
    blueColor = sf::Color(109,114,183);
}
std::pair<bool, bool> GUI::displayStartingScreen() {
    window.clear();

    sf::Text newGamePlayer("New game with player", font, 60);
    newGamePlayer.setFillColor(redColor);
    sf::FloatRect newGamePlayerButtonBounds = newGamePlayer.getLocalBounds();

    newGamePlayer.setOrigin(newGamePlayerButtonBounds.width / 2.f, newGamePlayerButtonBounds.height / 20.f);
    newGamePlayer.setPosition(window.getSize().x / 2.f, window.getSize().y / 4.f);

    sf::Text newGamePC("New game with computer", font, 60);
    newGamePC.setFillColor(redColor);
    sf::FloatRect newGamePCBounds = newGamePC.getLocalBounds();

    newGamePC.setOrigin(newGamePCBounds.width / 2.f, newGamePCBounds.height / 2.f);
    newGamePC.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);

    sf::FloatRect newGamePCGlobalBounds = newGamePC.getGlobalBounds();
    sf::FloatRect newGamePlayerButtonGlobalBounds = newGamePlayer.getGlobalBounds();

    window.draw(newGamePlayer);
    window.draw(newGamePC);
    window.display();

    sf::Event event;
    while(window.isOpen()) {
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed: {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        if (newGamePlayerButtonGlobalBounds.contains(mousePosition.x, mousePosition.y)) {
                            return std::make_pair(true, false);
                        }
                        if (newGamePCGlobalBounds.contains(mousePosition.x, mousePosition.y)) {
                            return std::make_pair(true, true);
                        }
                    }
                }
                    break;
                default:
                    return std::make_pair(false, false);
            }
        }
    }
    return std::make_pair(false, false);
}
 void GUI::renderBoard(){

    window.clear();
     const float sqrt3 = sqrt(3.f);


     sf::Texture texture;
     sf::Sprite hexagon;

        // Center the grid on the screen
        float startX = window.getSize().x/2.f;
        float startY = window.getSize().y/2.f;

        hexagonMap.clear();
        for(auto& column : board.getCells()){
            for(auto& cell : column){
                float x = startX + hexagonSize * (cell.getQ());
                //distance between 2 hexagons on the y axis -> +s-r
                float y = startY + hexagonSize*sqrt3/3* (cell.getQ() + 2*cell.getR());
                sf::Vector2f position(x, y);
                if(cell.getState()!=3) {
                    if (cell.getState() == 0) {
                        hexagon.setTexture(emptyHexagon);
                    } else if (cell.getState() == 1) {
                        hexagon.setTexture(redHexagon);
                    } else if (cell.getState() == 2) {
                        hexagon.setTexture(blueHexagon);
                    }
                    hexagon.setPosition(position);
                    // Scale the sprite to match the hexagon size and add it to the vector of hexagon sprites
                    hexagon.setScale(hexagonSize / redHexagon.getSize().x, hexagonSize / redHexagon.getSize().y);
                    hexagonMap[std::make_pair(cell.getQ(), cell.getR())] = hexagon;
                }

            }
        }
        for(auto& entry : hexagonMap){
            window.draw(entry.second);
        }
        drawScores();

        window.display();

}
void GUI::drawScores(){
    sf::Text redScoreText("Score:" + std::to_string(board.getScoreOfPlayer(1)),font,60);
    redScoreText.setFillColor(redColor);
    redScoreText.setPosition(window.getSize().x/4.f,window.getSize().y/4.f);
    window.draw(redScoreText);
    sf::Text blueScoreText("Score:" + std::to_string(board.getScoreOfPlayer(2)),font,60);
    blueScoreText.setFillColor(blueColor);
    blueScoreText.setPosition(window.getSize().x*63/100.f, window.getSize().y/4.f);
    window.draw(blueScoreText);

}

bool GUI::displayGameOverScreen() {

    sf::Text gameOverText("Game over!", font, 60);
    gameOverText.setFillColor(board.getMovablePieces(1).size() > board.getMovablePieces(2).size() ? redColor : blueColor);
    sf::FloatRect gameOverTextRect = gameOverText.getLocalBounds();
    gameOverText.setOrigin(gameOverTextRect.left + gameOverTextRect.width / 2.0f,
                           gameOverTextRect.top + gameOverTextRect.height / 2.0f);
    gameOverText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 8.0f);

    sf::Text newGameText("New game", font, 60);
    newGameText.setFillColor(board.getMovablePieces(1).size() > board.getMovablePieces(2).size() ? redColor : blueColor);
    sf::FloatRect newGameTextRect = newGameText.getLocalBounds();
    newGameText.setOrigin(newGameTextRect.left + newGameTextRect.width / 2.0f,
                           newGameTextRect.top + newGameTextRect.height / 2.0f);
    newGameText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 5.0f);
    sf::FloatRect newGameTextGlobalBounds = newGameText.getGlobalBounds();


    window.clear();
    renderBoard();
    window.draw(gameOverText);
    window.draw(newGameText);
    window.display();
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed: {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        if (newGameTextGlobalBounds.contains(mousePosition.x, mousePosition.y)) {
                            window.clear();
                            return false;
                        }
                    }
                }
                default:
                    break;
            }
        }

    }
}

void GUI::handleGameEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonPressed:
                if(event.mouseButton.button == sf::Mouse::Left) {
                    //if we're during a move
                    if (showingDestinations) {
                        destinationCell = getSelectedCell();
                        if (destinationCell == selectedCell) {
                            //cancel the move
                            showingDestinations = false;
                            renderBoard();
                        }

                        else if (board.isCellWithinBoard(destinationCell.getQ(), destinationCell.getR())) {


                            HexCell &movableSourceCell = board.getCell(selectedCell.getQ(),
                                                                       selectedCell.getR());
                            HexCell &movableDestinationCell = board.getCell(destinationCell.getQ(),
                                                                            destinationCell.getR());
                            //if its a valid move - make it
                            if(board.makePlayerMove( movableSourceCell,movableDestinationCell)) {
                                showingDestinations = false;
                            }
                            renderBoard();
                        }
                    }
                    else{
                        selectedCell = getSelectedCell();
                        if((selectedCell.getState() == board.getCurrentPlayer()) && (std::find(board.getMovablePieces(board.getCurrentPlayer()).begin(),board.getMovablePieces(board.getCurrentPlayer()).end(),selectedCell) != board.getMovablePieces(board.getCurrentPlayer()).end())){
                            showAvailableDestinations();
                            showingDestinations = true;
                        }
                    }
                }
                break;
            default:
                break;
        }
    }
}
HexCell GUI::getSelectedCell() {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

    for (const auto& entry : hexagonMap) {
        sf::FloatRect bounds = entry.second.getGlobalBounds();

        if (bounds.contains(mousePosition.x, mousePosition.y)) {

            int q = entry.first.first;
            int r = entry.first.second;


            std::cout<<"q: "<<q<<"r: "<<r<<"\n";
            if(board.isCellWithinBoard(q,r)) {
                std::cout<<"state "<<board.getCell(q,r).getState()<<"\n";
                return board.getCell(q, r);
            }
        }
    }
    //returns invalid cell if no valid was selected
    return HexCell();
}

void GUI::showAvailableDestinations(){
    const float sqrt3 = sqrt(3.f);



    sf::Texture texture;
    sf::Sprite hexagon;

    float startX = window.getSize().x/2;
    float startY = window.getSize().y/2;

    auto availableRangeOne = board.getAvailableDestPiecesInRangeOne(selectedCell);
    auto availableRangeTwo = board.getAvailableDestPiecesInRangeTwo(selectedCell);


    for(auto& column : board.getCells()){
        for(auto& cell : column){
            float x = startX + hexagonSize * (cell.getQ());
            float y = startY + hexagonSize * sqrt3/3 * (cell.getQ() + 2*cell.getR());
            sf::Vector2f position(x, y);

            if(std::find(availableRangeOne.begin(), availableRangeOne.end(), cell) != availableRangeOne.end()){
                hexagon.setTexture(emptyHexagonRange1);
            } else if(std::find(availableRangeTwo.begin(), availableRangeTwo.end(), cell) != availableRangeTwo.end()){
                hexagon.setTexture(emptyHexagonRange2);
            } else{
                continue;
            }

            hexagon.setPosition(position);
            hexagon.setScale(hexagonSize / emptyHexagonRange1.getSize().x, hexagonSize / emptyHexagonRange1.getSize().y);
            hexagonMap[std::make_pair(cell.getQ(), cell.getR())] = hexagon;
        }
    }
    hexagonMap[std::make_pair(selectedCell.getQ(),selectedCell.getR())].setTexture(selectedCell.getState()==1? redHexagonHighlighted:blueHexagonHighlighted);
    window.clear();
    for(auto& hexagonEntry : hexagonMap){
        window.draw(hexagonEntry.second);
    }
    drawScores();

    window.display();
}


