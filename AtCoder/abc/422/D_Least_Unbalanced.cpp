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
    int n, k;
    cin >> n >> k;

    int total = 1 << n;

    int x = k / total;
    int extra = k % total;
    vector<int> ans(total, x);

    if (extra != 0) {
        cout << 1 << '\n';
        vector<int> add(1, extra);
        for (int i = 0; i < n; i++) {
            vector<int> nxt;
            nxt.reserve(add.size() * 2);
            for (int w: add) {
                int a = w / 2;
                int b = w - a;
                nxt.push_back(a);
                nxt.push_back(b);
            }
            add.swap(nxt);
        }
        for (int i = 0; i < total; i++) {
            ans[i] += add[i];
        }
    } else {
        cout << 0 << '\n';
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
    // cin >> T;
    while (T--)
        solve();
    return 0;
}
