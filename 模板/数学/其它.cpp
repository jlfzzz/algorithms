#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> DIRS = {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}};
using ll = long long;
constexpr int MOD = int(1e9 + 7);


// 手动算 ceil(sqrt(x))，防止浮点数hack
auto calc1 = [&](ll x) -> ll {
    ll lo = 1, hi = x + 1;
    ll res = 0;
    while (lo < hi) {
        ll mid = lo + (hi - lo) / 2;
        if (mid <= x / mid) {
            res = mid;
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    return res;
};
