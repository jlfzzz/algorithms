#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define db long double
#define pb emplace_back
#define pf emplace_front
#define pob pop_back
#define ep emplace
#define ins insert
#define all(x) (x).begin(), (x).end()
#define all2(x, i) (x).begin() + (i), (x).end()
using pii = pair<ll, ll>;
#define ull unsigned long long
#define vi vector<int>
#define vp vector<pii>
#define vl vector<long long>
#define vvi vector<vector<int>>
#define vvp vector<vector<pii>>
#define vvl vector<vector<long long>>
#define D(i, j, k) for (int(i) = (j); (i) >= (k); (i)--)
#define SZ(a) ((int) (a).size())
#define prq priority_queue
#define fi first
#define se second
constexpr int MOD = int(1e9 + 7);
constexpr long long INF = 0x3f3f3f3f3f3f3f3f;
constexpr int inf = 0x3f3f3f3f;
#define F(i, j, k) for (int(i) = (j); (i) <= (k); (i)++)


class Solution {
public:
    bool pyramidTransition(string bottom, vector<string> &allowed) {
        string groups[6][6]{}; // 三角形底部两个字母 -> [三角形顶部字母]
        for (auto &s: allowed) {
            groups[s[0] - 'A'][s[1] - 'A'] += s[2];
        }

        int n = bottom.size();
        vector<string> pyramid(n);
        for (int i = 0; i < n - 1; i++) {
            pyramid[i].resize(i + 1);
        }
        pyramid[n - 1] = move(bottom);

        // 现在准备填 (i, j) 这个格子
        // 返回继续填能否填完所有格子（从下往上填，每行从左到右填）
        auto dfs = [&](this auto &&dfs, int i, int j) -> bool {
            if (i < 0) { // 所有格子都已填完
                return true;
            }

            if (j == i + 1) { // i 行已填完
                return dfs(i - 1, 0); // 开始填 i-1 行
            }

            // 枚举 (i, j) 填什么字母
            // 这取决于 (i+1, j) 和 (i+1, j+1) 填的字母
            for (char top: groups[pyramid[i + 1][j] - 'A'][pyramid[i + 1][j + 1] - 'A']) {
                pyramid[i][j] = top;
                if (dfs(i, j + 1)) {
                    return true;
                }
            }
            return false;
        };

        // 从倒数第二行开始填
        return dfs(n - 2, 0);
    }
};
