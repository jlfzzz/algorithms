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

    // auto temp = a;
    // ranges::sort(temp);
    // temp.erase(unique(temp.begin(), temp.end()), temp.end());

    // int mex = 0;
    // for (int x: temp) {
    //     if (x != mex) {
    //         break;
    //     }
    //     mex++;
    // }

    map<int, int> cnt;
    for (int x: a)
        cnt[x]++;

    int ans = 0;
    bool f = false;
    while (true) {
        if (!cnt.contains(ans)) {
            break;
        }
        int c = cnt[ans];
        if (c == 1) {
            if (f) {
                break;
            }
            ans++;
            f = 1;
            // break;
        } else {
            ans++;
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
