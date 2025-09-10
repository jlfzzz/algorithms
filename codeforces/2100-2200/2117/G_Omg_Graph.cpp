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

class Uf {
public:
    vector<int> fa;
    vector<int> rank;
    vector<int> mn;
    Uf(int n) : fa(n) {
        iota(fa.begin(), fa.end(), 0);
        rank.resize(n);
        ranges::fill(rank, 1);
        mn.assign(n + 1, inf);
    }

    int find(int x) {
        if (fa[x] != x) {
            fa[x] = find(fa[x]);
        }
        return fa[x];
    }

    bool merge(int x, int y, int w) {
        int px = find(x), py = find(y);
        if (px == py) {
            return false;
        }

        int cx = rank[px], cy = rank[py];
        if (cx == cy) {
            fa[py] = px;
            rank[px]++;
            mn[px] = min({mn[px], w, mn[py]});
        } else if (cx > cy) {
            mn[px] = min({mn[px], w, mn[py]});
            fa[py] = px;
        } else {
            mn[py] = min({mn[px], w, mn[py]});
            fa[px] = py;
        }
        return true;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;

    struct info {
        int u, v, w;
    };

    vector<info> vi;
    For(i, m) {
        int u, v, w;
        cin >> u >> v >> w;
        vi.emplace_back(u, v, w);
    }

    Uf uf(n + 1);
    ranges::sort(vi, [](info &a, info &b) { return a.w < b.w; });

    int ans = inf;
    for (auto &[u, v, w]: vi) {
        uf.merge(u, v, w);
        if (uf.find(1) == uf.find(n)) {
            ans = min(ans, uf.mn[uf.find(1)] + w);
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
