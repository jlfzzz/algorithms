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
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') {
            cnt++;
        }
        if (cnt == k) {
            cout << "NO\n";
            return;
        }
        if (i - k + 1 >= 0) {
            if (s[i - k + 1] == '1') {
                cnt--;
            }
        }
    }

    int low = 1, high = n;
    vector<int> ans(n);
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') {
            ans[i] = low++;
        } else {
            ans[i] = high--;
        }
    }
    cout << "YES\n";
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
