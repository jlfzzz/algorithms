#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
	bool ck(vector<int>& nums, int x, int orders) {
		int sum = 0;
		for(int i : nums) {
			sum += max(i - x, 0);
			if(sum > orders) {
				return true;
			}
		}
		return false;
	}
	int maxProfit(vector<int>& nums, int orders) {
		int l = 0, r = 1e9;
		while(l < r) {
			int mid = (l + r) >> 1;
			if(ck(nums, mid, orders)) {
				l = mid + 1;
			} else {
				r = mid;
			}
		}
		long res = 0, mod = 1e9 + 7;
		for(int i : nums) {
			if(i > l) {
				res += ((long)(i + l + 1) * (long)(i - l)) >> 1;
				res %= mod;
				orders -= i - l;
			}
		}
		res += (long)l * (long)orders;
		res %= mod;
		return res;
	}
};


class Solution {
public:
	int maxProfit(vector<int>& inventory, int orders) {
		ll n = inventory.size();
		ranges::sort(inventory, greater<>());
		ll remainder = orders;
		ll i = 0;
		ll prev = inventory[0];
		ll sum = 0;
		while (remainder > 0) {
			ll j = i + 1;
			while (j < n && inventory[j] == prev) {
				j++;
			}
			ll next = 0;
			if (j < n) {
				next = inventory[j];
			}

			ll parts = j;
			ll max_point = prev;
			ll mn_point = next + 1;
			ll max_count = (max_point - mn_point + 1) * parts;
			ll max_total = (mn_point + max_point) * (max_point - mn_point + 1) * parts / 2;
			if (remainder - max_count >= 0) {
				remainder -= max_count;
				sum = (sum + max_total) % MOD;
			} else {
				ll each_line_to_take = remainder / parts;
				sum = (sum + (max_point + max_point - each_line_to_take + 1) * each_line_to_take * parts / 2) % MOD;
				ll extra = remainder % parts;
				sum = (sum + (max_point - each_line_to_take) * extra) % MOD;
				return sum;
			}
			prev = next;
			i = j;
		}
		return sum;
	}
};

class Solution {
private:
	using LL = long long;

	static constexpr int mod = 1000000007;

	static constexpr LL rangeSum(int x, int y) {
		return static_cast<LL>(x + y) * (y - x + 1) / 2;
	}

public:
	int maxProfit(vector<int> &inventory, int orders) {
		int l = 0;
		int r = *max_element(inventory.begin(), inventory.end());
		int T = -1;
		while (l <= r) {
			int mid = (l + r) / 2;
			LL total = accumulate(inventory.begin(), inventory.end(), 0LL, [&](LL acc, int ai) {
				return acc + max(ai - mid, 0);
			});
			if (total <= orders) {
				T = mid;
				r = mid - 1;
			} else {
				l = mid + 1;
			}
		}
		int rest = orders - accumulate(inventory.begin(), inventory.end(), 0, [&](int acc, int ai) {
			return acc + max(ai - T, 0);
		});
		LL ans = 0;
		for (int ai: inventory) {
			if (ai >= T) {
				if (rest > 0) {
					ans += rangeSum(T, ai);
					--rest;
				} else {
					ans += rangeSum(T + 1, ai);
				}
			}
		}
		return ans % mod;
	}
};

class Solution {
public:
	int maxProfit(vector<int> &nums, int orders) {
		sort(nums.begin(), nums.end(), greater<int>());
		long res = 0, mod = 1e9 + 7;
		int j = 0;
		while (orders > 0) {
			while (j < nums.size() && nums[j] >= nums[0]) {
				++j;
			}
			int next = 0;
			if (j < nums.size()) {
				next = nums[j];
			}
			long bucks = j, delta = nums[0] - next;
			long rem = bucks * delta;
			if (rem > orders) {
				long dec = orders / bucks;
				long a1 = nums[0] - dec + 1, an = nums[0];
				res += (((a1 + an) * dec) / 2) * bucks;
				res += (nums[0] - dec) * (orders % bucks);
			} else {
				long a1 = next + 1, an = nums[0];
				res += (((a1 + an) * delta) / 2) * bucks;
				nums[0] = next;
			}
			orders -= rem;
			res %= mod;
		}
		return res;
	}
};
