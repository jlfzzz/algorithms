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
    vector<int> a(n);
    For(i, n) { cin >> a[i]; }

    int need = 0;
    int ave = -1;
    int pos = -1;
    ranges::sort(a);
    for (int i = 0; i < n - 1; i++) {
        int x = a[i], y = a[i + 1];
        int d = y - x;
        int t = (i + 1) * d;
        if (need + t <= k) {
            need += t;
        } else {
            int have = k - need;
            int extra = have / (i + 1);
            ave = x + extra;
            pos = i + 1;
            break;
        }
    }

    int ans = 0;
    if (ave == -1) {
        int have = k - need;
        int extra = have / (n);
        int t = have % n;
        ans = (a.back() + extra) * n - n + 1 + t;
    } else {
        int extra = (k - need) % pos;
        ans = ave * n - n + 1 + (n - pos + extra);
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
