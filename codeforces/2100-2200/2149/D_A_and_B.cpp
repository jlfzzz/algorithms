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
    int n;
    cin >> n;
    string s;
    cin >> s;

    int ans = inf;
    auto f = [&](char target) -> int {
        vector<int> pos;
        for (int i = 0; i < n; i++)
            if (s[i] == target)
                pos.push_back(i);
        int m = pos.size();
        vector<int> temp(m);
        for (int i = 0; i < m; i++)
            temp[i] = pos[i] - i;
        int mid = temp[m / 2];
        int res = 0;
        for (int i = 0; i < m; i++)
            res += abs(temp[i] - mid);
        return res;
    };

    ans = min(f('a'), f('b'));
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
