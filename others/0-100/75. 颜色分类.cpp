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
#include <cstring>
#include <array> 
#include <bitset>
#include <stack>
#include <set>
#include <random>

using namespace std;

class Solution {
public:
    void sortColors(vector<int> &nums) {
        int n = nums.size();
        int left = 0;
        int right = n;
        int i = 0;

        while (i < right) {
            if (nums[i] == 0) {
                swap(nums[left], nums[i]);
                i++;
                left++;
            } else if (nums[i] == 1) {
                i++;
            } else {
                right--;
                swap(nums[i], nums[right]);
                //i++;
            }
        }
    }
};