#include <bits/stdc++.h>
#include <unordered_map>
#include <unordered_set>
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
    int n;
    cin >> n;
    vector<int> nums(n + 1);
    For(i, n) cin >> nums[i + 1];

    string ans(n + 1, '0');
    unordered_map<int, int> cnt;
    for (int i = 1; i <= n; i++) {
        cnt[nums[i]]++;
    }
    // unordered_map<int, set<int>> pos;
    vector<vector<int>> graph(n + 1, vector<int>());

    For(i, n - 1) {
        int x, y;
        cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    auto dfs = [&](this auto &&dfs, int i, int fa, int depth) -> void {
        unordered_set<int> st;
        st.insert(nums[fa]);
        st.insert(nums[i]);
        if (nums[i] == nums[fa]) {
            ans[nums[i]] = '1';
        }
        for (int v: graph[i]) {
            if (v == fa)
                continue;

            if (cnt[nums[v]] > 1 and ans[nums[v]] == '0') {
                if (st.contains(nums[v])) {
                    ans[nums[v]] = '1';
                }
                // pos[nums[v]].insert(depth + 1);
                st.insert(nums[v]);
            }
            dfs(v, i, depth + 1);
        }
    };
    // if (cnt[nums[1]] > 1) {
    //     pos[nums[1]].insert(0);
    // }
    dfs(1, 0, 0);

    // for (auto &[k, st]: pos) {
    //     if (ans[k] == '1')
    //         continue;
    //     for (auto it = st.begin(); it != st.end(); it++) {
    //         if (next(it) != st.end() and *(next(it)) - *it <= 2) {
    //             ans[k] = '1';
    //             break;
    //         }
    //     }
    // }
    cout << ans.substr(1) << '\n';
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
