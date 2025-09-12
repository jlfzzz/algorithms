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
    vector<int> a(n);
    For(i, n) cin >> a[i];

    set<int> st;
    for (int x: a)
        st.insert(x);

    vector<int> v;
    for (int x: st) {
        v.push_back(x);
    }

    ranges::sort(v);

    int ans = 0;
    int l = 0;
    for (int r = 0; r < v.size(); r++) {
        while (l < r && v[r] - v[l] >= n) {
            l++;
        }

        ans = max(ans, r - l + 1);
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
