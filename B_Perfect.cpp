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
    int n, m, k;
    cin >> n >> m >> k;
    vector<set<int>> st(n);
    vector<int> time(n);
    int ts = 0;
    for (int i = 0; i < k; i++) {
        int A, B;
        cin >> A >> B;
        A--;
        st[A].insert(B);
        if (st[A].size() == m) {
            time[A] = ++ts;
        }
    }

    vector<pii> temp;
    for (int i = 0; i < n; i++) {
        if (st[i].size() == m) {
            temp.push_back({i, time[i]});
            // cout << i + 1 << ' ';
        }
    }

    ranges::sort(temp, [](pii a, pii b) { return a.second < b.second; });

    for (auto &[a, b]: temp) {
        cout << a + 1 << ' ';
    }
    cout << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    // cin >> T;
    while (T--)
        solve();
    return 0;
}
