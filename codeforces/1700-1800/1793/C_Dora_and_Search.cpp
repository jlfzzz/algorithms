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
    int n;
    cin >> n;

    vector<int> p(n + 1);
    For(i, n) cin >> p[i + 1];



    int mn = 1;
    int mx = n;
    int l = 1;
    int r = n;

    while (l < r) {
        int tl = l, tr = r;
        while (tl <= n && (p[tl] == mn || p[tl] == mx)) {
            if (p[tl] == mn) {
                mn++;
            } else {
                mx--;
            }
            tl++;
        }

        while (tr >= 1 && (p[tr] == mn || p[tr] == mx)) {
            if (p[tr] == mn) {
                mn++;
            } else {
                mx--;
            }
            tr--;
        }

        if (tl == l && tr == r) {
            break;
        }
        l = tl, r = tr;
    }

    if (r - l + 1 >= 4) {
        cout << l << ' ' << r << '\n';
    } else {
        cout << -1 << '\n';
    }
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
