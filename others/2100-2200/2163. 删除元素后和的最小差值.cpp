#include "bits/stdc++.h"
using namespace std;
using ll = long long;

class Solution {
    public:
    long long minimumDifference(vector<int> &nums) {
        ll n = nums.size() / 3;
        ll s1 = 0;
        ll s2 = 0;
        priority_queue<ll, vector<ll>, greater<>> pq1;
        for (ll i = n * 2; i < n * 3; i++) {
            s1 += nums[i];
            pq1.emplace(nums[i]);
        }

        priority_queue<ll, vector<ll>> pq2;
        for (ll i = 0; i < n; i++) {
            s2 += nums[i];
            pq2.emplace(nums[i]);
        }

        vector<ll> forwards(n + 1, LONG_LONG_MAX);
        forwards[0] = s2;
        vector<ll> backwards(n + 1, LONG_LONG_MIN);
        backwards[n] = s1;
        for (ll i = n; i < n * 2; i++) {
            forwards[i - n + 1] = forwards[i - n];
            auto x = pq2.top();
            ll y = nums[i];
            if (y < x) {
                pq2.pop();
                pq2.emplace(y);
                forwards[i - n + 1] -= x - y;
            }
        }

        for (ll i = 2 * n - 1; i >= n; i--) {
            backwards[i - n] = backwards[i - n + 1];
            auto x = pq1.top();
            ll y = nums[i];
            if (y > x) {
                pq1.pop();
                pq1.emplace(y);
                backwards[i - n] += y - x;
            }
        }

        ll ans = LONG_LONG_MAX;
        for (ll i = n; i < 2 * n; i++) {
            ll left = forwards[i - n + 1];
            ll right = backwards[i - n + 1];
            ans = min(ans, left - right);
            left = forwards[i - n];
            right = backwards[i - n];
            ans = min(ans, left - right);
        }
        return ans;
    }
};
