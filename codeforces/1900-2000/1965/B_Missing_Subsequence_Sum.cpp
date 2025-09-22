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
    std::cin >> n >> k;

    int s = k - 1;
    std::vector<int> ans;
    for (int i = 1; i <= s; i *= 2) {
        ans.push_back(i);
        s -= i;
    }
    if (s > 0) {
        ans.push_back(s);
    }
    for (int i = k + 1; i <= n; i *= 2) {
        ans.push_back(i);
    }
    ans.push_back(2 * k + 1);
    std::cout << ans.size() << "\n";
    for (int i = 0; i < ans.size(); i++) {
        std::cout << ans[i] << " \n"[i == ans.size() - 1];
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
