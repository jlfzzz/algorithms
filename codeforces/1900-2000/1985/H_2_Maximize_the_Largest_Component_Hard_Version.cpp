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

    vector<string> grid(n);
    For(i, n) cin >> grid[i];

    auto id = [&](int i, int j) { return i * m + j; };

    struct DSU {
        vector<int> fa;
        vector<int> sz;
        DSU(int n) : fa(n), sz(n, 1) {
            for (int i = 0; i < n; ++i)
                fa[i] = i;
        }
        int find(int x) {
            if (fa[x] == x)
                return x;
            return fa[x] = find(fa[x]);
        }
        bool merge(int a, int b) {
            a = find(a);
            b = find(b);
            if (a == b)
                return false;
            fa[a] = b;
            sz[b] += sz[a];
            return true;
        }
    } uf(n * m);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] != '#')
                continue;
            if (j + 1 < m && grid[i][j + 1] == '#')
                uf.merge(id(i, j), id(i, j + 1));
            if (i + 1 < n && grid[i + 1][j] == '#')
                uf.merge(id(i, j), id(i + 1, j));
        }
    }

    vector<int> minR(n * m, n), maxR(n * m, -1), minC(n * m, m), maxC(n * m, -1);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] != '#')
                continue;
            int p = uf.find(id(i, j));
            if (i < minR[p])
                minR[p] = i;
            if (i > maxR[p])
                maxR[p] = i;
            if (j < minC[p])
                minC[p] = j;
            if (j > maxC[p])
                maxC[p] = j;
        }
    }

    vector<ll> rowDots(n, 0), colDots(m, 0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == '.') {
                rowDots[i]++;
                colDots[j]++;
            }
        }
    }

    vector<ll> rowDiff(n + 1, 0), colDiff(m + 1, 0);
    vector<ll> diff2D((n + 1) * (m + 1), 0);

    auto add_rect = [&](int r1, int c1, int r2, int c2, ll val) {
        diff2D[(r1) * (m + 1) + (c1)] += val;
        diff2D[(r2 + 1) * (m + 1) + (c1)] -= val;
        diff2D[(r1) * (m + 1) + (c2 + 1)] -= val;
        diff2D[(r2 + 1) * (m + 1) + (c2 + 1)] += val;
    };

    for (int i = 0; i < n * m; ++i) {
        // 肯定是uf的根节点
        if (maxR[i] == -1)
            continue;
        int r1 = max<int>(0, minR[i] - 1);
        int r2 = min<int>(n - 1, maxR[i] + 1);
        int c1 = max<int>(0, minC[i] - 1);
        int c2 = min<int>(m - 1, maxC[i] + 1);
        ll sz = uf.sz[i];

        rowDiff[r1] += sz;
        rowDiff[r2 + 1] -= sz;
        colDiff[c1] += sz;
        colDiff[c2 + 1] -= sz;
        add_rect(r1, c1, r2, c2, sz);
    }

    vector<ll> rowSum(n, 0), colSum(m, 0);
    {
        ll cur = 0;
        for (int i = 0; i < n; ++i) {
            cur += rowDiff[i];
            rowSum[i] = cur;
        }
    }
    {
        ll cur = 0;
        for (int j = 0; j < m; ++j) {
            cur += colDiff[j];
            colSum[j] = cur;
        }
    }

    for (int i = 0; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            diff2D[i * (m + 1) + j] += diff2D[i * (m + 1) + (j - 1)];
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            diff2D[i * (m + 1) + j] += diff2D[(i - 1) * (m + 1) + j];
        }
    }

    ll ans = 0;
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            ll overlap = diff2D[r * (m + 1) + c];
            ll addedDots = rowDots[r] + colDots[c] - (grid[r][c] == '.' ? 1 : 0);
            ll cand = rowSum[r] + colSum[c] - overlap + addedDots;
            if (cand > ans)
                ans = cand;
        }
    }

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
