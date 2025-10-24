#include <bits/stdc++.h>
using namespace std;

int id[128];
char rid[3];

void solve() {
    int n;
    cin >> n;

    vector<vector<int>> cnt(n, vector<int>(3, 0));

    vector<int> edges[3][3];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            edges[i][j].clear();

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        vector<int> c(3, 0);
        for (char ch: s)
            c[id[ch]]++;
        cnt[i] = c;

        for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 3; y++) {
                if (c[x] > 1 && c[y] == 0)
                    edges[x][y].push_back(i);
            }
        }
    }

    vector<array<int, 4>> ans;

    auto add = [&](int a, int x, int b, int y) { ans.push_back({a, x, b, y}); };

    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            while (!edges[x][y].empty() && !edges[y][x].empty()) {
                int a = edges[x][y].back();
                int b = edges[y][x].back();
                edges[x][y].pop_back();
                edges[y][x].pop_back();
                add(a, x, b, y);
            }
        }
    }

    int p = 0, q = 1, r = 2;
    if (!edges[0][2].empty())
        swap(q, r);

    int m = min({(int) edges[p][q].size(), (int) edges[q][r].size(), (int) edges[r][p].size()});
    for (int i = 0; i < m; i++) {
        int a = edges[p][q][i];
        int b = edges[q][r][i];
        int c = edges[r][p][i];
        add(a, p, b, q);
        add(b, p, c, r);
    }

    cout << ans.size() << "\n";
    for (auto &v: ans) {
        cout << v[0] + 1 << " " << rid[v[1]] << " " << v[2] + 1 << " " << rid[v[3]] << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    id['w'] = 0;
    id['i'] = 1;
    id['n'] = 2;
    rid[0] = 'w';
    rid[1] = 'i';
    rid[2] = 'n';

    int T;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
