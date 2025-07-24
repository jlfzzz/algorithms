/*
*/


#include <algorithm>
#include <vector>
#include <math.h>

using namespace std;

class Solution {
public:
    int maxArea(vector<int> &height) {
        int res = 0;

        int left = 0;
        int right = height.size() - 1;

        while (left < right) {
            int sum = (right - left) * min(height[left], height[right]);
            res = max(res, sum);
            if (height[left] < height[right]) {
                ++left;
            } else {
                --right;
            }
        }

        return res;
    }
};