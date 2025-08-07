#include <bits/stdc++.h>
#include <unordered_map>
#include <vector>
using namespace std;
using ll = long long;
#define i128 __int128_t
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
const ll MOD2 = 4611686018427387847;

void init() {}

void solve() {
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    int q;
    cin >> q;

    vector<int> d(n + 1, 0);
    vector<vector<int>> nxt(n + 2, vector<int>(k, n));
    for (int i = n - 1; i >= 0; i--) {
        nxt[i] = nxt[i + 1];
        int mx = *max_element(nxt[i].begin(), nxt[i].end());
        d[i] = 1 + d[mx];
        nxt[i][s[i] - 'a'] = i;
    }

    while (q--) {
        string t;
        cin >> t;
        int pos = -1;
        for (char c: t)
            pos = nxt[pos + 1][c - 'a'];
        cout << d[pos] << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    // cin >> T;
    while (T--)
        solve();
    return 0;
}
