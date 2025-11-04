#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <set>
#include <random>
#include "game.h"

using namespace std;

// Strategy: Adaptive pattern-based approach
// Use multiple pattern phases and adapt based on progress

class Solver {
private:
    Game* game;
    int n, m, s;
    vector<char> operations;
    mt19937 rng;
    int lastCheckHits;
    int stuckCounter;

    // Multiple pattern strategies
    char getPattern1(int cycle) {
        // Wide sweeping pattern
        if (cycle < 3) return 'A';
        if (cycle < 6) return 'E';
        if (cycle < 9) return 'B';
        if (cycle < 12) return 'D';
        if (cycle < 14) return 'C';
        return 'C';
    }

    char getPattern2(int cycle) {
        // Aggressive zigzag
        if (cycle < 2) return 'A';
        if (cycle < 4) return 'E';
        if (cycle < 6) return 'A';
        if (cycle < 8) return 'E';
        if (cycle < 10) return 'C';
        return 'C';
    }

    char getPattern3(int cycle) {
        // Gradual sweep
        if (cycle < 5) return 'B';
        if (cycle < 10) return 'D';
        if (cycle < 15) return 'B';
        if (cycle < 20) return 'D';
        return 'C';
    }

    char chooseOperation(int step) {
        // Check progress every 100 steps
        if (step % 100 == 0 && step > 0) {
            int currentHits = game->bricksHit();
            if (currentHits == lastCheckHits) {
                stuckCounter++;
            } else {
                stuckCounter = 0;
            }
            lastCheckHits = currentHits;
        }

        // Choose pattern based on progress and step
        int patternPhase = (step / 200) % 3;
        int cycle = step % 20;

        if (stuckCounter > 2) {
            // If stuck, try more aggressive pattern
            return getPattern2(cycle % 10);
        } else if (patternPhase == 0) {
            return getPattern1(cycle % 15);
        } else if (patternPhase == 1) {
            return getPattern2(cycle % 10);
        } else {
            return getPattern3(cycle % 20);
        }
    }

public:
    Solver(Game* g, int n_val, int m_val, int s_val)
        : game(g), n(n_val), m(m_val), s(s_val), rng(42),
          lastCheckHits(0), stuckCounter(0) {}

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

