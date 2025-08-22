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
const ll MOD2 = 4611686018427387847;
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    For(i, n) cin >> a[i];
    map<int, vector<int>> groups;

    for (int x: a) {
        int rem = x % k;
        groups[rem].push_back(x);
    }

    for (auto &[_, v]: groups) {
        ranges::sort(v);
    }

    int cnt = 0;
    for (auto &[_, v]: groups) {
        cnt += v.size() & 1;
    }

    if (cnt > 1) {
        cout << -1 << '\n';
        return;
    }

    int total = 0;
    int odd_pos = -1;
    for (auto &[rem, v]: groups) {
        int sz = v.size();
        if (sz % 2 == 0) {
            for (int i = 0; i < sz; i += 2) {
                total += (v[i + 1] - v[i]) / k;
            }
        } else {
            odd_pos = rem;
        }
    }

    if (odd_pos == -1) {
        cout << total << '\n';
        return;
    }

    vector<int> &v = groups[odd_pos];
    int sz = v.size();
    if (sz == 1) {
        cout << total << '\n';
        return;
    }

    int ans = inf;
    int m = sz / 2;
    vector<int> pre(m + 1, 0);
    for (int i = 0; i < m; i++) {
        pre[i + 1] = pre[i] + (v[i * 2 + 1] - v[i * 2]) / k;
    }

    vector<int> suf(m + 1, 0);
    for (int i = m - 1; i >= 0; i--) {
        suf[i] = suf[i + 1] + (v[i * 2 + 2] - v[i * 2 + 1]) / k;
    }
    for (int skip = 0; skip < sz; skip++) {
        if (skip % 2 == 0) {
            int left_pairs = skip / 2;
            int right_pairs = left_pairs;
            ans = min(ans, total + pre[left_pairs] + suf[right_pairs]);
        } else {
            int left_pairs = skip / 2;
            int right_pairs = left_pairs;
            int bridge_cost = 0;
            if (skip > 0 && skip < sz - 1) {
                bridge_cost = (v[skip + 1] - v[skip - 1]) / k;
            }

            ans = min(ans, total + pre[left_pairs] + suf[right_pairs + 1] + bridge_cost);
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
