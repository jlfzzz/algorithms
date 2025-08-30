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
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> a(n);
    For(i, n) cin >> a[i];
    vector<int> b(n);
    For(i, m) cin >> b[i];

    map<int, int> cnt1;
    for (int x: b)
        cnt1[x]++;

    int window = 0;
    int ans = 0;
    map<int, int> cnt2;
    for (int r = 0; r < n; r++) {
        int x = a[r];
        if (cnt1.contains(x)) {
            if (cnt2[x] < cnt1[x]) {
                window++;
            }
            cnt2[x]++;
        }

        if (window >= k && r >= m - 1) {
            ans++;
        }
        if (r - m + 1 >= 0) {
            int y = a[r - m + 1];
            if (cnt1.contains(y)) {
                if (cnt2[y] <= cnt1[y]) {
                    window--;
                }
                cnt2[y]--;
            }
        }
    }

    cout << ans << '\n';
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
