#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
using ll = long long;
#define i128 __int128_t
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
const ll MOD2 = 4611686018427387847;

void init() {}

void solve() {
    int n;
    cin >> n;
    vector<int> cnt(5001);
    int mx = 0, mn = 5001;

    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        cnt[x]++;
        mx = max(mx, x);
        mn = min(mn, x);
    }

    int ans = 0;

    for (int sum = mn * 2; sum <= mx * 2; ++sum) {
        int pairs = 0;
        for (int val = 1; val * 2 <= sum; ++val) {
            int target = sum - val;
            if (target > 5000)
                continue;

            if (val == target)
                pairs += cnt[val] / 2;
            else
                pairs += min(cnt[val], cnt[target]);
        }
        ans = max(ans, pairs * 2);
    }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    // cin >> T;
    while (T--)
        solve();
    return 0;
}
