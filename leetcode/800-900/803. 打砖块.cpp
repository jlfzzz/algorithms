#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
using ordered_set = tree<int, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update>;
using ordered_map = tree<int, int, less<>, rb_tree_tag, tree_order_statistics_node_update>;
using ordered_multiset =
    tree<pair<long long, long long>, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update>;

constexpr int N = int(5e5 + 5);
int INIT = [] { return 0; }();

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

class DSU {
public:
    vector<int> parent;
    vector<int> rank;
    vector<int> sz;
    ;
    int count;

    explicit DSU(const int n) : count(n) {
        parent.resize(n);
        rank.resize(n);
        sz.resize(n, 1);
        ranges::fill(rank, 1);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    int get_size(int x) { return sz[find(x)]; }

    bool unite(int x, int y) {
        int root_x = find(x);
        int root_y = find(y);

        if (root_x == root_y) {
            return false;
        }

        if (rank[root_x] == rank[root_y]) {
            parent[root_x] = root_y;
            rank[root_y] += 1;
            sz[root_y] += sz[root_x];
        } else if (rank[root_x] > rank[root_y]) {
            parent[root_y] = root_x;
            sz[root_x] += sz[root_y];
        } else {
            parent[root_x] = root_y;
            sz[root_y] += sz[root_x];
        }
        count--;
        return true;
    }
};

class Solution {
public:
    vector<int> hitBricks(vector<vector<int>> &grid, vector<vector<int>> &hits) {
        int R = SZ(grid);
        int C = SZ(grid[0]);
        int n = R * C;
        DSU dsu(n + 1);

        auto get_id = [&](int r, int c) { return r * C + c; };
        int dx[] = {0, 0, 1, -1};
        int dy[] = {1, -1, 0, 0};

        vvi curr = grid;
        for (auto &h: hits) {
            curr[h[0]][h[1]] = 0;
        }

        F(r, 0, R - 1) {
            F(c, 0, C - 1) {
                if (curr[r][c] == 1) {
                    int u = get_id(r, c);
                    if (r == 0)
                        dsu.unite(u, n);

                    if (r > 0 && curr[r - 1][c] == 1)
                        dsu.unite(u, get_id(r - 1, c));
                    if (c > 0 && curr[r][c - 1] == 1)
                        dsu.unite(u, get_id(r, c - 1));
                }
            }
        }

        int k = SZ(hits);
        vi res(k);

        D(i, k - 1, 0) {
            int r = hits[i][0];
            int c = hits[i][1];

            if (grid[r][c] == 0) {
                res[i] = 0;
                continue;
            }

            int pre = dsu.get_size(n);

            curr[r][c] = 1;
            int u = get_id(r, c);

            if (r == 0)
                dsu.unite(u, n);

            F(j, 0, 3) {
                int nr = r + dx[j];
                int nc = c + dy[j];
                if (nr >= 0 && nr < R && nc >= 0 && nc < C && curr[nr][nc] == 1) {
                    dsu.unite(u, get_id(nr, nc));
                }
            }

            int now = dsu.get_size(n);

            res[i] = max(0, now - pre - 1);
        }

        return res;
    }
};


// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     Solution sol;
// }
