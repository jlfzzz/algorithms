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
	int trap(vector<int>& height) {
		int ans = 0;
		int left = 0, right = height.size() - 1;
		int leftMax = 0, rightMax = 0;
		while (left < right) {
			leftMax = max(leftMax, height[left]);
			rightMax = max(rightMax, height[right]);
			if (height[left] < height[right]) {
				ans += leftMax - height[left];
				++left;
			} else {
				ans += rightMax - height[right];
				--right;
			}
		}
		return ans;
	}
};

class Solution2 {
public:
	int trap(vector<int>& height) {
		int n = height.size();
		vector<int> left_max(n);
		vector<int> right_max(n);
		int leftMax = 0;
		for (int i = 0; i < n; i++) {
			left_max[i] = max(height[i], leftMax);
			leftMax = left_max[i];
		}
		leftMax = 0;
		for (int i = n - 1; i >= 0; i--) {
			right_max[i] = max(height[i], leftMax);
			leftMax = right_max[i];
		}
		int ans = 0;
		for (int i = 0; i < n; i++) {
			ans += min(left_max[i], right_max[i]) - height[i];
		}
		return ans;
	}
};