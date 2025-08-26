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
    vector<int> cnt;
    Uf(int n) : fa(n), cnt(n, 1) {
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

    bool merge(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) {
            return false;
        }

        fa[px] = py;
        cnt[py] += cnt[px];
        return true;
    }
};

int DIR[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

void solve() {
    int n, m;
    cin >> n >> m;

    vector<vector<char>> grid(n, vector<char>(m));
    For(i, n) {
        string s;
        cin >> s;
        For(j, m) { grid[i][j] = s[j]; }
    }

    auto id = [&](int i, int j) { return i * m + j; };

    Uf uf(n * m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (auto [dx, dy]: DIR) {
                int ni = i + dx, ny = j + dy;
                if (ni >= 0 && ni < n && ny >= 0 && ny < m) {
                    if (grid[i][j] == '#' && grid[ni][ny] == '#')
                        uf.merge(id(i, j), id(ni, ny));
                }
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        map<int, int> st;
        int cnt = 0;
        for (int j = 0; j < m; j++) {
            int up = i - 1;
            if (up >= 0 && grid[up][j] == '#') {
                int fa = uf.find(id(up, j));
                if (!st.contains(fa)) {
                    cnt += uf.cnt[fa];
                    // if (grid[i][j] == '#') {
                    //     cnt--;
                    // }
                    st[fa]++;
                }
            }
            int down = i + 1;
            if (down < n && grid[down][j] == '#') {
                int fa = uf.find(id(down, j));
                if (!st.contains(fa)) {
                    cnt += uf.cnt[fa];
                    // if (grid[i][j] == '#') {
                    //     cnt--;
                    // }
                    st[fa]++;
                }
            }
        }
        for (int j = 0; j < m; j++) {
            int fa = uf.find(id(i, j));
            if (grid[i][j] != '#') {
                cnt++;
            } else {
                if (!st.contains(fa)) {
                    cnt++;
                }
            }
        }
        ans = max(ans, cnt);
    }

    for (int i = 0; i < m; i++) {
        map<int, int> st;
        int cnt = 0;
        for (int j = 0; j < n; j++) {
            int left = i - 1;
            if (left >= 0 && grid[j][left] == '#') {
                int fa = uf.find(id(j, left));
                if (!st.contains(fa)) {
                    cnt += uf.cnt[fa];
                    // if (grid[j][i] == '#') {
                    //     cnt--;
                    // }
                    st[fa]++;
                }
            }
            int right = i + 1;
            if (right < m && grid[j][right] == '#') {
                int fa = uf.find(id(j, right));
                if (!st.contains(fa)) {
                    cnt += uf.cnt[fa];
                    // if (grid[j][i] == '#') {
                    //     cnt--;
                    // }
                    st[fa]++;
                }
            }
        }
        for (int j = 0; j < n; j++) {
            int fa = uf.find(id(j, i));
            if (grid[j][i] != '#') {
                cnt++;
            } else {
                if (!st.contains(fa)) {
                    cnt++;
                }
            }
        }
        ans = max(ans, cnt);
    }

    cout << ans << endl;
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
