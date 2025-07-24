#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <unordered_set>
#include <cmath>   
#include <memory> 
#include <map>

using namespace std;

class Solution {
public:
    int minimumMountainRemovals(vector<int> &nums) {
        int n = nums.size();
        vector<int> left2Right(n, 1), right2Left(n, 1), temp;

        for (int i = 0; i < n; i++) {
            int x = nums[i];
            auto it = ranges::lower_bound(temp, x);
            if (it == temp.end()) {
                temp.emplace_back(x);
            } else {
                *it = x;
            }
            left2Right[i] = temp.size();
        }

        temp.clear();
        for (int i = n - 1; i >= 0; i--) {
            int x = nums[i];
            auto it = ranges::lower_bound(temp, x);
            if (it == temp.end()) {
                temp.emplace_back(x);
            } else {
                *it = x;
            }
            right2Left[i] = temp.size();
        }

        int ans = 100000;
        for (int i = 1; i < n - 1; i++) {
            if (left2Right[i] > 1 && right2Left[i] > 1) {
                ans = min(ans, i + 1 - left2Right[i] + n - i + 1 - right2Left[i] - 1);
                //minRemovals = min(minRemovals, n - (leftLIS[i] + rightLIS[i] - 1)); 也可以
            }
        }
        return ans;
    }
};

class Solution {
public:
    int minimumMountainRemovals(vector<int> &nums) {
        int n = nums.size();

        // 计算每个位置结尾的最长递增子序列长度
        vector<int> lis(n, 1);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[j] < nums[i]) {
                    lis[i] = max(lis[i], lis[j] + 1);
                }
            }
        }

        // 计算每个位置开头的最长递减子序列长度
        vector<int> lds(n, 1);
        for (int i = n - 1; i >= 0; i--) {
            for (int j = n - 1; j > i; j--) {
                if (nums[j] < nums[i]) {
                    lds[i] = max(lds[i], lds[j] + 1);
                }
            }
        }

        // 找到最长的山形子序列
        int maxLen = 0;
        for (int i = 0; i < n; i++) {
            // 峰值必须同时有递增部分和递减部分
            if (lis[i] > 1 && lds[i] > 1) {
                maxLen = max(maxLen, lis[i] + lds[i] - 1); // -1是因为峰值被计算了两次
            }
        }

        // 最小删除次数 = 总长度 - 最长山形子序列长度
        return n - maxLen;
    }
};