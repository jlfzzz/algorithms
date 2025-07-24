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

using namespace std;

class Solution {
public:
	bool containsNearbyAlmostDuplicate(vector<int> &nums, int k, int t) {
		set<long> st;
		for (int i = 0; i < nums.size(); i++) {
			auto lb = st.lower_bound(static_cast<long>(nums[i]) - t);
			if (lb != st.end() && *lb <= static_cast<long>(nums[i]) + t) return true;
			st.insert(nums[i]);
			if (i >= k) st.erase(nums[i - k]);
		}
		return false;
	}
};


class Solution {
public:
	bool containsNearbyAlmostDuplicate(vector<int> &nums, int k, int t) {
		set<long> st;
		for (int i = 0; i < nums.size(); i++) {
			auto lb = st.lower_bound(static_cast<long>(nums[i]) - t);
			if (lb != st.end() && *lb <= static_cast<long>(nums[i]) + t) return true;
			st.insert(nums[i]);
			if (i >= k) st.erase(nums[i - k]);
		}
		return false;
	}
};
