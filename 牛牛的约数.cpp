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

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    unordered_map<int, int> pos;
    for (int i = 0; i < n; ++i)
        pos[a[i]] = i + 1;
    auto vals = a;
    ranges::sort(vals);
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    int m = vals.size();
    auto gcd128 = [](__int128 x, __int128 y) {
        while (y) {
            __int128 t = x % y;
            x = y;
            y = t;
        }
        return x;
    };
    const __int128 LIM = (__int128) 1000000000000000000LL;
    __int128 L = 1;
    vector<int> basis;
    vector<int> pick(m, -1);
    for (int t = 0; t < m; t++) {
        int v = vals[t];
        if (t == 0)
            pick[t] = -1;
        else {
            bool allDiv = (L <= LIM) && (v % (long long) L == 0);
            if (allDiv)
                pick[t] = -1;
            else {
                int y = -1;
                for (int b: basis) {
                    if (v % b != 0) {
                        y = b;
                        break;
                    }
                }
                pick[t] = y;
            }
        }
        __int128 g = gcd128(L, (__int128) v);
        __int128 newL = (L / g) * (__int128) v;
        if (newL > L)
            basis.push_back(v);
        L = (newL > LIM ? LIM + 1 : newL);
    }
    for (int i = 0; i < n; i++) {
        int x = a[i];
        int t = ranges::lower_bound(vals, x) - vals.begin();
        if (pick[t] == -1)
            cout << -1 << ' ';
        else {
            int y = pick[t];
            cout << pos[y] << ' ';
        }
    }
    cout << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
