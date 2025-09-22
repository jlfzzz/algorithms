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
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    For(i, n) cin >> a[i];

    vector<int> pre(n + 1);
    map<int, set<int>> pos;
    for (int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] ^ a[i - 1];
        pos[pre[i]].insert(i);
    }

    while (q--) {
        int l, r;
        cin >> l >> r;

        int t1 = pre[r] ^ pre[l - 1];

        if (t1 == 0) {
            cout << "YES\n";
            continue;
        }

        auto itR = pos.find(pre[r]);
        if (itR == pos.end()) {
            cout << "NO\n";
            continue;
        }

        auto &stR = itR->second;
        auto iit = stR.lower_bound(l);
        if (iit == stR.end() || *iit >= r) {
            cout << "NO\n";
            continue;
        }

        auto itL = pos.find(pre[l - 1]);
        if (itL == pos.end()) {
            cout << "NO\n";
            continue;
        }

        auto &stL = itL->second;
        auto jit = stL.upper_bound(r - 1);
        if (jit == stL.begin()) {
            cout << "NO\n";
            continue;
        }
        --jit;

        if (*iit < *jit)
            cout << "YES\n";
        else
            cout << "NO\n";
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
