#include <bits/stdc++.h>
using namespace std;

constexpr int N = int(1e5 + 5);

int INIT = [] { return 0; }();

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using ordered_set = tree<int, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update>;
using ordered_map = tree<int, int, less<>, rb_tree_tag, tree_order_statistics_node_update>;
using pll = pair<long long, long long>;
#define i128 __int128_t
#define ull unsigned long long
constexpr int inf = 0x3f3f3f3f / 2;
using pii = pair<int, int>;
constexpr int MOD = int(1e9 + 7);
using ll = long long;

class Solution {
public:
    vector<int> processQueries(int c, vector<vector<int>> &connections, vector<vector<int>> &queries) {
        vector<vector<int>> g(c + 1);
        for (auto &v: connections) {
            g[v[0]].push_back(v[1]);
            g[v[1]].push_back(v[0]);
        }

        int tot = 0;
        vector<int> id(c + 1);
        vector<priority_queue<int, vector<int>, greater<>>> pqs;
        auto dfs = [&](this auto &&dfs, int u, int fa, priority_queue<int, vector<int>, greater<>> &pq) -> void {
            id[u] = tot;
            pq.push(u);
            for (int v: g[u]) {
                if (v == fa) {
                    continue;
                }
                dfs(v, u, pq);
            }
        };


        for (int i = 1; i <= c; i++) {
            if (!id[i]) {
                priority_queue<int, vector<int>, greater<>> pq;
                dfs(i, 0, pq);
                pqs.emplace_back(pq);
                tot++;
            }
        }

        vector<int> del(c + 1), ans;
        for (auto &q: queries) {
            int op = q[0];
            int x = q[1];

            if (op == 1) {
                if (!del[x]) {
                    ans.push_back(x);
                } else {
                    while (!pqs[id[x]].empty() && del[pqs[id[x]].top()]) {
                        pqs[id[x]].pop();
                    }
                    if (pqs[id[x]].empty()) {
                        ans.push_back(-1);
                    } else {
                        ans.push_back(pqs[id[x]].top());
                    }
                }
            } else {
                del[x] = 1;
            }
        }

        return ans;
    }
};




int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // Solution sol1;
    // ll n = 11;
    // vector<int> nums1{}, nums{};
}
