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
    int n, m, q;
    cin >> n >> m >> q;
    vector<int> a(n);
    vector<int> b(m);
    For(i, n) cin >> a[i];
    For(i, m) cin >> b[i];

    set<int> s1, s2;
    vector<int> v1, v2;
    for (int x: a) {
        if (!s1.contains(x)) {
            s1.insert(x);
            v1.push_back(x);
        }
    }
    for (int x: b) {
        if (!s2.contains(x)) {
            s2.insert(x);
            v2.push_back(x);
        }
    }

    for (int i = 0; i < v2.size(); i++) {
        if (v1[i] != v2[i]) {
            cout << "TIDAK\n";
            return;
        }
    }
    cout << "YA\n";
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
