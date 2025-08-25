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
    vector<int> b(n);
    For(i, n) cin >> b[i];

    int m;
    cin >> m;
    vector<int> d(m);
    For(i, m) cin >> d[i];

    map<int, int> need;
    for (int i = 0; i < n; i++) {
        if (a[i] == b[i]) {
        } else {
            need[b[i]]++;
        }
    }

    map<int, int> have;
    for (int t: d) {
        have[t]++;
    }

    for (auto &[k, v]: need) {
        if (have[k] < v) {
            cout << "NO\n";
            return;
        }
    }

    int last = -1;
    for (int i = 0; i < m; i++) {
        int t = d[i];
        if (!need.contains(t)) {
            last = i;
        }
    }

    if (last == -1) {
        cout << "YES\n";
        return;
    }


    map<int, int> cnt;
    for (int x: b)
        cnt[x]++;
    for (int i = last; i < m; i++) {
        if (cnt.contains(d[i])) {
            cout << "YES\n";
            return;
        }
    }

    cout << "NO\n";
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
