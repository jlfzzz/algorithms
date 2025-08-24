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
    int n, L1, R1, L2, R2;
    cin >> n >> L1 >> R1 >> L2 >> R2;

    vector<int> a(n + 1);
    for (int i = 3; i <= n; i++) {
        cin >> a[i];
    }

    if (n == 3) {
        vector<pii> anss;
        for (int i = 0; i <= 9; i++) {
            for (int j = 0; j <= 9; j++) {

                if (i * j % 10 == a[3]) {
                    int ans1 = -1;
                    for (int k = 0; k < 20; k++) {
                        int t = L1 + k;
                        if (t > R1) {
                            break;
                        }
                        if (t % 10 == i) {
                            ans1 = t;
                            break;
                        }
                    }
                    if (ans1 != -1) {
                        int ans2 = -1;
                        for (int k = 0; k < 20; k++) {
                            int t = L2 + k;
                            if (t > R2) {
                                break;
                            }
                            if (t % 10 == j) {
                                ans2 = t;
                                break;
                            }
                        }
                        if (ans2 != -1) {
                            anss.emplace_back(ans1, ans2);
                            // cout << ans1 << ' ' << ans2 << '\n';
                            // return;
                        }
                    }
                }
            }
        }
        if (anss.size() > 0) {
            ranges::sort(anss);
            cout << anss[0].first << ' ' << anss[0].second << '\n';
            return;
        }
    } else {
        vector<pii> anss;
        for (int i = 0; i <= 9; i++) {
            for (int j = 0; j <= 9; j++) {
                if (i * j % 10 == a[3] && j * a[3] % 10 == a[4]) {
                    int ans1 = -1;
                    for (int k = 0; k < 20; k++) {
                        int t = L1 + k;
                        if (t > R1) {
                            break;
                        }
                        if (t % 10 == i) {
                            ans1 = t;
                            break;
                        }
                    }
                    if (ans1 != -1) {
                        int ans2 = -1;
                        for (int k = 0; k < 20; k++) {
                            int t = L2 + k;
                            if (t > R2) {
                                break;
                            }
                            if (t % 10 == j) {
                                ans2 = t;
                                break;
                            }
                        }
                        if (ans2 != -1) {
                            // cout << ans1 << ' ' << ans2 << '\n';
                            // return;
                            anss.emplace_back(ans1, ans2);
                        }
                    }
                }
            }
        }
        if (anss.size() > 0) {
            ranges::sort(anss);
            cout << anss[0].first << ' ' << anss[0].second << '\n';
            return;
        }
    }
    cout << -1 << ' ' << -1 << '\n';
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
