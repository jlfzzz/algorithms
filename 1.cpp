#include <bits/stdc++.h>
using namespace std;

// Potion Seller
// 目标：(S_t, D_t)。可任意比例混合已购药水，结果是二维点的凸组合。
// 关键：二维下若可达，最多 3 瓶即可（Carathéodory）。
// 优化方案：三瓶情况用极角排序 + 区间最小值在 O(n^2) 解决（而不是 O(n^3) 穷举）。

struct Potion {
    long long s, d, cost;
};

static inline __int128 cross_ll(long long ax, long long ay, long long bx, long long by) {
    return (__int128) ax * by - (__int128) ay * bx;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long S_t, D_t;
    if (!(cin >> n >> S_t >> D_t))
        return 0;

    vector<Potion> all(n);
    for (int i = 0; i < n; i++)
        cin >> all[i].s >> all[i].d >> all[i].cost;

    // 重复点只保留成本最低者，能显著减少规模
    {
        map<pair<long long, long long>, long long> best;
        for (const auto &p: all) {
            pair<long long, long long> key = {p.s, p.d};
            auto it = best.find(key);
            if (it == best.end())
                best[key] = p.cost;
            else
                it->second = min(it->second, p.cost);
        }
        vector<Potion> comp;
        comp.reserve(best.size());
        for (auto &kv: best)
            comp.push_back({kv.first.first, kv.first.second, kv.second});
        all.swap(comp);
        n = (int) all.size();
    }

    const pair<long long, long long> T = {S_t, D_t};

    long long bestCost = (long long) 4e18;
    vector<pair<long long, long long>> bestPick;

    // 1 瓶：必须完全等于目标
    for (int i = 0; i < n; i++) {
        if (all[i].s == S_t && all[i].d == D_t) {
            if (all[i].cost < bestCost) {
                bestCost = all[i].cost;
                bestPick = {{all[i].s, all[i].d}};
            }
        }
    }

    // 2 瓶：通过“无向方向”分组，在每个方向上各取正/负半射线最小成本
    {
        struct PairMin {
            long long pos = (long long) 4e18, neg = (long long) 4e18;
            int ip = -1, in = -1;
        };
        map<pair<long long, long long>, PairMin> bucket; // key: 规范化方向（x>0 或 x=0,y>0）
        auto norm = [](long long x, long long y) {
            long long g = std::gcd(std::llabs(x), std::llabs(y));
            x /= g;
            y /= g;
            if (x < 0 || (x == 0 && y < 0)) {
                x = -x;
                y = -y;
            }
            return make_pair(x, y);
        };
        auto sideDot = [](long long vx, long long vy, long long nx, long long ny) {
            long long dot = vx * nx + vy * ny;
            return (dot > 0) ? 1 : -1; // vx,vy 非零向量
        };
        for (int i = 0; i < n; i++) {
            long long vx = all[i].s - S_t, vy = all[i].d - D_t;
            if (vx == 0 && vy == 0)
                continue; // 已在 1 瓶处理
            auto k = norm(vx, vy);
            auto &pm = bucket[k];
            int sg = sideDot(vx, vy, k.first, k.second);
            if (sg > 0) {
                if (all[i].cost < pm.pos) {
                    pm.pos = all[i].cost;
                    pm.ip = i;
                }
            } else {
                if (all[i].cost < pm.neg) {
                    pm.neg = all[i].cost;
                    pm.in = i;
                }
            }
        }
        for (auto &kv: bucket)
            if (kv.second.ip != -1 && kv.second.in != -1) {
                long long sum = kv.second.pos + kv.second.neg;
                if (sum < bestCost) {
                    bestCost = sum;
                    auto A = all[kv.second.ip];
                    auto B = all[kv.second.in];
                    bestPick = {{A.s, A.d}, {B.s, B.d}};
                }
            }
    }

    // 3 瓶：极角排序 + 区间最小值（O(n^2)）
    {
        struct Vec {
            long long x, y, cost;
            int idx;
        };
        vector<Vec> v;
        v.reserve(n);
        for (int i = 0; i < n; i++) {
            long long x = all[i].s - S_t, y = all[i].d - D_t;
            if (x == 0 && y == 0)
                continue;
            v.push_back({x, y, all[i].cost, i});
        }
        int m = (int) v.size();
        if (m >= 3) {
            auto upper = [](const Vec &a) { return a.y > 0 || (a.y == 0 && a.x > 0); };
            auto cmp = [&](const Vec &a, const Vec &b) {
                bool ua = upper(a), ub = upper(b);
                if (ua != ub)
                    return ua > ub;
                __int128 cr = cross_ll(a.x, a.y, b.x, b.y);
                if (cr != 0)
                    return cr > 0;
                if (a.cost != b.cost)
                    return a.cost < b.cost;
                return a.idx < b.idx;
            };
            sort(v.begin(), v.end(), cmp);

            vector<Vec> arr(2 * m);
            for (int i = 0; i < 2 * m; i++)
                arr[i] = v[i % m];

            int N = 2 * m;
            vector<int> lg(N + 1, 0);
            for (int i = 2; i <= N; i++)
                lg[i] = lg[i >> 1] + 1;
            int K = lg[N] + 1;
            auto better = [&](int p, int q) {
                if (p == -1)
                    return q;
                if (q == -1)
                    return p;
                if (arr[p].cost != arr[q].cost)
                    return arr[p].cost < arr[q].cost ? p : q;
                return (arr[p].idx < arr[q].idx) ? p : q;
            };
            vector<vector<int>> st(K, vector<int>(N, -1));
            for (int i = 0; i < N; i++)
                st[0][i] = i;
            for (int k = 1; k < K; k++) {
                int len = 1 << k, half = len >> 1;
                for (int i = 0; i + len <= N; i++)
                    st[k][i] = better(st[k - 1][i], st[k - 1][i + half]);
            }
            auto queryPos = [&](int L, int R) {
                if (L > R)
                    return -1;
                int k = lg[R - L + 1];
                return better(st[k][L], st[k][R - (1 << k) + 1]);
            };

            auto crossv = [](const Vec &a, const Vec &b) { return cross_ll(a.x, a.y, b.x, b.y); };

            int r = 0;
            for (int i = 0; i < m; i++) {
                if (r < i)
                    r = i;
                while (r + 1 < i + m && crossv(arr[i], arr[r + 1]) > 0)
                    r++;
                for (int j = i + 1; j <= r; j++) {
                    int L = r + 1, R = i + m - 1;
                    if (L > R)
                        continue;
                    int pos = queryPos(L, R);
                    if (pos == -1)
                        continue;
                    long long sum = arr[i].cost + arr[j].cost + arr[pos].cost;
                    if (sum < bestCost) {
                        bestCost = sum;
                        auto A = all[arr[i].idx];
                        auto B = all[arr[j].idx];
                        auto C = all[arr[pos].idx];
                        bestPick = {{A.s, A.d}, {B.s, B.d}, {C.s, C.d}};
                    }
                }
            }
        }
    }

    if (bestPick.empty()) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    cout << (int) bestPick.size() << "\n";
    for (auto &p: bestPick)
        cout << p.first << ' ' << p.second << "\n";
    return 0;
}
