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
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;
    vector<int> ind(m);
    For(i, m) {
        cin >> ind[i];
        ind[i]--;
    }
    string c;
    cin >> c;

    ranges::sort(c);
    ranges::sort(ind);

    ind.erase(unique(ind.begin(), ind.end()), ind.end());

    For(i, ind.size()) {
        int idx = ind[i];
        s[idx] = c[i];
    }

    cout << s << '\n';
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
