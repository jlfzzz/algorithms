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

void solve2() {
    int n;
    cin >> n;
    string s;
    cin >> s;

    s = ' ' + s;

    auto q_pow = [&](int b, int e) -> int {
        int res = 1;
        while (e) {
            if (e & 1) {
                res = res * b % MOD;
            }
            b = b * b % MOD;
            e /= 2;
        }
        return res;
    };

    int inv = q_pow(2, MOD - 2);

    int f = 0;
    for (int i = n; i >= 2; i--) {
        if (s[i] == '1') {
            f = (f + (((1 - f + MOD) % MOD) * inv % MOD)) % MOD;
        } else {
            f = inv * f % MOD;
        }
    }

    cout << n - 1 + f << '\n';
}
void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;

    s = ' ' + s;

    auto q_pow = [&](int b, int e) -> int {
        int res = 1;
        while (e) {
            if (e & 1) {
                res = res * b % MOD;
            }
            b = b * b % MOD;
            e /= 2;
        }
        return res;
    };

    int inv = q_pow(2, MOD - 2);
    int ans = (n - 1) % MOD;

    int f = 0;
    for (int i = n; i >= 2; i--) {
        if (s[i] == '1') {
            f = (1 - f) * inv % MOD + f;
        } else {
            f = inv * f % MOD;
        }
    }

    cout << (ans + f + MOD) % MOD << '\n';
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
