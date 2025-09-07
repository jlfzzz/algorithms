#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
constexpr int MOD = int(1e9 + 7);
#define i128 __int128_t
#define ull unsigned long long
constexpr int inf = 0x3f3f3f3f / 2;


class Solution {
public:
    int minOperations(vector<int> &nums) {
        int n = nums.size();
        bool f = true;
        int a = nums[0];
        for (int i = 1; i < n; i++) {
            if (nums[i] != a) {
                f = false;
            }
        }

        if (f) {
            return 0;
        }
        return 1;
    }
};
