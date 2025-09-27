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
    int x;
    cin >> x;

    int i = 0;
    int m = bit_width((ull) x);
    vector<int> ans(m);
    while (i < m) {
        while (i < m && (1 << i & x) == 0) {
            i++;
        }
        if (i == m) {
            break;
        }
        int j = i + 1;

        while (j < m && (1 << j & x) != 0) {
            j++;
        }

        int d = j - i;
        if (d == 1) {
            ans[i] = 1;
            i = j;
        } else {
            ans[i] = -1;
            if (j == m) {
                ans.push_back(1);
            } else {
                ans[j] = 1;
            }

            i = j;
            x |= 1 << i;
        }
    }

    cout << ans.size() << '\n';
    for (int x: ans)
        cout << x << ' ';
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
