#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

class UnionFind {
public:
    vector<int> fa;
    int cc;

    UnionFind(int n) : fa(n), cc(n) { iota(fa.begin(), fa.end(), 0); }

    int find(int x) {
        if (fa[x] != x)
            fa[x] = find(fa[x]);
        return fa[x];
    }

    bool merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y)
            return false;
        fa[x] = y;
        cc--;
        return true;
    }
};

void solve() {
    int n, m1, m2;
    cin >> n >> m1 >> m2;
    UnionFind uf1(n), uf2(n);
    vector<pii> edges(m1);

    for (int i = 0; i < m1; i++) {
        int u, v;
        cin >> u >> v;
        edges[i] = {u - 1, v - 1};
    }

    for (int i = 0; i < m2; i++) {
        int u, v;
        cin >> u >> v;
        uf2.merge(u - 1, v - 1);
    }

    int remove_cnt = 0;
    for (auto [u, v]: edges) {
        if (uf2.find(u) == uf2.find(v)) {
            uf1.merge(u, v);
        } else {
            remove_cnt++;
        }
    }

    int add_cnt = uf1.cc - uf2.cc;
    cout << remove_cnt + add_cnt << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
