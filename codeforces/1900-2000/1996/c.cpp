#include <bits/stdc++.h>
#include <vector>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define fori(n) for (int i = 0; i < (n); ++i)
#define ford(n) for (int i = (n) - 1; i >= 0; --i)
constexpr int MOD = int(1e9 + 7);

void init() {}

void solve() {
    int n, q;
    cin >> n >> q;
    string a, b;
    cin >> a >> b;
    vector<pii> queries(q);
    fori(q) {
        int x, y;
        cin >> x >> y;
        queries[i] = {x - 1, y - 1};
    }
    vector<vector<int>> pre1(n + 1, vector<int>(26));
    vector<vector<int>> pre2(n + 1, vector<int>(26));
    fori(n) {
        for (int j = 0; j < 26; j++) {
            pre1[i + 1][j] = pre1[i][j];
            pre2[i + 1][j] = pre2[i][j];
        }
        pre1[i + 1][a[i] - 'a']++;
        pre2[i + 1][b[i] - 'a']++;
    }

    for (auto &[l, r]: queries) {
        vector<int> diff1(26);
        vector<int> diff2(26);
        for (int i = 0; i < 26; i++) {
            diff1[i] = pre1[r + 1][i] - pre1[l][i];
            diff2[i] = pre2[r + 1][i] - pre2[l][i];
        }
        ll t = 0;
        fori(26) { t += abs(diff1[i] - diff2[i]); }
        cout << t / 2 << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
