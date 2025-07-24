#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <map>

using namespace std;

class Solution {
public:
    int deleteAndEarn(vector<int> &nums) {
        map<int, int> all;
        for (int x : nums) {
            all[x]++;
        }

        vector<int> dp(all.size() + 2, 0);
        int i = 2;
        int prev = -1;
        for (auto &p : all) {
            if (p.first - prev == 1) {
                dp[i] = max(dp[i - 2] + p.first * p.second, dp[i - 1]);
            } else {
                dp[i] = dp[i - 1] + p.first * p.second;
                //dp[i] = max(dp[i - 2] + p.first * p.second, dp[i - 1] + p.first * p.second);
            }

            prev = p.first;
            i++;
        }
        return dp[all.size() + 1];
    }
};

class Solution {
public:
    int deleteAndEarn(vector<int> &nums) {
        int maxElement = ranges::max(nums);
        vector<int> dp(maxElement + 1, 0);
        unordered_map<int, int> map;

        for (int x : nums) {
            map[x]++;
        }

        dp[0] = 0;
        dp[1] = map[1];
        for (int i = 2; i <= maxElement; i++) {
            dp[i] = max(dp[i - 1], dp[i - 2] + i * map[i]);
        }
        return dp[maxElement];
    }
};



class Solution {
public:
    int deleteAndEarn(vector<int> &nums) {
        const int MAX_NUM = 10001;
        vector<int> count(MAX_NUM, 0);

        // 第一步：统计每个数出现的频率
        for (int num : nums) {
            count[num]++;
        }

        // 第二步：动态规划数组 dp[i] 表示处理到数字 i 时能获得的最大点数
        vector<int> dp(MAX_NUM, 0);
        dp[0] = 0;
        dp[1] = count[1] * 1;

        for (int i = 2; i < MAX_NUM; ++i) {
            // 两种选择：选 i（不能选 i-1） or 不选 i（保留 dp[i-1]）
            dp[i] = max(dp[i - 1], dp[i - 2] + count[i] * i);
        }

        // 第三步：返回处理到最大数字时的最大得分
        return dp[MAX_NUM - 1];
    }
};
