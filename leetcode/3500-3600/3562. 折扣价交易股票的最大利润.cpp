
#include <bits/stdc++.h>
using namespace std;
using pll = pair<long long, long long>;
#define i128 __int128_t
#define ull unsigned long long
constexpr int inf = 0x3f3f3f3f / 2;
using pii = pair<int, int>;
using ll = long long;

class Solution {
public:
    int maxProfit(int n, vector<int> &present, vector<int> &future, vector<vector<int>> &hierarchy, int budget) {
        vector<vector<int>> g(n + 1);
        for (auto &v: hierarchy) {
            g[v[0]].push_back(v[1]);
        }

        vector<vector<int>> dp0(n + 1, vector<int>(budget + 1, -1e9)), dp1(n + 1, vector<int>(budget + 1, -1e9));
        auto dfs = [&](this auto &&dfs, int u) -> void {
            int c1 = present[u - 1];
            int val1 = future[u - 1];
            int contrib1 = val1 - c1;
            int contrib0 = val1 - c1 / 2;

            vector<int> f0(budget + 1, -1e9), f1(budget + 1, -1e9), f2(budget + 1, -1e9);

            if (c1 <= budget) {
                f0[c1] = contrib1;
            }
            if (c1 / 2 <= budget) {
                f1[c1 / 2] = contrib0;
            }
            f2[0] = 0;

            for (int v: g[u]) {
                dfs(v);

                vector<int> g0(budget + 1, -1e9), g1(budget + 1, -1e9), g2(budget + 1, -1e9);

                for (int cur = 0; cur <= budget; cur++) {
                    for (int son = 0; cur + son <= budget; son++) {
                        if (f2[cur] > -1e9 && dp0[v][son] > -1e9) {
                            g2[cur + son] = max(g2[cur + son], f2[cur] + dp0[v][son]);
                        }

                        if (f0[cur] > -1e9 && dp1[v][son] > -1e9) {
                            g0[cur + son] = max(g0[cur + son], f0[cur] + dp1[v][son]);
                        }

                        if (f1[cur] > -1e9 && dp1[v][son] > -1e9) {
                            g1[cur + son] = max(g1[cur + son], f1[cur] + dp1[v][son]);
                        }
                    }
                }

                f0.swap(g0);
                f1.swap(g1);
                f2.swap(g2);
            }

            for (int i = 0; i <= budget; i++) {
                dp0[u][i] = max(f0[i], f2[i]);
                dp1[u][i] = max(f1[i], f2[i]);
            }
        };

        dfs(1);

        int ans = 0;
        for (int i = 0; i <= budget; i++) {
            ans = max(ans, dp0[1][i]);
        }
        return ans;
    }
};
