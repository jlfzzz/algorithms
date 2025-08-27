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
    int n, x;
    cin >> n >> x;
    string s;
    cin >> s;
    x--;
    int L = -1;
    int R = -1;
    for (int i = x - 1; i >= 0; i--) {
        if (s[i] == '#') {
            L = i;
            break;
        }
    }
    for (int i = x + 1; i < n; i++) {
        if (s[i] == '#') {
            R = i;
            break;
        }
    }

    int ans = inf;
    if (L == -1 && R == -1) {
        ans = 1;
    } else {
        if (L != -1 && R != -1) {
            if (L + 1 > n - R) {
                ans = min({ans, n - x, L + 2});
            } else {
                ans = min(x + 1, n - R + 1);
            }
        } else {
            if (L == -1) {
                ans = min(x + 1, n - R + 1);
            } else {
                ans = min(n - x, L + 2);
            }
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
