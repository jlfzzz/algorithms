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

    if (n <= 2) {
        cout << 0 << '\n';
        return;
    }

    // auto b = a;
    // ranges::sort(b);
    // b.erase(unique(b.begin(), b.end()), b.end());

    auto f = [&](vector<int> &v) -> int {
        // vector<int> tree(n + 1);

        // auto add = [&](int i) -> void {
        //     i++;
        //     for (; i <= n; i += i & -i) {
        //         tree[i]++;
        //     }
        // };

        // auto query = [&](int i) -> int {
        //     int res = 0;
        //     i++;
        //     while (i) {
        //         res += tree[i];
        //         i -= i & -i;
        //     }
        //     return res;
        // };

        // int ans = 0;
        // add(ranges::lower_bound(b, v[0]) - b.begin());
        // add(ranges::lower_bound(b, v[1]) - b.begin());

        // for (int i = 2; i < n; i++) {
        //     int x = v[i];
        //     int pre = v[i - 1];

        //     int j = tree[n] - query(ranges::lower_bound(b, x) - b.begin());
        //     //j = tree[n] - j;
        //     if (pre > x) {
        //         j--;
        //     }
        //     ans += j;
        // }
        // return ans;
        // int ans = 0;
        // multiset<int> st;
        // st.insert(v[0]);
        // st.insert(v[1]);
        // for (int i = 2; i < n; i++) {
        //     int x = v[i];
        //     auto it = st.upper_bound(x);
        //     if (it != st.end() && v[i - 1] < x) {
        //         ans++;
        //     }
        //     st.insert(x);
        // }
        // return ans;

        int ans = 0;
        deque<int> dq;
        for (int i = 0; i < n; i++) {
            int x = v[i];
            bool same = false;
            while (!dq.empty() && x >= v[dq.back()]) {
                if (x == v[dq.back()]) {
                    same = true;
                }
                dq.pop_back();
            }

            if (!dq.empty() && dq.back() < i - 1 && !same) {
                ans++;
            }
            dq.push_back(i);
        }
        return ans;
    };

    int ans = f(a);
    ranges::reverse(a);
    cout << ans + f(a) << '\n';
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
