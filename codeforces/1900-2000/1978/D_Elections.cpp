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
    int n, c;
    cin >> n >> c;
    vector<int> a(n);
    For(i, n) cin >> a[i];

    a[0] += c;
    map<int, int> suf;
    for (int i = 0; i < n; i++) {
        suf[a[i]]++;
    }

    set<int> pre;
    int pre_sum = 0;
    vector<int> ans(n);
    for (int i = 0; i < n; i++) {
        int x = a[i];
        suf[x]--;
        if (suf[x] == 0) {
            suf.erase(x);
        }

        auto it1 = pre.lower_bound(x);
        auto it2 = suf.upper_bound(x);
        int cnt = x;

        if (it1 != pre.end()) {
            cnt += pre_sum;
            ans[i] = i;
            auto it3 = suf.upper_bound(cnt);
            if (it3 != suf.end()) {
                ans[i]++;
            }
        } else if (it2 != suf.end()) {
            cnt += pre_sum;
            ans[i] = i;
            auto it3 = suf.upper_bound(cnt);
            if (it3 != suf.end()) {
                ans[i]++;
            }
        } else {
            ans[i] = 0;
        }

        pre_sum += x;
        pre.insert(x);
    }

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
    cin >> T;
    while (T--)
        solve();
    return 0;
}
