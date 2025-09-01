#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
constexpr int MOD = int(1e9 + 7);
#define i128 __int128_t
#define ull unsigned long long
constexpr int inf = 0x3f3f3f3f / 2;


const int MX = 100'001;
vector<int> divisors[MX];

int init = [] {
    for (int i = 1; i < MX; i++) {
        for (int j = i; j < MX; j += i) {
            divisors[j].push_back(i);
        }
    }
    return 0;
}();

class Solution {
public:
    vector<int> minDifference(int n, int k) {
        int min_diff = INT_MAX;
        vector<int> path(k), ans;

        auto dfs = [&](this auto &&dfs, int i, int n, int mn, int mx) -> void {
            if (i == k - 1) {
                int d = max(mx, n) - min(mn, n);
                if (d < min_diff) {
                    min_diff = d;
                    path[i] = n;
                    ans = path;
                }
                return;
            }
            for (int d: divisors[n]) {
                path[i] = d;
                dfs(i + 1, n / d, min(mn, d), max(mx, d));
            }
        };

        dfs(0, n, INT_MAX, 0);
        return ans;
    }
};
