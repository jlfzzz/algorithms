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

constexpr int N = 1e5 + 5;
vector<vector<int>> divisors(N, vector<int>());

void init() {
    for (int i = 2; i <= N; i++) {
        for (int j = i; j <= N; j += i) {
            divisors[j].push_back(i);
        }
    }
}

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    For(i, n) cin >> a[i + 1];

    map<int, vector<int>> st;
    for (int i = 1; i <= n; i++) {
        st[a[i]].push_back(i);
    }


    while (q--) {
        int k, l, r;
        cin >> k >> l >> r;

        vector<pii> temp;
        for (int d: divisors[k]) {
            if (!st.contains(d)) {
                continue;
            }
            auto it = ranges::lower_bound(st[d], l);
            if (it != st[d].end() && *it <= r) {
                temp.emplace_back(*it, d);
            }
        }

        ranges::sort(temp);

        int ans = 0;

        for (auto &[pos, d]: temp) {
            ans += (pos - l) * k;
            while (k % d == 0) {
                k /= d;
            }
            ans += k;
            l = pos + 1;
        }

        ans += max((r - l + 1) * k, 0ll);

        cout << ans << '\n';
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
