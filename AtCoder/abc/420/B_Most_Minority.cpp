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
    map<int, int> cnt;
    vector<string> votes;
    For(i, n) {
        string s;
        cin >> s;
        votes.emplace_back(s);
    }

    For(i, m) {
        int cnt0 = 0;
        for (int j = 0; j < n; j++) {
            if (votes[j][i] == '0') {
                cnt0++;
            }
        }
        if (cnt0 == 0 || cnt0 == n) {
            for (int j = 0; j < n; j++) {
                cnt[j]++;
            }
            continue;
        }

        if (cnt0 > n - cnt0) {
            for (int j = 0; j < n; j++) {
                if (votes[j][i] == '1') {
                    cnt[j]++;
                }
            }
        } else {
            for (int j = 0; j < n; j++) {
                if (votes[j][i] == '0') {
                    cnt[j]++;
                }
            }
        }
    }

    int mx = 0;
    for (auto &[k, v]: cnt) {
        mx = max(mx, v);
    }

    vector<int> ans;
    for (auto &[k, v]: cnt) {
        if (v == mx) {
            ans.push_back(k);
        }
    }

    for (int x: ans) {
        cout << x + 1 << ' ';
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
