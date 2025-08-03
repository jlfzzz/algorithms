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
#include <queue>

using namespace std;

// 1， 2 二分。 1 手动判断循环数组，2用前后哨兵节点
// 3 预处理

class Solution {
public:
    vector<int> solveQueries(vector<int> &nums, vector<int> &queries) {
        vector<int> ans;
        unordered_map<int, vector<int>> mp;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            mp[nums[i]].emplace_back(i);
        }

        for (int index : queries) {
            int target = nums[index];
            if (mp[target].size() == 1) {
                ans.emplace_back(-1);
                continue;
            }
            auto it = lower_bound(mp[target].begin(), mp[target].end(), index);
            int idx = it - mp[target].begin();

            int size = mp[target].size();
            int leftIdx = mp[target][(idx - 1 + size) % size];
            int rightIdx = mp[target][(idx + 1 + size) % size];
            int leftDiff, rightDiff;

            if (leftIdx < index) {
                leftDiff = index - leftIdx;
            } else {
                leftDiff = n - (leftIdx - index);
            }

            if (rightIdx < index) {
                rightDiff = n - (index - rightIdx);
            } else {
                rightDiff = rightIdx - index;
            }

            ans.emplace_back(min(leftDiff, rightDiff));
        }

        return ans;
    }
};

class Solution {
public:
    vector<int> solveQueries(vector<int> &nums, vector<int> &queries) {
        unordered_map<int, vector<int>> indices;
        for (int i = 0; i < nums.size(); i++) {
            indices[nums[i]].push_back(i);
        }

        int n = nums.size();
        for (auto &[_, p] : indices) {
            // 前后各加一个哨兵
            int i0 = p[0];
            p.insert(p.begin(), p.back() - n);
            p.push_back(i0 + n);
        }

        for (int &i : queries) { // 注意这里是引用
            auto &p = indices[nums[i]];
            if (p.size() == 3) {
                i = -1;
            } else {
                int j = ranges::lower_bound(p, i) - p.begin();
                i = min(i - p[j - 1], p[j + 1] - i);
            }
        }
        return queries;
    }
};

class Solution {
public:
    vector<int> solveQueries(vector<int> &nums, vector<int> &queries) {
        int n = nums.size();
        vector<int> left(n), right(n);
        unordered_map<int, int> pos;
        for (int i = -n; i < n; i++) {
            if (i >= 0) {
                left[i] = pos[nums[i]];
            }
            pos[nums[(i + n) % n]] = i;
        }

        pos.clear();
        for (int i = n * 2 - 1; i >= 0; i--) {
            if (i < n) {
                right[i] = pos[nums[i]];
            }
            pos[nums[i % n]] = i;
        }

        for (int &i : queries) {
            int l = left[i];
            i = i - l == n ? -1 : min(i - l, right[i] - i);
        }
        return queries;
    }
};
