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

    vector<string> vs(n);
    For(i, n) cin >> vs[i];

    string t;
    cin >> t;
    int m = t.size();

    auto check = [&](const string &s) -> bool {
        int j = 0;
        for (char c: s) {
            if (j < m && c == t[j]) {
                j++;
                if (j == m)
                    return false;
            }
        }
        return true;
    };

    for (auto &s: vs) {
        if (!check(s)) {
            cout << "NO\n";
            return;
        }
    }

    string ans;
    vector<int> pos(n, 0);

    vector<vector<int>> wait(26);
    for (int i = 0; i < n; i++) {
        if (!vs[i].empty()) {
            wait[vs[i][0] - 'a'].push_back(i);
        }
    }

    int j = 0;

    while (true) {
        bool done = true;
        for (int c = 0; c < 26; c++) {
            if (!wait[c].empty()) {
                done = false;
                break;
            }
        }
        if (done)
            break;

        int pick = -1;
        for (int c = 0; c < 26; c++) {
            if (!wait[c].empty() && (j >= m || c != t[j] - 'a')) {
                pick = c;
                break;
            }
        }

        if (pick == -1) {
            pick = t[j] - 'a';
            j++;
        }

        ans.push_back(char('a' + pick));

        vector<int> cur;
        swap(cur, wait[pick]);
        for (int idx: cur) {
            pos[idx]++;
            if (pos[idx] < vs[idx].size()) {
                wait[vs[idx][pos[idx]] - 'a'].push_back(idx);
            }
        }
    }

    cout << "YES\n" << ans << "\n";
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
