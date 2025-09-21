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
    int n, m;
    cin >> n >> m;
    vector<string> vs(n);
    For(i, n) { cin >> vs[i]; }

    vector<char> nxt(5);
    nxt[0] = 'n';
    nxt[1] = 'a';
    nxt[2] = 'r';
    nxt[3] = 'e';
    nxt[4] = 'k';

    set<char> st;
    st.insert('n');
    st.insert('a');
    st.insert('r');
    st.insert('e');
    st.insert('k');

    // 0是以k结尾
    vector<vector<int>> memo(n, vector<int>(5, -inf));
    auto dfs = [&](this auto &&dfs, int i, int last) -> int {
        if (i == n) {
            return 0;
        }

        int &x = memo[i][last];
        if (x != -1) {
            return x;
        }

        int res = dfs(i + 1, last);

        int score = 0;
        int total_st = 0;
        int cur = last;
        for (char c: vs[i]) {
            if (st.count(c))
                total_st++;
            if (c == nxt[cur]) {
                score++;
                cur++;
                if (cur == 5)
                    cur = 0;
            }
        }

        int cycles = (last + score) / 5;
        int new_last = (last + score) % 5;
        int delta = 10 * cycles - total_st;

        res = max(res, delta + dfs(i + 1, new_last));
        x = res;
        return res;
    };

    int ans = dfs(0, 0);
    ans = max(ans, 0ll);
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
