#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <set>
#include <random>
#include "game.h"

using namespace std;

// Strategy: Use a smarter greedy approach with limited lookahead
// Sample a few operations and choose the best one

class Solver {
private:
    Game* game;
    int n, m, s;
    vector<char> operations;
    mt19937 rng;

    // Try a subset of operations and choose the best
    char chooseBestOperation(int step) {
        vector<char> ops = {'A', 'B', 'C', 'D', 'E'};

        // For small n, try all operations
        if (n <= 50) {
            char bestOp = 'C';
            int bestScore = -1;

            for (char op : ops) {
                Game::Save* save = game->save();
                int oldHits = game->bricksHit();
                int reward = game->play(op);
                int newHits = game->bricksHit();
                int score = (newHits - oldHits) * 1000 + reward;

                if (score > bestScore) {
                    bestScore = score;
                    bestOp = op;
                }

                game->load(save);
                game->erase(save);
            }
            return bestOp;
        }

        // For large n, use pattern with occasional sampling
        if (step % 10 == 0) {
            // Sample 3 random operations
            vector<char> sample = {'C', 'B', 'D'};
            char bestOp = 'C';
            int bestScore = -1;

            for (char op : sample) {
                Game::Save* save = game->save();
                int oldHits = game->bricksHit();
                int reward = game->play(op);
                int newHits = game->bricksHit();
                int score = (newHits - oldHits) * 1000 + reward;

                if (score > bestScore) {
                    bestScore = score;
                    bestOp = op;
                }

                game->load(save);
                game->erase(save);
            }
            return bestOp;
        }

        // Use pattern
        int cycle = step % 20;
        if (cycle < 4) return 'A';
        else if (cycle < 8) return 'E';
        else if (cycle < 12) return 'B';
        else if (cycle < 16) return 'D';
        else return 'C';
    }

public:
    Solver(Game* g, int n_val, int m_val, int s_val)
        : game(g), n(n_val), m(m_val), s(s_val), rng(42) {}

    void solve() {
        int maxOps = min(m, 16 * n * n);

        for (int step = 0; step < maxOps && game->bricksRemaining() > 0; step++) {
            char op = chooseBestOperation(step);
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

