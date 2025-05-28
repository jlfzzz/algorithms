//
// Created by 123 on 25-5-27.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] =  {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
	int maxArea(vector<int>& height) {
		int n = height.size();
		int left = 0;
		int right = n - 1;
		int ans = 0;
		while (left < right) {
			ans = max(ans, min(height[left], height[right]) * (right - left));
			if (height[left] < height[right]) {
				left++;
			} else {
				right--;
			}
		}
		return ans;
	}
};