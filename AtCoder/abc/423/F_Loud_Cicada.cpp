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
int C[25][25];
void init() {
    for (int i = 0; i <= 20; i++) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; j++)
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
    }
}

void solve() {
    int n, m, y;
    cin >> n >> m >> y;
    vector<int> a(n);
    For(i, n) cin >> a[i];

    int u = 1 << n;
    vector<int> LCM(u, 1);
    LCM[0] = 1;
    for (int mask = 1; mask < u; mask++) {
        int b = __builtin_ctzll((unsigned long long) mask);
        int nmask = mask ^ (1 << b);
        int l = LCM[nmask];
        if (l > y) {
            LCM[mask] = y + 1;
            continue;
        }
        int x = a[b];
        int g = gcd(l, x);
        int temp = l / g;
        if (temp > 0 && temp > y / x) {
            LCM[mask] = y + 1;
        } else {
            LCM[mask] = temp * x;
        }
    }

    i128 ans = 0;
    for (int mask = 1; mask < u; mask++) {
        int k = __builtin_popcountll((unsigned long long) mask);
        if (k < m)
            continue;
        int L = LCM[mask];
        if (L == 0 || L > y)
            continue;
        i128 temp = (i128) (y / L) * (i128) C[k][m];
        if ((k - m) & 1)
            ans -= temp;
        else
            ans += temp;
    }

    cout << (int) ans << '\n';
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
