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
    int n, m;
    cin >> n >> m;
    int tot = n + m + 1;

    vector<int> a(tot + 1), b(tot + 1);
    for (int i = 1; i <= tot; i++)
        cin >> a[i];
    for (int i = 1; i <= tot; i++)
        cin >> b[i];

    vector<int> f(tot + 1);
    vector<int> id(tot + 1);

    int res = 0;
    int ca = 0, cb = 0;

    for (int i = 1; i <= n + m; i++) {
        if (ca == n) {
            res += b[i];
            id[i] = 0;
            ++cb;
        } else if (cb == m) {
            res += a[i];
            id[i] = 1;
            ++ca;
        } else if (a[i] > b[i]) {
            res += a[i];
            id[i] = 1;
            ++ca;
        } else {
            res += b[i];
            id[i] = 0;
            ++cb;
        }
    }

    int forced_ca = tot, forced_cb = tot;
    f[tot] = 0;

    for (int i = n + m; i >= 1; i--) {
        if (id[i]) {
            if (forced_ca == tot)
                f[i] = f[forced_ca] + a[forced_ca];
            else
                f[i] = f[forced_ca] + (a[forced_ca] - b[forced_ca]);
        } else {
            if (forced_cb == tot)
                f[i] = f[forced_cb] + b[forced_cb];
            else
                f[i] = f[forced_cb] + (b[forced_cb] - a[forced_cb]);
        }

        if (id[i] && b[i] > a[i])
            forced_cb = i;
        else if (!id[i] && b[i] < a[i])
            forced_ca = i;
    }

    for (int i = 1; i <= n + m; i++) {
        int contrib = id[i] ? a[i] : b[i];
        cout << res - contrib + f[i] << " ";
    }
    cout << res << "\n";
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
