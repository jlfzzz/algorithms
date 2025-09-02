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

    auto ask = [&](vector<int> &v) -> int {
        cout << "? " << v.size() << ' ';
        for (int x: v) {
            cout << x << ' ';
        }
        cout << endl;
        int t;
        cin >> t;
        return t;
    };

    int l = 1, r = n + 1;
    int pos = -1;
    while (l < r) {
        int m = (l + r) / 2;
        vector<int> v;
        for (int i = 1; i <= m; i++) {
            v.push_back(i);
        }

        int t = ask(v);
        if (t > 0) {
            pos = m;
            r = m;
        } else {
            l = m + 1;
        }
    }

    string ans(n + 1, '?');
    if (pos == -1) {
        l = 2, r = n + 1;
        int target = -1;
        while (l < r) {
            int m = (l + r) / 2;
            vector<int> v;
            v.push_back(m), v.push_back(1);

            int t = ask(v);

            if (t != 0) {
                target = m;
                r = m;
            } else {
                l = m + 1;
            }
        }

        assert(target >= 2);
        for (int i = 1; i < target; i++) {
            ans[i] = ')';
        }
        for (int i = target; i <= n; i++) {
            ans[i] = '(';
        }
    } else {
        int pos1 = pos - 1, pos2 = pos;

        for (int i = 1; i <= n - (n & 1); i += 2) {
            int a = i, b = i + 1;
            vector<int> v;
            v.push_back(pos1);
            v.push_back(pos2);
            v.push_back(pos1);
            v.push_back(a);
            v.push_back(b);
            v.push_back(pos2);

            int t = ask(v);
            if (t == 4) {
                ans[a] = '(';
                ans[b] = ')';
            } else if (t == 2) {
                ans[a] = '(';
                ans[b] = '(';
            } else if (t == 3) {
                ans[a] = ')';
                ans[b] = ')';
            } else if (t == 6) {
                ans[a] = ')';
                ans[b] = '(';
            }
        }

        if (n & 1) {
            vector<int> v;
            v.push_back(pos1), v.push_back(n);
            int t = ask(v);
            if (t == 1) {
                ans[n] = ')';
            } else {
                ans[n] = '(';
            }
        }
    }

    ans = ans.substr(1);
    cout << "! " << ans << endl;
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
