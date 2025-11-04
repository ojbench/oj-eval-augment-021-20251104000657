#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <set>
#include "game.h"

using namespace std;

// Strategy: Use a greedy approach to hit bricks efficiently
// Try to maximize score while minimizing operations

class Solver {
private:
    Game* game;
    int n, m, s;
    vector<char> operations;
    
    // Try different operations and choose the best one
    char chooseBestOperation() {
        vector<char> ops = {'A', 'B', 'C', 'D', 'E'};
        char bestOp = 'C';
        int bestReward = -1;
        int bestBricksHit = -1;
        
        // Try each operation and see which gives best immediate reward
        for (char op : ops) {
            Game::Save* save = game->save();
            int oldHits = game->bricksHit();
            int reward = game->play(op);
            int newHits = game->bricksHit();
            int bricksHit = newHits - oldHits;
            
            // Prefer operations that hit more bricks, then higher reward
            if (bricksHit > bestBricksHit || 
                (bricksHit == bestBricksHit && reward > bestReward)) {
                bestOp = op;
                bestReward = reward;
                bestBricksHit = bricksHit;
            }
            
            game->load(save);
            game->erase(save);
        }
        
        return bestOp;
    }
    
public:
    Solver(Game* g, int n_val, int m_val, int s_val) 
        : game(g), n(n_val), m(m_val), s(s_val) {}
    
    void solve() {
        int totalBricks = game->bricksTotal();
        int maxOps = m;

        // Keep playing until all bricks are hit or we reach max operations
        while (game->bricksRemaining() > 0 && (int)operations.size() < maxOps) {
            char op = chooseBestOperation();
            game->play(op);
            operations.push_back(op);

            // Safety check - if we're not making progress, try different strategy
            if ((int)operations.size() > maxOps / 2 &&
                game->bricksHit() < totalBricks / 4) {
                // Try more aggressive moves
                if (operations.size() % 2 == 0) {
                    op = 'A';
                } else {
                    op = 'E';
                }
                game->play(op);
                operations.push_back(op);
            }
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

