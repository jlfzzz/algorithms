#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int> &nums) {
        ranges::sort(nums);
        int n = nums.size();
        vector<int> memo(n), from_(n, -1);

        auto dfs = [&](this auto &&dfs, int i) -> int {
            int &res = memo[i]; // 注意这里是引用
            if (res) { // 之前计算过
                return res;
            }
            for (int j = 0; j < i; j++) {
                if (nums[i] % nums[j]) {
                    continue;
                }
                int f = dfs(j);
                if (f > res) {
                    res = f;
                    from_[i] = j; // 记录最佳转移来源
                }
            }
            res++; // 加上 nums[i] 自己
            return res;
            };

        int max_f = 0, max_i = 0;
        for (int i = 0; i < n; i++) {
            int f = dfs(i);
            if (f > max_f) {
                max_f = f;
                max_i = i; // 最长合法子序列的最后一个数的下标
            }
        }

        vector<int> path;
        for (int i = max_i; i >= 0; i = from_[i]) {
            path.push_back(nums[i]);
        }
        return path; // 不需要 reverse，任意顺序返回均可
    }
};
