#include <iostream>
#include <unordered_set>
#include <ctime>

#include "piece.hpp"
#include "board.hpp"

using namespace std;

clock_t startTime;
clock_t endTime;
long long currNodes = 0;
long long totalNodes = 0;
bool solutionFound = false;

// Used for testing pieces
void printPieces(vector<Piece*>& allPieces) {
    int xOrig = 2;
    int yOrig = 0;
    int index = 0;
    
    for (Piece* piece : allPieces) {
        cout << "Piece: " << piece->representation << endl << endl;
        vector<vector<char>> matrix = {
            {'-', '-', '-', '-', '-', '-'},
            {'-', '-', '-', '-', '-', '-'},
            {'-', '-', '-', '-', '-', '-'},
            {'-', '-', '-', '-', '-', '-'},
        };

        for (vector<int> coord : piece->offsets) {
            matrix[yOrig + coord[1]][xOrig + coord[0]] = piece->representation;
        }

        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[0].size(); j++) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    index++;
}

void solve(int x, int y, vector<Piece*>& unused, int numRemaining, Board* board) {
    currNodes++;

    // All pieces placed & solution has been found
    if (numRemaining == 0) {
        endTime = clock();
        double runtime = (double) (endTime - startTime) / CLOCKS_PER_SEC * 1000.0;
        totalNodes = currNodes;

        board->print();
        cout << "Runtime: " << runtime << " ms" << endl;
        cout << "Nodes: " << totalNodes << endl;
        solutionFound = true;

        return;
    }

    // Invalid coordinates (out of bounds)
    if (x == -1 && y == -1) {
        return;
    }

    // Try all pieces in current position
    for (int i = 0; i < unused.size(); i++) {
        if (unused[i] == nullptr) { // piece already used
            continue;
        }
        if (board->placePiece(x, y, unused[i])) { // place piece if possible
            Piece* currPiece = unused[i];
            unused[i] = nullptr;

            vector<int> nextCoord = board->nextCoord(x, y);
            solve(nextCoord[0], nextCoord[1], unused, numRemaining - 1, board);

            unused[i] = currPiece;
            board->removePiece(x, y, unused[i]);
        }
    }
    return;
}

int main() {
    Board* board = new Board();
    
    Piece* darkred = new Piece('1', {{0, 0}, {0, 1}, {1, 1}});
    Piece* red = new Piece('2', {{0, 0}, {0, 1}, {1, 1}, {1, 2}, {2, 2}});
    Piece* medblue = new Piece('3', {{0, 0}, {1, 0}, {0, 1}, {0, 2}, {1, 2}});
    Piece* green = new Piece('4', {{0, 0}, {0, 1}, {1, 1}, {0, 2}, {0, 3}});
    Piece* purple = new Piece('5', {{0, 0}, {1, 0}, {2, 0}, {0, 1}, {0, 2}});
    Piece* lightblue = new Piece('6', {{0, 0}, {0, 1}, {1, 1}, {2, 1}, {1, 0}});
    Piece* white = new Piece('7', {{0, 0}, {0, 1}, {-1, 1}, {1, 1}, {0, 2}});
    Piece* yellow = new Piece('8', {{0, 0}, {1, 0}, {2, 0}, {3, 0}});
    Piece* pink = new Piece('9', {{0, 0}, {1, 0}, {1, 1}, {0, 1}});
    Piece* darkblue = new Piece('A', {{0, 0}, {0, 1}, {0, 2}, {1, 2}, {1, 3}});
    Piece* orange = new Piece('B', {{0, 0}, {0, 1}, {0, 2}, {1, 2}});
    Piece* lightgreen = new Piece('C', {{0, 0}, {0, 1}, {1, 1}, {2, 1}, {3, 1}});

    vector<Piece*> allPieces = {darkred, red, medblue, green, purple, lightblue, white, yellow, pink, darkblue, orange, lightgreen};

    startTime = clock();
    solve(0, 0, allPieces, allPieces.size(), board);

    if (!solutionFound) {
        cout << "No Solution Found." << endl;
    }

    return 0;
}