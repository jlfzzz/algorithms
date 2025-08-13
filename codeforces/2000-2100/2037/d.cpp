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
    int n, m, l;
    cin >> n >> m >> l;

    vector<pii> hurdles(n);
    vector<pii> powers(m);

    For(i, n) {
        int x, y;
        cin >> x >> y;
        hurdles[i] = {x, y};
    }
    For(i, m) {
        int x, y;
        cin >> x >> y;
        powers[i] = {x, y};
    }

    priority_queue<int> pq;
    int i = 0;
    int j = 0;
    int power = 1;
    int ans = 0;

    while (i < n) {
        while (j < m and powers[j].first < hurdles[i].first) {
            pq.emplace(powers[j].second);
            j++;
        }

        while (!pq.empty() and power < hurdles[i].second - hurdles[i].first + 2) {
            int x = pq.top();
            pq.pop();
            ans++;
            power += x;
        }
        if (power < hurdles[i].second - hurdles[i].first + 2) {
            cout << -1 << '\n';
            return;
        }
        i++;
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
