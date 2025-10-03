#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define int ll
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

class Solution {
public:
    int trap(vector<int> &height) { 
        int n = height.size();
        vector<int> stk;

        int ans = 0;
        for (int i = 0; i < n; i++) {
            while (!stk.empty() && height[i] >= height[stk.back()]) {
                int j = stk.back();
                if (stk.size() >= 2) {
                    int k = stk[stk.size() - 2];
                    int mn = min(height[i], height[k]) - height[j];
                    ans += mn * (i - k - 1);
                }
                stk.pop_back();
            }
            stk.push_back(i);
        }

        return ans;
    }
};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    cin >> T;
    return 0;
}
