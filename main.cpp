#include "Game.h"

int main() {

    Game game;
    while(game.isWindowOpen()){
        game.play();
    }



    return 0;
}
