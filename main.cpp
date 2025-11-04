#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <set>
#include <random>
#include "game.h"

using namespace std;

// Strategy: Use a simple pattern-based approach
// Alternate between different operations to cover the board

class Solver {
private:
    Game* game;
    int n, m, s;
    vector<char> operations;
    mt19937 rng;

    // Simple heuristic: try to sweep the board systematically
    char chooseOperation(int step) {
        // Pattern: sweep left and right to cover the board
        int cycle = step % 20;

        if (cycle < 4) return 'A';      // Move left
        else if (cycle < 8) return 'E'; // Move right
        else if (cycle < 12) return 'B'; // Move left slowly
        else if (cycle < 16) return 'D'; // Move right slowly
        else return 'C';                 // Stay center
    }

public:
    Solver(Game* g, int n_val, int m_val, int s_val)
        : game(g), n(n_val), m(m_val), s(s_val), rng(42) {}

    void solve() {
        int maxOps = min(m, 16 * n * n); // Limit operations

        // Simple pattern-based approach
        for (int step = 0; step < maxOps && game->bricksRemaining() > 0; step++) {
            char op = chooseOperation(step);
            game->play(op);
            operations.push_back(op);
        }
    }
    
    void printSolution() {
        for (char op : operations) {
            cout << op << endl;
        }
    }
};

int main() {
    // Create game instance with cin - it will read all input
    Game* game = new Game(cin);

    // Get parameters from game
    int n = game->n;
    int m = game->m;
    int s = game->s;

    // Solve
    Solver solver(game, n, m, s);
    solver.solve();
    solver.printSolution();

    delete game;
    return 0;
}

