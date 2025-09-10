#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define int ll
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
// constexpr int MOD = int(1e9 + 7);
// constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

// constexpr int LIM = 62;

constexpr int MAXB = 20;
constexpr int MAXV = 1 << MAXB;
static int32_t F[MAXB][MAXV];
static long long G[MAXB][MAXV];

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    For(i, n) cin >> a[i];

    long long S = 0;
    for (int x: a)
        S += (long long) MAXV - (long long) x;

    for (int p = MAXB - 1; p >= 0; p--) {
        memset(F[p], 0, sizeof(F[p]));
        memset(G[p], 0, sizeof(G[p]));
        int lowMask = (1 << p) - 1;
        for (int x: a)
            if (((x >> p) & 1) == 0) {
                F[p][(int) x] += 1;
                G[p][(int) x] += (x & lowMask);
            }
        for (int b = 0; b < MAXB; b++) {
            for (int mask = MAXV - 1; mask >= 0; mask--) {
                if (mask & (1 << b)) {
                    F[p][mask ^ (1 << b)] += F[p][mask];
                    G[p][mask ^ (1 << b)] += G[p][mask];
                }
            }
        }
    }

    while (q--) {
        int k;
        cin >> k;
        if ((i128) k >= (i128) S) {
            auto add = (long long) ((k - S) / n);
            cout << ((long long) MAXV + add) << '\n';
            continue;
        }
        long long res = 0;
        long long cat = 0;
        for (int p = MAXB - 1; p >= 0; p--) {
            i128 cost =
                (i128) cat * ((i128) 1 << p) + (i128) F[p][(int) res] * ((i128) 1 << p) - (i128) G[p][(int) res];
            if ((i128) k >= cost) {
                cat += F[p][(int) res];
                res |= 1ll << p;
                k -= (long long) cost;
            }
        }
        cout << res << '\n';
    }
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
