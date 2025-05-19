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
    char nextGreatestLetter(vector<char> &letters, char target) {
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
        auto i = lower_bound(letters.begin(), letters.end(), target + 1);
        
        if (i == letters.end()) return letters[0];
        return *i;
    }
};