#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int ll
using i128 = __int128_t;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int i = 0; i < (n); i++)
constexpr ll MOD = 998244353;
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

void solve() {
    int N;
    string T;
    cin >> N >> T;

    int M = 1 << N;
    vector<int> dp(M, -1);

    function<int(int)> f = [&](int mask) -> int {
        if (mask == 0)
            return 1;
        int &memo = dp[mask];
        if (memo != -1)
            return memo;
        memo = 0;
        char prev = 0;
        bool has_prev = false;
        for (int i = 0; i < N; i++) {
            if (!((mask >> i) & 1))
                continue;
            if (!has_prev || T[i] != prev) {
                int child = mask ^ (1 << i);
                memo += f(child);
                if (memo >= MOD)
                    memo -= MOD;
                prev = T[i];
                has_prev = true;
            }
        }
        return memo;
    };

    cout << f((1 << N) - 1) << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    while (T--)
        solve();
    return 0;
}
