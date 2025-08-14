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
const ll MOD2 = 4611686018427387847;
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

void solve() {
    int n, m;
    cin >> n >> m;

    vector<int> b(m);
    multiset<int> a;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        a.insert(x);
    }
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }

    auto Find = [&](auto &&self, int x) -> bool {
        if (a.contains(x)) {
            a.extract(x);
            return true;
        } else if (a.empty() or *a.begin() > x) {
            return false;
        }
        if (x % 2 == 0) {
            return self(self, x / 2) and self(self, x / 2);
        } else {
            return self(self, x / 2) and self(self, x / 2 + 1);
        }
    };

    bool ok = true;
    for (auto x: b) {
        ok &= Find(Find, x);
    }
    ok &= a.empty();
    cout << (ok ? "Yes" : "No") << "\n";
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
