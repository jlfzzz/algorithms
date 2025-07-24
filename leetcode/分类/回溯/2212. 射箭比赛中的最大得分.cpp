#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<int> maximumBobPoints(int numArrows, vector<int> &aliceArrows) {
        int maxScore = 0;
        vector<int> best(12, 0);

        for (int mask = 0; mask < (1 << 12); ++mask) {
            int arrowsUsed = 0;
            int score = 0;
            vector<int> bob(12, 0);

            // 计算当前 mask 的得分和箭数
            for (int i = 0; i < 12; ++i) {
                if (mask & (1 << i)) {
                    int need = aliceArrows[i] + 1;
                    arrowsUsed += need;
                    bob[i] = need;
                    score += i;
                }
            }

            if (arrowsUsed > numArrows) continue;

            // 分配剩余箭到任意区域，比如 0
            bob[0] += numArrows - arrowsUsed;

            // 更新最优结果
            if (score > maxScore) {
                maxScore = score;
                best = bob;
            }
        }

        return best;
    }
};
