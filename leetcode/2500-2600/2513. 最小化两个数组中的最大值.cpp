//
// Created by 123 on 25-6-9.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] =  {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
	using ll = long long;

	// 计算最大公约数
	ll gcd(ll a, ll b) {
		return b == 0 ? a : gcd(b, a % b);
	}

	// 最小公倍数
	ll lcm(ll a, ll b) {
		return a / gcd(a, b) * b;
	}

	int minimizeSet(int divisor1, int divisor2, int uniqueCnt1, int uniqueCnt2) {
		ll lo = 1, hi = 1e18;
		ll l = lcm(divisor1, divisor2);

		while (lo < hi) {
			ll mid = lo + (hi - lo) / 2;

			ll onlyA = mid / divisor2 - mid / l;
			ll onlyB = mid / divisor1 - mid / l;
			ll shared = mid - mid / divisor1 - mid / divisor2 + mid / l;

			ll needA = max(0LL, (ll)uniqueCnt1 - onlyA);
			ll needB = max(0LL, (ll)uniqueCnt2 - onlyB);

			if (needA + needB <= shared) {
				hi = mid;
			} else {
				lo = mid + 1;
			}
		}

		return lo;
	}
};
