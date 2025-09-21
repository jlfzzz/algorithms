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

static inline int bitlen(unsigned long long x) { return x ? (int) (64 - __builtin_clzll(x)) : 0; }

void init() {}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    For(i, n) cin >> a[i];
    int i = 0;
    while (i < n && a[i] == -1)
        i++;

    vector<int> ans(n);

    if (i == n) {
        for (int j = 0; j < n; j++)
            ans[j] = (j % 2 == 0 ? 1 : 2);
        for (int v: ans)
            cout << v << ' ';
        cout << '\n';
        return;
    }

    for (int j = i - 1, flag = 1; j >= 0; --j, flag ^= 1) {
        ans[j] = flag ? a[i] * 2 : a[i];
    }

    while (i < n) {
        ans[i] = a[i];
        int j = i + 1;
        while (j < n && a[j] == -1)
            j++;

        if (j == n) {
            int flag = 0;
            for (int k = i + 1; k < n; k++) {
                ans[k] = (flag == 0 ? ans[i] * 2 : ans[i]);
                flag ^= 1;
            }
            break;
        }

        int x = a[i];
        int y = a[j];
        int d = j - i - 1;
        int e = j - i;

        if (d == 0) {
            if (!(x == (y / 2) || y == (x / 2))) {
                cout << -1 << '\n';
                return;
            }
            i = j;
            continue;
        }

        int len1 = bitlen((ull) x);
        int len2 = bitlen((ull) y);
        int p1 = len1 - 1;
        int p2 = len2 - 1;
        int limit = min(len1, len2);
        int same = 0;
        for (int t = 0; t < limit; t++) {
            if ((x >> p1) == (y >> p2))
                same++;
            else
                break;
            p1--;
            p2--;
        }

        int up = len1 - same;
        int down = len2 - same;
        int need = up + down;

        if (need > e || ((e - need) & 1)) {
            cout << -1 << '\n';
            return;
        }

        int p = i + 1;
        int cycles = (e - need) / 2;
        for (int c = 0; c < cycles; ++c) {
            int cur = ans[p - 1];
            ans[p++] = cur * 2;
            ans[p++] = ans[p - 2];
        }

        if (down == 0) {
            for (int t = 0; t < up - 1; ++t) {
                ans[p] = ans[p - 1] / 2;
                p++;
            }
        } else {
            for (int t = 0; t < up; ++t) {
                ans[p] = ans[p - 1] / 2;
                p++;
            }
            for (int k = down - 1; k >= 1; --k) {
                int bit = (y >> k) & 1;
                ans[p] = ans[p - 1] * 2 + bit;
                p++;
            }
        }

        i = j;
    }

    for (int x: ans)
        cout << x << ' ';
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
