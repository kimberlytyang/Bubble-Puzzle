#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <iostream>

#include "piece.hpp"

using namespace std;

class Board {
    public:
        vector<vector<char>> board = {
            {'-'},
            {'-', '-'},
            {'-', '-', '-'},
            {'-', '-', '-', '-'},
            {'-', '-', '-', '-', '-'},
            {'-', '-', '-', '-', '-', '-'},
            {'-', '-', '-', '-', '-', '-', '-'},
            {'-', '-', '-', '-', '-', '-', '-', '-'},
            {'-', '-', '-', '-', '-', '-', '-', '-', '-'},
            {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        };

        // Prints the current board
        void print() {
            for (int i = 0; i < board.size(); i++) {
                for (int j = 0; j < board[i].size(); j++) {
                    cout << board[i][j] << " ";
                }
                cout << endl;
            }
        }

        // Returns true if coordinate (x, y) is on the board and vacant
        bool isValidCoord(int x, int y) {
            if (y >= board.size() || x >= board[y].size() || board[y][x] != '-') {
                return false;
            }
            return true;
        }

        // Finds next open coordinate from left to right & top to bottom
        vector<int> nextCoord(int x, int y) {
            for (int i = y; i < board.size(); i++) {
                for (int j = (i == y) ? x + 1 : 0; j < board[i].size(); j++) {
                    if (board[i][j] == '-') {
                        return {j, i};
                    }
                }
            }
            return {-1, -1};
        }

        // Attempts to place a piece and returns true if piece is placed successfully
        bool placePiece(int x, int y, Piece* piece) {
            for (vector<int> coord : piece->offsets) {
                if (!isValidCoord(x + coord[0], y + coord[1])) {
                    return false;
                }
            }
            for (vector<int> coord : piece->offsets) {
                board[y + coord[1]][x + coord[0]] = piece->representation;
            }
            return true;
        }

        // Clears out the placement of a piece
        void removePiece(int x, int y, Piece* piece) {
            for (vector<int> coord : piece->offsets) {
                board[y + coord[1]][x + coord[0]] = '-';
            }
        }
};

#endif