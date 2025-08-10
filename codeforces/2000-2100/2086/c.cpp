#include <bits/stdc++.h>
#include <vector>
using namespace std;
using ll = long long;
#define i128 __int128_t
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
const ll MOD2 = 4611686018427387847;
#define int ll
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

void solve() {
    int n;
    cin >> n;
    vector<int> p(n + 1);
    For(i, n) cin >> p[i + 1];

    int ans = 0;

    For(i, n) {
        int d;
        cin >> d;

        if (p[d] != -1) {
            if (p[d] == d) {
                p[d] = -1;
                ans++;
            } else {
                while (true) {
                    if (p[d] == -1) {
                        break;
                    }
                    ans++;
                    int t = p[d];
                    p[d] = -1;
                    d = t;
                }
            }
        }
        cout << ans << ' ';
    }
    cout << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
