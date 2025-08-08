#include <bits/stdc++.h>
#include <set>
#include <type_traits>
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

void init() {}

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    For(i, n) cin >> a[i];

    vector<int> pre(n + 1);
    vector<int> suf(n + 1);
    For(i, n) {
        pre[i + 1] = pre[i];
        if (a[i] <= k) {
            pre[i + 1]++;
        }
    }
    for (int i = n - 1; i >= 0; i--) {
        suf[i] = suf[i + 1];
        if (a[i] <= k) {
            suf[i]++;
        }
    }

    bool ans = false;
    int l = -1;
    int r = -1;

    for (int i = 1; i <= n - 1; i++) {
        if (2 * pre[i] >= i) {
            if (l == -1) {
                l = i;
            } else if (l != -1 and pre[i] > 1) {
                ans = true;
            }
        }
    }

    for (int i = n - 1; i >= 1; i--) {
        if (2 * suf[i] >= n - i) {
            if (r == -1) {
                r = i;
            } else if (r != -1 and suf[i] > 1) {
                ans = true;
            }
        }
    }

    if (ans || (l != -1 and r != -1 and l < r)) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
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
