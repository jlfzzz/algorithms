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
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    For(i, n) cin >> a[i];

    map<int, int> cnt;
    for (int x: a) {
        cnt[x]++;
    }

    vector<int> keys;
    for (auto &p: cnt) {
        keys.push_back(p.first);
    }

    int ans = 0;
    int sum = 0;
    int left = 0;
    for (int right = 0; right < keys.size(); ++right) {
        if (right > 0 && keys[right] != keys[right - 1] + 1) {
            sum = 0;
            left = right;
        }
        sum += cnt[keys[right]];
        while (keys[right] - keys[left] + 1 > k) {
            sum -= cnt[keys[left]];
            left++;
        }
        ans = max(ans, sum);
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
