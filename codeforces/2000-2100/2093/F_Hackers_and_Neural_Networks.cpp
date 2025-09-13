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
    int n, m;
    cin >> n >> m;

    vector<string> a(n);
    For(i, n) cin >> a[i];

    vector<vector<string>> b(m, vector<string>(n));
    For(i, m) {
        For(j, n) { cin >> b[i][j]; }
    }

    int best = -1;
    int best_cnt = 0;
    for (int i = 0; i < m; i++) {
        int cnt = 0;
        for (int j = 0; j < n; j++) {
            if (b[i][j] == a[j]) {
                cnt++;
            }
        }

        //cout << "i is :" << i << "cnt is: " << cnt << endl;
        if (cnt > best_cnt) {
            best = i;
            best_cnt = cnt;
        }
    }

    if (best == -1) {
        cout << -1 << '\n';
        return;
    }

    //cout << "best is: " << best << endl;
    int ans = n;
    vector<int> taken(n);
    for (int i = 0; i < n; i++) {
        //cout << b[best][0] << endl;
        if (a[i] == b[best][i]) {
            taken[i] = 1;
        }
    }

    for (int i = 0; i < n; i++) {
        if (!taken[i]) {
            // cout << i << endl;
            bool find = false;
            for (int j = 0; j < m; j++) {
                if (b[j][i] == a[i]) {
                    find = true;
                    break;
                }
            }

            if (!find) {
                cout << -1 << '\n';
                return;
            }

            ans += 2;
        }
    }

    cout << ans << '\n';
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
