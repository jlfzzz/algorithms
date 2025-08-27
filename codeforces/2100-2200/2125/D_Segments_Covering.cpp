#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define int ll
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(998244353);
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

void solve2() {
    int n, m;
    cin >> n >> m;
    map<int, vector<pii>> cnt;
    int base = 1;

    auto q_pow = [&](int base, int power) {
        int res = 1;
        while (power) {
            if (power & 1) {
                res = res * base % MOD;
            }
            base = base * base % MOD;
            power /= 2;
        }
        return res;
    };

    For(i, n) {
        int l, r, p, q;
        cin >> l >> r >> p >> q;
        int t = p * q_pow(q, MOD - 2) % MOD;
        int one = (1 - t + MOD) % MOD;
        base = base * one % MOD;
        int tt = t * q_pow(one, MOD - 2) % MOD;
        cnt[l].emplace_back(r, tt);
    }

    map<int, int> memo;
    auto dfs = [&](this auto &&dfs, int l) -> int {
        if (memo.contains(l)) {
            return memo[l];
        }

        if (!cnt.contains(l)) {
            return memo[l] = (l == m + 1);
        }
        int res = 0;
        for (const auto [r, p]: cnt[l]) {
            res = (res + (dfs(r + 1) * p % MOD)) % MOD;
        }
        memo[l] = res;
        return res;
    };
    int ans = dfs(1) % MOD;
    cout << ans * base % MOD << '\n';
}
void solve() {
    int n, m;
    cin >> n >> m;
    map<int, vector<pii>> cnt;
    int base = 1;

    auto q_pow = [&](int base, int power) {
        int res = 1;
        while (power) {
            if (power & 1) {
                res = res * base % MOD;
            }
            base = base * base % MOD;
            power /= 2;
        }
        return res;
    };

    For(i, n) {
        int l, r, p, q;
        cin >> l >> r >> p >> q;
        int t = p * q_pow(q, MOD - 2) % MOD;
        int one = (1 - t + MOD) % MOD;
        base = base * one % MOD;
        int tt = t * q_pow(one, MOD - 2) % MOD;
        cnt[l].emplace_back(r, tt);
    }

    map<int, int> memo;
    auto dfs = [&](this auto &&dfs, int l) -> int {
        if (memo.contains(l)) {
            return memo[l];
        }

        if (!cnt.contains(l)) {
            return memo[l] = (l == m + 1);
        }
        int res = 0;
        for (const auto [r, p]: cnt[l]) {
            res = (res + (dfs(r + 1) * p % MOD)) % MOD;
        }
        memo[l] = res;
        return res;
    };
    int ans = dfs(1) % MOD;
    cout << ans * base % MOD << '\n';
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
