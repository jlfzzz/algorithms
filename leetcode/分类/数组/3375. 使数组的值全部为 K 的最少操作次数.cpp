#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

// 排序

class Solution {
public:
    int minOperations(vector<int> &nums, int k) {
        ranges::sort(nums);
        int n = nums.size();
        if (k > nums[0]) return -1;
        int count = 0;

        
        for (int i = n - 1;i > 0; i--) {
            if (nums[i] != nums[i - 1]) {
                count++;
            }
        }

        if (k == nums[0]) return count;
        return count + 1;
    }
};

// map
class Solution {
public:
    int minOperations(vector<int> &nums, int k) {
        unordered_map<int, int> map;
        int mn = nums[0];
        for (int x : nums) {
            mn = min(mn, x);
            map[x]++;
        }
        if (k > mn) return -1;

        if (k == mn) return map.size() - 1;
        return map.size();
    }
};