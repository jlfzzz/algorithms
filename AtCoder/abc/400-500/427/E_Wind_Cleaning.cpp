#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);
    const vector<int> dx = {-1, 0, 1, 0}, dy = {0, 1, 0, -1};
    int n, m;
    cin >> n >> m;
    vector<string> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    queue<vector<string>> q;
    q.push(a);
    map<vector<string>, int> dis;
    dis[a] = 0;
    while (!q.empty()) {
        auto u = move(q.front());
        q.pop();
        int cnt = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (u[i][j] == '#')
                    cnt++;
        if (cnt == 0) {
            cout << dis[u] << '\n';
            return 0;
        }
        for (int d = 0; d < 4; d++) {
            vector<string> v(n, string(m, '.'));
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (u[i][j] == '#') {
                        int ni = i + dx[d], nj = j + dy[d];
                        if (ni < 0 || ni >= n || nj < 0 || nj >= m)
                            continue;
                        if (u[ni][nj] == 'T')
                            goto nxt; // 不能有垃圾走到高桥身上
                        v[ni][nj] = '#';
                    } else if (u[i][j] == 'T')
                        v[i][j] = 'T';
                }
            }
            if (dis.find(v) != dis.end())
                continue;
            dis[v] = dis[u] + 1;
            q.push(v);
        nxt:;
        }
    }
    cout << -1 << '\n';
}
