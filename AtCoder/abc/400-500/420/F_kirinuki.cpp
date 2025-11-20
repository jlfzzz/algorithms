#include <bits/stdc++.h>
using ll = long long;
using namespace std;
const int N = 5e5;

int st[N + 5], top, L[N + 5], R[N + 5];
string s[N + 5];

int main() {
    ll ans = 0;
    int n, m, K;
    cin >> n >> m >> K;
    for (int i = 1; i <= n; i++)
        cin >> s[i], s[i] = ' ' + s[i];
    vector<vector<ll>> cnt(n + 5, vector<ll>(m + 5, 0));
    vector<vector<int>> h(n + 5, vector<int>(m + 5, 0));
    /*
        cnt[i][j] -> 高度不超过i, 长度不超过j时，可组成子矩形的数量
    */
    auto cal = [&](int k, int x, int y) {
        return cnt[k][x + y + 1] - cnt[k][x] - cnt[k][y];
        // 减去重复情况
    };
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (i * j <= K)
                cnt[i][j]++;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            // 长度为j的区间 = 2*长度为j-1的区间 - 长度为[j-2]的区间
            cnt[i][j] = cnt[i][j] + cnt[i][j - 1] * 2;
            if (j > 1)
                cnt[i][j] -= cnt[i][j - 2];
        }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cnt[i][j] += cnt[i - 1][j];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            if (s[i][j] == '#')
                h[i][j] = 0;
            else
                h[i][j] = h[i - 1][j] + 1;
        }
    for (int id = 1; id <= n; id++) {
        for (int i = 1; i <= m; i++) {
            while (top && h[id][i] <= h[id][st[top]]) {
                int c = st[top--];
                R[c] = i - 1;
            }
            L[i] = st[top] + 1, st[++top] = i;
        }
        while (top)
            R[st[top--]] = m;
        for (int i = 1; i <= m; i++)
            ans += cal(h[id][i], i - L[i], R[i] - i);
    }
    cout << ans << endl;
    return 0;
}
