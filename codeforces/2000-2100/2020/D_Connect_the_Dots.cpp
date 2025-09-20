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
class UnionFind {
public:
    vector<int> parent;
    vector<int> rank;
    int count;

    explicit UnionFind(const int n) : count(n) {
        parent.resize(n);
        rank.resize(n);
        ranges::fill(rank, 1);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    bool unite(int x, int y) {
        int root_x = find(x);
        int root_y = find(y);

        if (root_x == root_y) {
            return false;
        }

        if (rank[root_x] == rank[root_y]) {
            parent[root_x] = root_y;
            rank[root_y] += 1;
        } else if (rank[root_x] > rank[root_y]) {
            parent[root_y] = root_x;
        } else {
            parent[root_x] = root_y;
        }
        count--;
        return true;
    }
};
void solve() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> diff(11, vector<int>(n + 1));
    For(i, m) {
        int a, d, k;
        cin >> a >> d >> k;

        diff[d][a] = max(diff[d][a], k);
    }

    UnionFind uf(n + 1);

    for (int d = 1; d <= 10; d++) {
        auto &v = diff[d];

        for (int i = 1; i <= d; i++) {
            int cnt = 0;
            for (int j = i; j <= n; j += d) {
                if (cnt) {
                    uf.unite(j - d, j);
                    cnt--;
                }
                cnt = max(cnt, v[j]);
            }
        }

        // cout << "uf count is: " << uf.count - 1 << '\n';
    }

    int ans = uf.count - 1;
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
