#include <bits/stdc++.h>
#include <unordered_map>
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
    vector<int> S(n);
    For(i, n) cin >> S[i];

    int s = 0;
    unordered_map<int, int> cnt;
    for (int x: S)
        cnt[x]++;

    if (cnt.contains(0)) {
        if (cnt.contains(1)) {
            int t = min(cnt[0], cnt[1]);
            s += t * 2;
            cnt[0] -= t;
            cnt[1] -= t;
        }
    }
    for (auto &[k, v]: cnt) {
        if (k != 0)
            s += k * v;
    }
    s += cnt[0];
    cout << s << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
