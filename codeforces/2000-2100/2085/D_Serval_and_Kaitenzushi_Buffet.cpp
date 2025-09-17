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

    vector<int> d(n + 1);
    For(i, n) cin >> d[i + 1];

    priority_queue<int, vector<int>, greater<>> pq;
    int ans = 0;
    int cnt = 0;
    for (int i = n; i >= 1; i--) {
        if (cnt >= k) {
            cnt -= k;
            pq.emplace(d[i]);
        } else {
            if (!pq.empty() && d[i] > pq.top()) {
                pq.pop();
                pq.emplace(d[i]);
            }
            cnt++;
        }
    }

    while (!pq.empty()) {
        ans += pq.top();
        pq.pop();
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
