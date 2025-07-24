/*
*/


#include <algorithm>
#include <vector>
#include <math.h>

using namespace std;

class Solution {
public:
    int trap(vector<int> &height) {
        //1
                // int ans = 0;
                // int left = 0, right = height.size() - 1;
                // int leftMax = 0, rightMax = 0;
                // while (left < right) {
                //     leftMax = max(leftMax, height[left]);
                //     rightMax = max(rightMax, height[right]);
                //     if (height[left] < height[right]) {
                //         ans += leftMax - height[left];
                //         ++left;
                //     } else {
                //         ans += rightMax - height[right];
                //         --right;
                //     }
                // }
                // return ans;

        //2
                //     int ans = 0;
            //     vector<int> leftMax(height.size());
            //     vector<int> rightMax(height.size());

            //     leftMax[0] = height[0];
            //     for (int i = 1; i < height.size(); ++i) {
            //         leftMax[i] = max(leftMax[i - 1], height[i]);
            //     }

            //     rightMax[0] = height[height.size() - 1];
            //     for (int i = height.size() - 2; i >= 0; --i) {
            //         rightMax[i] = max(rightMax[i + 1], height[i]);
            //     }

            //     for (int i = 1; i < height.size(); ++i) {
            //         ans += min(leftMax[i], rightMax[i]) - height[i];
            //     }

            //     return ans;



        int ans = 0;
        int left = 0, right = height.size() - 1;
        int leftMax = 0, rightMax = 0;
        while (left < right) {
            leftMax = max(leftMax, height[left]);
            rightMax = max(rightMax, height[right]);
            if (leftMax < rightMax) {
                ans += leftMax - height[left];
                ++left;
            } else {
                ans += rightMax - height[right];
                --right;
            }
        }
        return ans;
    }
    //3


};

