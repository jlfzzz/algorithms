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

    int mn = ranges::min(a);
    int pos = -1;
    for (int i = 0; i < n; i++) {
        if (a[i] == mn) {
            pos = i;
            break;
        }
    }

    bool f = true;
    int pre = a[pos];
    for (int i = pos; i < n; i++) {
        if (a[i] < pre) {
            f = false;
        }
        pre = a[i];
    }

    if (f) {
        cout << pos << '\n';
    } else {
        cout << -1 << '\n';
    }
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
