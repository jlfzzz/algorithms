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
    int maxAbsoluteSum(vector<int> &nums) {
        int maxSum = 0, minSum = 0;
        int currentMax = 0, currentMin = 0;

        for (int num : nums) {
            // 更新最大子数组和
            currentMax = max(num, currentMax + num);
            maxSum = max(maxSum, currentMax);

            // 更新最小子数组和
            currentMin = min(num, currentMin + num);
            minSum = min(minSum, currentMin);
        }

        return max(maxSum, -minSum);
    }
};