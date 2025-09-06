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

    struct Info {
        int s, t, id;
    };

    vector<Info> v;
    For(i, n) {
        int a, b;
        cin >> a >> b;
        v.emplace_back(a, b, i + 1);
    }

    ranges::sort(v, [&](const Info &a, const Info &b) { return a.s < b.s; });
    for (int i = 1; i < n; i++) {
        auto &[preL, preR, t1] = v[i - 1];
        auto &[curL, curR, t2] = v[i];
        if (curR < preR) {
            cout << "No\n";
            return;
        }
    }

    vector<int> ans;
    stack<int> stk1;
    for (int i = 0; i < n; i++) {
        auto &[L1, R1, id1] = v[i];
        int ns = (i + 1 < n) ? v[i + 1].s : inf;

        stk1.emplace(i);

        while (!stk1.empty() && v[stk1.top()].t < ns) {
            int j = stk1.top();
            stk1.pop();
            ans.push_back(v[j].id);
        }
    }

    while (!stk1.empty()) {
        int j = stk1.top();
        stk1.pop();
        ans.push_back(v[j].id);
    }

    cout << "Yes\n";
    for (int x: ans) {
        cout << x << ' ';
    }
    cout << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    // cin >> T;
    while (T--)
        solve();
    return 0;
}
