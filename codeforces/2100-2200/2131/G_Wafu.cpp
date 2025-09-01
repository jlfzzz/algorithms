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

int mult[100'005];
int cost[100'005];
constexpr int LIMIT = 61;
int ans;

void init() {
    mult[0] = 1;
    int pre = 1;
    for (int i = 1; i <= LIMIT; i++) {
        mult[i] = pre * i % MOD;
        pre = pre * mult[i] % MOD;
    }
    cost[0] = 0;
    int pc = 0;
    for (int i = 1; i <= LIMIT; i++) {
        cost[i] = min(inf, 1 + pc);
        pc = min(inf, pc + cost[i]);
    }
}

void f(int x) {
    if (x == 0)
        return;
    for (int i = 1; i <= LIMIT; i++) {
        if (x <= 0)
            break;
        if (x - cost[i] >= 0) {
            x -= cost[i];
            ans = ans * mult[i] % MOD;
        } else {
            ans = ans * i % MOD;
            x--;
            break;
        }
    }
    f(x);
}

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> s(n);
    For(i, n) cin >> s[i];

    ranges::sort(s);
    ans = 1;

    for (int i = 0; i < n && k > 0; i++) {
        int x = s[i];
        if (x <= LIMIT && cost[x] <= k) {
            ans = ans * mult[x] % MOD;
            k -= cost[x];
        } else {
            ans = ans * x % MOD;
            f(k - 1);
            k = 0;
        }
    }

    cout << ans % MOD << '\n';
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
