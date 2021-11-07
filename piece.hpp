#ifndef PIECE_HPP
#define PIECE_HPP

#include <vector>

using namespace std;

class Piece {
    public:
        Piece() {
            offsets = {{0, 0}};
        }
        Piece(char representation, vector<vector<int>> offsets) : representation(representation), offsets(offsets) {}
        vector<vector<int>> offsets;
        char representation;
};

#endif