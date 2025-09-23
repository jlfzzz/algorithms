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
    vector<int> a(n + 1);
    For(i, n) cin >> a[i + 1];
    a[0] = -1;
    a.push_back(-1);
    vector<int> ans(n + 1, inf);

    vector<int> pre(n + 1), suf(n + 2);
    vector<int> l(n + 1), r(n + 2);

    for (int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] + a[i];
        l[i] = (a[i] == a[i - 1] ? l[i - 1] + 1 : 1);
    }

    for (int i = n; i >= 1; i--) {
        suf[i] = suf[i + 1] + a[i];
        r[i] = (a[i] == a[i + 1] ? r[i + 1] + 1 : 1);
    }

    for (int i = 1; i <= n; i++) {
        int x = a[i];

        int best = inf;

        if (i > 1 && pre[i - 1] > x) {
            int pos = lower_bound(pre.begin(), pre.begin() + i, pre[i - 1] - x) - pre.begin();
            int lenL = i - pos;
            if (lenL >= 2) {
                int left = l[i - 1];
                if (lenL <= left) {
                    if (left < i - 1)
                        lenL = left + 1;
                    else
                        lenL = inf;
                }
            }
            best = min(best, lenL);
        }

        if (i < n) {
            int pos = upper_bound(pre.begin() + (i + 1), pre.begin() + (n + 1), pre[i] + x) - pre.begin();
            if (pos <= n) {
                int lenR = pos - i;
                if (lenR >= 2) {
                    int right = r[i + 1];
                    if (lenR <= right) {
                        if (right < n - i)
                            lenR = right + 1;
                        else
                            lenR = inf;
                    }
                }
                best = min(best, lenR);
            }
        }

        ans[i] = best;
    }

    for (int i = 1; i <= n; i++) {
        int x = ans[i];
        if (x < 1 || x > n) {
            cout << -1 << ' ';
        } else {
            cout << x << ' ';
        }
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
