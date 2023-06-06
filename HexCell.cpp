#include "HexCell.h"

//0 empty 1 red 2 blue 3 blocked
HexCell::HexCell(int q, int r) : q(q), r(r), state(0) {}
HexCell::HexCell() : q(-10), r(-10), state(3) {}





int HexCell::getQ() const {
    return q;
}

int HexCell::getR() const {
    return r;
}

int HexCell::getState() const {
    return state;
}

void HexCell::setState(int state) {
    this->state = state;
}

