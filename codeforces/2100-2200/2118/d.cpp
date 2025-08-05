#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 578;
int t;
int n, k, q;

struct s {
    ll p, d;
} pd[N];

ll a;
int ans;
int vis[N][N][2];

bool dfs(int u, int t, int di) {
    if (vis[u][t][di])
        return 0;
    if (u < 1 || u > n)
        return 1;
    vis[u][t][di] = 1;

    if (!di) { // 向左
        return dfs(u - 1, (t + pd[u].p - pd[u - 1].p) % k, ((t + pd[u].p - pd[u - 1].p) % k == pd[u - 1].d ? 1 : 0));
    } else { // 向右
        return dfs(u + 1, (t + pd[u + 1].p - pd[u].p) % k, ((t + pd[u + 1].p - pd[u].p) % k == pd[u + 1].d ? 0 : 1));
    }
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> t;

    while (t--) {
        cin >> n >> k;

        for (int i = 1; i <= n; i++) {
            cin >> pd[i].p;
        }

        for (int i = 1; i <= n; i++) {
            cin >> pd[i].d;
        }

        cin >> q;

        while (q--) {
            cin >> a;
            ans = 1;
            memset(vis, 0, sizeof(vis));

            for (int i = 1; i <= n; i++) {
                if (pd[i].p >= a) {
                    ans = dfs(i, (pd[i].p - a) % k, (pd[i].d != (pd[i].p - a) % k));
                    break;
                }
            }

            if (ans)
                cout << "YES\n";
            else
                cout << "NO\n";
        }
    }

    return 0;
}
