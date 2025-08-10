#include <bits/stdc++.h>
#include <vector>
using namespace std;
using ll = long long;
#define i128 __int128_t
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
const ll MOD2 = 4611686018427387847;
#define int ll
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

void solve() {
    int n;
    cin >> n;
    string t;
    cin >> t;

    vector<int> cnt2(2, 0);
    cnt2[0] = 1;
    int odd = 0;
    int cnt = 0;
    int ans = 0;

    for (int j = 0; j < n; ++j) {
        if (t[j] == '0') {
            cnt++;
        }

        ans += cnt2[cnt & 1];
        cnt2[cnt & 1]++;
    }

    cout << ans << '\n';
}

// void solve() {
//     int n;
//     cin >> n;
//     string t;
//     cin >> t;

//     int ans = 0;

//     vector<int> cnt(2, 0);
//     cnt[0] = 1;

//     int pre = 0;
//     for (int j = 0; j < n; ++j) {
//         if (t[j] == '1') {
//             pre++;
//         }

//         int v = ((j + 1) - pre) % 2;
//         if (v < 0) {
//             v += 2;
//         }

//         ans += cnt[v];
//         cnt[v]++;
//     }

//     cout << ans << endl;
// }

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    // cin >> T;
    while (T--)
        solve();
    return 0;
}
