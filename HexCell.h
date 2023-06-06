#ifndef HEXXAGON_HEXCELL_H
#define HEXXAGON_HEXCELL_H
#include <vector>


class HexCell {
    int q;
    int r;
    // 0 empty 1 red 2 blue 3 blocked
    int state;
public:

    HexCell(int q, int r);
    HexCell();

    bool operator==( const HexCell other) const {
        return (q == other.q && r == other.r );
    };


    int getQ() const;

    int getR() const;

    int getState() const;

    void setState(int state);



};


#endif //HEXXAGON_HEXCELL_H
