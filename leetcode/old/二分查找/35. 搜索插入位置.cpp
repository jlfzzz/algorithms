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
    int searchInsert(vector<int> &nums, int target) {
        auto lowerBound = [&](vector<int> &nums, int target) -> int {
            int left = 0;
            int n = nums.size();
            int right = n;

            while (left < right) {
                int mid = left + (right - left) / 2;
                if (nums[mid] < target) {
                    left = mid + 1;
                } else {
                    right = mid;
                }
            }
            return left;
            };
        return lowerBound(nums, target);
        // int n = nums.size();
        // if (index == n) return n;
        // return index;
    }
};