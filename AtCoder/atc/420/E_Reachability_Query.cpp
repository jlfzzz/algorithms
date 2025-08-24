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
const ll MOD2 = 4611686018427387847;
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

class Uf {
public:
    vector<int> fa;
    vector<int> cnt_black;

    Uf(int n) : fa(n), cnt_black(n) {
        for (int i = 0; i < n; i++) {
            fa[i] = i;
        }
    }

    int find(int x) {
        int f = fa[x];
        if (f != x) {
            fa[x] = find(f);
        }
        return fa[x];
    }

    void unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) {
            return;
        }

        fa[px] = py;
        cnt_black[py] += cnt_black[px];
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> cols(n);
    Uf uf(n);

    while (q--) {
        int op;
        cin >> op;

        if (op == 1) {
            int u, v;
            cin >> u >> v;
            u--, v--;

            uf.unite(u, v);
        } else if (op == 2) {
            int v;
            cin >> v;
            v--;

            int old = cols[v];
            int fa = uf.find(v);
            if (old) {
                uf.cnt_black[fa]--;
            } else {
                uf.cnt_black[fa]++;
            }
            cols[v] = !old;

            // if (op == 11) {
            //     cout << cols[v] << '\n';
            // }
        } else {
            int v;
            cin >> v;
            v--;

            if (cols[v]) {
                cout << "Yes\n";
                continue;
            }

            int fa = uf.find(v);
            if (uf.cnt_black[fa]) {
                cout << "Yes\n";
            } else {
                cout << "No\n";
            }
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    // cin >> T;
    while (T--)
        solve();
    return 0;
}
