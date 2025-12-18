#include <bits/stdc++.h>
using namespace std;
using pll = pair<long long, long long>;
#define i128 __int128_t
#define ull unsigned long long
constexpr int inf = 0x3f3f3f3f / 2;
using pii = pair<int, int>;
using ll = long long;


class Solution {
public:
    int countSubarrays(vector<int> &nums, int k) {
        int n = nums.size();
        int pos = -1;
        for (int i = 0; i < n; i++) {
            int &x = nums[i];
            if (x > k) {
                x = 1;
            } else if (x < k) {
                x = -1;
            } else {
                pos = i + 1;
                x = 0;
            }
        }

        vector<int> pref(2 * n + 1, 0);
        pref[0 + n] = 1;

        int pre = 0;
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            int x = nums[i - 1];
            pre += x;

            if (i < pos) {
                pref[pre + n]++;
            } else {
                ans += pref[pre + n]; 
                ans += pref[pre - 1 + n];
            }
        }

        return ans;
    }
};
