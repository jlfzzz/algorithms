#include <bits/stdc++.h>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> smallestSubarrays(vector<int> &nums) {
        int n = nums.size();
        vector<int> ans(n, 0);

        for (int i = 0; i < n; i++) {
            ans[i] = 1;
            int x = nums[i];
            for (int j = i - 1; j >= 0; j--) {
                if ((nums[j] | x) == nums[j]) {
                    break;
                }
                nums[j] |= x;
                ans[j] = i - j + 1;
            }
        }
        return ans;
    }
};

class Solution2 {
public:
    vector<int> smallestSubarrays(vector<int> &nums) {
        int n = nums.size();
        vector<int> ans(n);
        vector<pair<int, int>> ors; // 按位或的值 + 对应子数组的右端点的最小值
        for (int i = n - 1; i >= 0; --i) {
            ors.emplace_back(0, i);
            ors[0].first |= nums[i];
            int k = 0;
            for (int j = 1; j < ors.size(); ++j) {
                ors[j].first |= nums[i];
                if (ors[k].first == ors[j].first)
                    ors[k].second = ors[j].second; // 合并相同值，下标取最小的
                else
                    ors[++k] = ors[j];
            }
            ors.resize(k + 1);
            // 本题只用到了 ors[0]，如果题目改成任意给定数字，可以在 ors 中查找
            ans[i] = ors[0].second - i + 1;
        }
        return ans;
    }
};
