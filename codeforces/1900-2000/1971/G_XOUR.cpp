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
    For(i, n) cin >> a[i];

    vector<pii> small;
    map<int, vector<pii>> other;

    for (int i = 0; i < n; i++) {
        int x = a[i];
        if (x <= 3) {
            small.emplace_back(x, i);
        } else {
            int t = x >> 2;
            other[t].emplace_back(x, i);
        }
    }

    vector<int> ans(n);
    {
        ranges::sort(small);
        vector<int> idx;
        for (auto &[x, i]: small) {
            idx.push_back(i);
        }
        ranges::sort(idx);
        for (int i = 0; i < idx.size(); i++) {
            ans[idx[i]] = small[i].first;
        }
    }

    for (auto &[k, v]: other) {
        ranges::sort(v);
        vector<int> idx;
        for (auto &[x, i]: v) {
            idx.push_back(i);
        }
        ranges::sort(idx);
        for (int i = 0; i < idx.size(); i++) {
            ans[idx[i]] = v[i].first;
        }
    }

    for (int x: ans) {
        cout << x << ' ';
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
