#include <cmath>

class Solution {
public:
    int poorPigs(int buckets, int minutesToDie, int minutesToTest) {
        if (buckets == 1) return 0;

        int T = minutesToTest / minutesToDie;
        // 计算 x = ceil(log(buckets) / log(T + 1))
        return ceil(log(buckets) / log(T + 1));
    }
};