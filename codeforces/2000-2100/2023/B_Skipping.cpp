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
    std::cin >> n;

    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    std::vector<int> b(n);
    for (int i = 0; i < n; i++) {
        std::cin >> b[i];
        b[i]--;
    }

    std::vector<int> dp(n, inf);

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> q;
    q.emplace(0LL, 0);

    while (!q.empty()) {
        auto [d, i] = q.top();
        q.pop();

        if (dp[i] != inf) {
            continue;
        }
        dp[i] = d;

        q.emplace(d + a[i], b[i]);
        if (i > 0) {
            q.emplace(d, i - 1);
        }
    }

    int ans = 0;
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
        ans = std::max(ans, sum - dp[i]);
    }
    std::cout << ans << "\n";
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
