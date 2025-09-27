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

struct cmp {
    bool operator()(pii &a, pii &b) {
        int mx1 = max(a.first, a.second);
        int mx2 = max(b.first, b.second);
        return mx1 < mx2;
    }
};

void solve() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);

    priority_queue<pii, vector<pii>, cmp> pq;
    For(i, n) {
        int x, y;
        cin >> x >> y;
        a[i] = x, b[i] = y;
        pq.emplace(x, y);
    }

    int pre = inf;
    int ans = inf;

    bool f = false;
    while (!pq.empty()) {
        auto [x, y] = pq.top();
        pq.pop();

        int mx;
        if (x == -1 || y == 1) {
            mx = max(x, y);

            if (f) {

            } else {

            }
        } else {
        }

        
    }
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
