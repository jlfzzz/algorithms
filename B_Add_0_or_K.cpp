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
    For(i, n) cin >> a[i];
    auto f = [&](int x) -> int {
        if ((x & 1) == 0)
            return 2;
        for (int d = 3; d * d <= x; d += 2)
            if (x % d == 0)
                return d;
        return x;
    };
    int p = f(k + 1);
    auto qpow = [&](int a, int e, int mod) -> int {
        int res = 1 % mod;
        int b = (a % mod + mod) % mod;
        while (e) {
            if (e & 1)
                res = res * b % mod;
            b = b * b % mod;
            e >>= 1;
        }
        return res;
    };
    int inv = qpow(k % p, p - 2, p);
    For(i, n) {
        int x = (a[i] % p + p) % p;
        int t = (p - x) % p * inv % p;
        a[i] += t * k;
    }
    For(i, n) cout << a[i] << ' ';
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
