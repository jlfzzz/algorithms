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
    int n, q;
    cin >> n >> q;
    vector<int> p(n + 1);
    For(i, n) cin >> p[i + 1];

    set<pii> st;
    for (int i = 1; i <= n; i++) {
        st.emplace(p[i], i);
    }

    while (q--) {
        int l, r, k;
        cin >> l >> r >> k;

        int j = st.lower_bound({k, -1})->second;
        if (j > r || j < l) {
            cout << -1 << ' ';
            continue;
        }

        int need_s = 0, need_b = 0, s = 0, b = 0;
        while (l <= r) {
            int m = (l + r) / 2;

            if (p[m] == k) {
                break;
            } else if (p[m] < k) {
                if (j > m) {
                    s++;
                } else {
                    need_b++;
                }
            } else {
                if (j < m) {
                    b++;
                } else {
                    need_s++;
                }
            }

            if (j < m) {
                r = m - 1;
            } else {
                l = m + 1;
            }
        }

        int have_s = k - 1 - s - need_b;
        int have_b = n - k - b - need_s;
        int mn = min(need_s, need_b);

        // cout << k << endl << s << endl;

        // cout << have_s << endl << have_b << endl;


        if (have_s + mn < need_s || have_b + mn < need_b) {
            cout << -1 << ' ';
            continue;
        }

        cout << mn * 2 + (max(need_b, need_s) - mn) * 2 << ' ';
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
