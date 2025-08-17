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
const ll MOD2 = 4611686018427387847;
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

int n, m;
int ans[51];
int memo[51][2501][51];
vector<int> divisors[51];

void precompute_divisors() {
    for (int i = 1; i <= 50; ++i) {
        for (int j = 1; j <= i; ++j) {
            if (i % j == 0) {
                divisors[i].push_back(j);
            }
        }
        reverse(divisors[i].begin(), divisors[i].end());
    }
}

bool dfs(int idx, int rem, int prev) {
    if (idx == n + 1) {
        return rem == 0;
    }

    if (memo[idx][rem][prev] != -1) {
        return memo[idx][rem][prev];
    }

    for (int d: divisors[prev]) {
        int remaining_len = n - idx + 1;
        if (rem >= d + (remaining_len - 1) && rem <= d * remaining_len) {
            ans[idx] = d;
            if (dfs(idx + 1, rem - d, d)) {
                return memo[idx][rem][prev] = 1;
            }
        }
    }

    return memo[idx][rem][prev] = 0;
}

void solve() {
    int x;
    cin >> n >> m >> x;

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= x; ++j) {
            for (int k = 0; k <= m; ++k) {
                memo[i][j][k] = -1;
            }
        }
    }

    bool found = false;
    for (int start = 1; start <= m; ++start) {
        if (x >= start + (n - 1) && x <= start * n) {
            ans[1] = start;
            if (dfs(2, x - start, start)) {
                found = true;
                break;
            }
        }
    }

    if (found) {
        for (int i = 1; i <= n; ++i) {
            cout << ans[i] << (i == n ? "" : " ");
        }
        cout << "\n";
    } else {
        cout << -1 << "\n";
    }
}


signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    cin >> T;
    precompute_divisors();
    while (T--)
        solve();
    return 0;
}
