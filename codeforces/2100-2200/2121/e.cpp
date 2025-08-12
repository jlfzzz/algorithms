#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
const ll MOD2 = 4611686018427387847;
#define int ll
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

// 上下界数位dp
// 还有贪心做法，更简单应该

void solve() {
    int l, r;
    cin >> l >> r;

    string s1 = to_string(l);
    string s2 = to_string(r);
    if (s1.size() < s2.size()) {
        swap(s1, s2);
        swap(l, r);
    }

    int n = s1.size(), m = s2.size();
    if (n != m) {
        string t(n - m, ' ');
        s2 = t + s2;
    }

    if (s1 < s2) {
        swap(s1, s2);
    }

    vector memo(n, vector<vector<int>>(2, vector<int>(2, -1)));
    auto dfs = [&](this auto &&dfs, int i, bool is_lo, bool is_hi) -> int {
        if (i == n) {
            return 0;
        }

        int &x = memo[i][is_lo][is_hi];
        if (x != -1) {
            return x;
        }

        int res = inf;
        int hi = is_hi ? s1[i] - '0' : 9;
        int lo = is_lo ? s2[i] - '0' : 0;

        for (int j = lo; j <= hi; j++) {
            res = min(res, dfs(i + 1, is_hi && j == (s1[i] - '0'), is_lo && j == (s2[i] - '0')) + (j == s1[i] - '0') +
                               (j == s2[i] - '0'));
        }
        x = res;
        return res;
    };

    cout << dfs(0, true, true) << '\n';
}






// void solve() {
// 	int l, r;
// 	cin >> l >> r;

// 	string s1 = to_string(l);
// 	string s2 = to_string(r);
// 	int n = s1.length();

// 	vector<vector<vector<int> > > memo(n + 1, vector<vector<int> >(2, vector<int>(2, -1)));

// 	auto dfs = [&](this auto &&dfs, int i, bool is_lo, bool is_hi) -> int {
// 		if (i == n) return 0;

// 		int &res = memo[i][is_lo][is_hi];
// 		if (!is_lo and !is_hi and res != -1) return res;

// 		int t = INT_MAX;
// 		int x1 = s1[i] - '0';
// 		int x2 = s2[i] - '0';
// 		int lo = 0;
// 		int hi = 9;
// 		if (i == 0) lo = 1;

// 		if (is_lo) lo = x1;
// 		if (is_hi) hi = x2;

// 		for (int j = lo; j <= hi; j++) {
// 			int extra = 0;
// 			if (j == x1) extra++;
// 			if (j == x2) extra++;
// 			t = min(t, dfs(i + 1, is_lo and j == lo, is_hi and j == hi) + extra);
// 		}
// 		res = t;
// 		return res;
// 	};
// 	cout << dfs(0, true, true) << '\n';
// }

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
