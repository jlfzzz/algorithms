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
    string largestNumber(vector<int> &nums) {
        ranges::sort(nums, [](int x, int y) { return to_string(x) + to_string(y) > to_string(y) + to_string(y); });

        string ans;
        for (int x: nums) {
            if (ans.size() && ans[0] == '0')
                continue;
            ans += to_string(x);
        }

        return ans;
    }
};
