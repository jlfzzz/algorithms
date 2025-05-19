#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

class Solution {
public:
    int rob(vector<int> &nums) {
        int n = nums.size();
        vector<int> f(n + 2);
        for (int i = 2; i < n + 2; i++) {
            f[i] = max(f[i - 1], f[i - 2] + nums[i - 2]);
        }
        return f[n + 1];
    }
};


class Solution {
public:
    int rob(vector<int> &nums) {
        int n = nums.size();
        vector<int> memo(n, -1); // -1 表示没有计算过
        // dfs(i) 表示从 nums[0] 到 nums[i] 最多能偷多少
        auto dfs = [&](this auto &&dfs, int i) -> int {
            if (i < 0) { // 递归边界（没有房子）
                return 0;
            }
            if (memo[i] != -1) { // 之前计算过
                return memo[i];
            }
            return memo[i] = max(dfs(i - 1), dfs(i - 2) + nums[i]);
            };
        return dfs(n - 1); // 从最后一个房子开始思考
    }
};
