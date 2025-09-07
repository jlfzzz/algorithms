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
    vector<int> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        cin >> b[i];

    struct BIT {
        int N;
        vector<int> t;
        void init(int n) {
            N = n;
            t.assign(N + 2, 0);
        }
        void update(int idx, int val) {
            for (; idx <= N; idx += idx & -idx)
                t[idx] = max(t[idx], val);
        }
        int query(int idx) {
            int res = 0;
            for (; idx > 0; idx -= idx & -idx)
                res = max(res, t[idx]);
            return res;
        }
    } bit;

    bit.init(2 * n + 1);

    vector<int> prev(n + 1, 0);
    vector<int> st;
    st.reserve(n);

    for (int i = 1; i <= n; i++) {
        while (!st.empty() && a[st.back()] < a[i])
            st.pop_back();
        prev[i] = st.empty() ? 0 : st.back();
        st.push_back(i);
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int idx_a = (2 * n + 1 - a[i] + 1);
        bit.update(idx_a, i);

        int right = 2 * n + 1 - b[i] + 1;
        int pos = bit.query(right);

        int pre = prev[i];
        int t1 = min(pre, pos);
        int t2 = (b[i] == a[i]) ? (i - pre) : 0;
        int total = t1 + t2;
        ans += total * (n - i + 1);
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
