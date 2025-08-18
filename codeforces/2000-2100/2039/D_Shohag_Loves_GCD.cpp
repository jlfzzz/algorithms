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

void init() {}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> S(m);
    For(i, m) cin >> S[i];

    ranges::reverse(S);
    vector<int> ans(n + 1, -1);

    ans[1] = 0;
    for (int i = 2; i <= n; i++) {
        ans[i] = 1;
        if (1 >= m) {
            cout << -1 << '\n';
            return;
        }
    }

    for (int i = 2; i <= n; i++) {
        for (int j = i + i; j <= n; j += i) {
            if (ans[j] == ans[i]) {
                ans[j]++;
                if (ans[j] >= m) {
                    cout << -1 << '\n';
                    return;
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << S[ans[i]] << ' ';
    }
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
