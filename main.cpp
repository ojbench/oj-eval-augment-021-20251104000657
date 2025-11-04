#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <set>
#include <random>
#include "game.h"

using namespace std;

// Strategy: Use an improved pattern that covers the board more effectively
// Focus on creating diverse trajectories

class Solver {
private:
    Game* game;
    int n, m, s;
    vector<char> operations;
    mt19937 rng;

    // Improved pattern that creates more diverse ball trajectories
    char chooseOperation(int step) {
        // Use a longer, more varied pattern
        // The key is to create different angles to hit different parts of the board
        int cycle = step % 40;

        // Phase 1: Strong left sweep
        if (cycle < 5) return 'A';
        // Phase 2: Gradual return to center
        if (cycle < 10) return 'D';
        // Phase 3: Strong right sweep
        if (cycle < 15) return 'E';
        // Phase 4: Gradual return to center
        if (cycle < 20) return 'B';
        // Phase 5: Moderate left
        if (cycle < 25) return 'B';
        // Phase 6: Center
        if (cycle < 27) return 'C';
        // Phase 7: Moderate right
        if (cycle < 32) return 'D';
        // Phase 8: Center
        if (cycle < 34) return 'C';
        // Phase 9: Mix
        if (cycle < 37) return (cycle % 2 == 0) ? 'A' : 'E';
        // Phase 10: Center stabilize
        return 'C';
    }

public:
    Solver(Game* g, int n_val, int m_val, int s_val)
        : game(g), n(n_val), m(m_val), s(s_val), rng(42) {}

    void solve() {
        int maxOps = min(m, 16 * n * n);

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

