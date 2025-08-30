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
    map<string, vector<int>> mp;
    For(i, n) {
        string s;
        cin >> s;
        mp[s].push_back(i + 1);
    }

    int x;
    cin >> x;
    string y;
    cin >> y;
    if (mp.contains(y)) {
        for (int i: mp[y]) {
            if (i == x) {
                cout << "Yes\n";
                return;
            }
        }
        cout << "No\n";
    } else {
        cout << "No\n";
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    //  cin >> T;
    while (T--)
        solve();
    return 0;
}
