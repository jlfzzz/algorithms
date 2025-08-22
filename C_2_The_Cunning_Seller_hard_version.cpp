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
const ll MOD2 = 4611686018427387847;
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

int pow3[27];
int cost[27];

void init() {
    pow3[0] = 1;
    for (int i = 1; i < 27; i++) {
        pow3[i] = pow3[i - 1] * 3;
    }

    cost[0] = 3;
    for (int i = 1; i < 27; i++) {
        cost[i] = pow3[i + 1] + i * pow3[i - 1];
    }
}

void solve() {
    int n, k;
    cin >> n >> k;

    map<int, int> cnt;
    int curr = n;
    int ans = 0;
    int deals = 0;

    while (curr > 0) {
        int i = upper_bound(pow3, pow3 + 27, curr) - pow3 - 1;
        curr -= pow3[i];
        cnt[i]++;
        ans += cost[i];
        deals++;
    }

    if (deals > k) {
        cout << -1 << '\n';
        return;
    }
    if (cnt.find(0) == cnt.end()) {
        cnt[0] = 0;
    }

    for (auto it = prev(cnt.end()); it != cnt.begin() && deals < k; --it) {
        int i = it->first;
        int count = it->second;

        if (count == 0 || i == 0)
            continue;

        int save = cost[i] - 3 * cost[i - 1];
        if (save <= 0)
            continue;

        int can = min(count, (k - deals) / 2);

        if (can > 0) {
            it->second -= can;
            cnt[i - 1] += can * 3;
            ans -= can * save;
            deals += can * 2;
        }
    }

    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
