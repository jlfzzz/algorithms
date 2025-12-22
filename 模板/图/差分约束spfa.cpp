#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<ll, ll>;
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

/*
【差分约束 · 建图逻辑速查手册】

核心判断：
1. 求【最小值】 -> 必须满足所有下界 -> 跑【最长路】(Longest Path) -> 标准形式：A >= B + w
2. 求【最大值】 -> 必须满足所有上界 -> 跑【最短路】(Shortest Path) -> 标准形式：A <= B + w

---------------------------------------------------------------------------

模式一：最长路模式 (用于求最小值 / 判正环)
【标准形式】：Target >= Source + Weight  (松弛逻辑：if dis[v] < dis[u] + w)

   (1) 题目说：A[i] >= 1 (正整数限制)
       前缀和转化：P[i] - P[i-1] >= 1
       移项整理：  P[i] >= P[i-1] + 1
       建边操作：  add(i-1, i, 1);   // 从 i-1 指向 i，权值为 1

   (2) 题目说：Sum(L, R) = S (区间和限制)
       前缀和转化：P[R] - P[L-1] = S
       拆解等式 (转化为 >=):
       a. P[R] - P[L-1] >= S
          移项：P[R] >= P[L-1] + S
          建边：add(L-1, R, S);

       b. P[R] - P[L-1] <= S
          变号：P[L-1] - P[R] >= -S  (两边乘-1，不等号反向)
          移项：P[L-1] >= P[R] - S
          建边：add(R, L-1, -S);

   (3) 题目说：A[i] <= K (如果有这种上界限制)
       转化：A[i] <= K -> -A[i] >= -K
       前缀和：-(P[i] - P[i-1]) >= -K -> P[i-1] - P[i] >= -K
       移项：P[i-1] >= P[i] - K
       建边：add(i, i-1, -K);

---------------------------------------------------------------------------

模式二：最短路模式 (用于求最大值 / 判负环)
【标准形式】：Target <= Source + Weight  (松弛逻辑：if dis[v] > dis[u] + w)

   (1) 题目说：A[i] >= 1 (正整数限制)
       前缀和转化：P[i] - P[i-1] >= 1
       变号整理：  P[i-1] - P[i] <= -1 (两边乘-1，转化为 <=)
       移项整理：  P[i-1] <= P[i] - 1
       建边操作：  add(i, i-1, -1);  // 注意方向反了，且权值为负

   (2) 题目说：Sum(L, R) = S (区间和限制)
       前缀和转化：P[R] - P[L-1] = S
       拆解等式 (转化为 <=):
       a. P[R] - P[L-1] <= S
          移项：P[R] <= P[L-1] + S
          建边：add(L-1, R, S);

       b. P[R] - P[L-1] >= S
          变号：P[L-1] - P[R] <= -S (两边乘-1，转化为 <=)
          移项：P[L-1] <= P[R] - S
          建边：add(R, L-1, -S);

   (3) 题目说：A[i] <= K (如果有这种上界限制)
       前缀和：P[i] - P[i-1] <= K
       移项：P[i] <= P[i-1] + K
       建边：add(i-1, i, K);

---------------------------------------------------------------------------
*/

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<pii>> g(n + 1, vector<pii>());

    // 建图
    for (int i = 1; i <= n; i++) {

    }

    // 下面的是最短路
    // true = invalid
    auto spfa = [&]() -> bool {
        queue<int> q;
        vector<ll> cnt(n + 1), dis(n + 1, inf), vis(n + 1);

        dis[1] = 0;
        q.push(1);
        vis[1] = true;
        cnt[1] = 1;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            vis[u] = false;

            for (auto &[v, w]: g[u]) {
                if (dis[u] + w < dis[v]) {
                    dis[v] = dis[u] + w;

                    if (!vis[v]) {
                        cnt[v]++; // 入队次数+1
                        if (cnt[v] >= n + 2) {
                            return true; // 检测到负环
                        }
                        q.push(v);
                        vis[v] = true;
                    }
                }
            }
        }
        return false;
    };

    cout << (spfa() ? "YES" : "NO") << '\n';
}
