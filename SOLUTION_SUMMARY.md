# Solution Summary for Problem 021 - Snooker Brick Out!

## Problem Overview
This is a brick-out game simulation where we need to control a ball to hit bricks efficiently. The score consists of:
- 90% game score (based on bricks hit and combo bonuses)
- 10% control efficiency score (fewer operations is better)

## Submission History

### Submission 1 (707276) - Score: 214,280 / 1,000,000 (21.4%)
- **Approach**: Greedy algorithm trying all 5 operations at each step
- **Result**: Time Limit Exceeded on large test cases (5, 9, 10)
- **Issue**: Too slow due to save/load operations for each decision

### Submission 2 (707279) - Score: 290,644 / 1,000,000 (29.1%)
- **Approach**: Simple pattern-based approach with 20-step cycle
- **Result**: All test cases pass, no TLE
- **Pattern**: A(4) → E(4) → B(4) → D(4) → C(4)
- **Improvement**: Fast execution, reasonable coverage

### Submission 3 (707282) - Score: 186,466 / 1,000,000 (18.6%)
- **Approach**: Hybrid - greedy for small n, pattern for large n
- **Result**: Time Limit Exceeded on large test cases (5, 8, 9, 10)
- **Issue**: Greedy approach still too slow even with sampling

### Submission 4 (707284) - Score: 291,845 / 1,000,000 (29.2%) ⭐ BEST
- **Approach**: Improved pattern with 40-step cycle
- **Result**: All test cases pass, best score achieved
- **Pattern**: More varied trajectory with longer cycle
  - Strong left sweep (A×5)
  - Gradual return (D×5)
  - Strong right sweep (E×5)
  - Gradual return (B×5)
  - Moderate movements and center stabilization
- **Key Success Factor**: Longer cycle creates more diverse ball trajectories

### Submission 5 (707287) - Score: 290,100 / 1,000,000 (29.0%)
- **Approach**: Adaptive multi-pattern with progress tracking
- **Result**: All test cases pass, slightly worse than submission 4
- **Features**: 
  - Three different patterns
  - Progress tracking every 100 steps
  - Pattern switching based on progress
- **Issue**: Added complexity didn't improve results

## Best Solution Analysis

The best solution (Submission 4, commit eaed574) uses a simple but effective pattern-based approach:

### Key Insights:
1. **Speed is Critical**: For large test cases (n=1000), greedy approaches with save/load are too slow
2. **Pattern Length Matters**: A 40-step cycle provides better coverage than a 20-step cycle
3. **Trajectory Diversity**: Creating varied ball angles helps hit more bricks
4. **Simplicity Wins**: Complex adaptive strategies don't necessarily improve results

### Performance by Test Case:
- Test 1 (n=10): 25.6% (400 reward, 43 ops)
- Test 2 (n=10): 48.1% (400 reward, 43 ops) - Best performance
- Test 3 (n=20): 26.5% (1650 reward, 127 ops)
- Test 4 (n=50): 27.3% (10200 reward, 255 ops)
- Test 5 (n=1000): 27.5% (164750 reward, 3871 ops)
- Test 6-10: Similar performance around 27%

### Limitations:
- Only hitting ~20% of bricks on average (except test 2 with 44%)
- No adaptation to actual game state
- No targeting of specific brick patterns
- No optimization for colored brick combos

## Potential Improvements (Not Implemented Due to Submission Limit)

1. **Monte Carlo Tree Search**: Could explore multiple trajectories but would need careful optimization
2. **Reinforcement Learning**: Pre-trained model could learn better patterns
3. **Brick Density Analysis**: Adjust pattern based on remaining brick distribution
4. **Combo Optimization**: Specifically target colored brick sequences for 50-point bonuses
5. **Velocity Management**: More sophisticated control of horizontal velocity accumulation

## Conclusion

The best achievable score with the implemented approaches is **291,845 / 1,000,000 (29.2%)**.

This represents a reasonable solution given the constraints:
- Fast execution (no TLE)
- Simple and maintainable code
- Consistent performance across all test cases
- Room for improvement with more sophisticated algorithms

The problem is challenging because:
- The game physics are complex
- Optimal control requires long-term planning
- The search space is exponential
- Time constraints prevent exhaustive search

A pattern-based approach provides a good balance between performance and execution speed.

