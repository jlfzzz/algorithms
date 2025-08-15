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
    int n;
    cin >> n;
    vector<int> a(n);
    For(i, n) cin >> a[i];
    map<long long, bool> mp;
    int s = 0;
    mp[s] = true;
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        s += a[i];
        if (mp[s]) {
            mp.clear();
            cnt++;
            s = 0;
            mp[s] = 1;
        } else {
            mp[s] = 1;
        }
    }
    cout << cnt << endl;
    mp.clear();
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
