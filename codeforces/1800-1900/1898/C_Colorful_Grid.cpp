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
    int n, m, k;
    cin >> n >> m >> k;

    // 保持你原来的存储布局：row[n][m-1], col[m][n-1] (col indexed by column first)
    vector<vector<char>> row(n, vector<char>(m - 1, 'R'));
    vector<vector<char>> col(m, vector<char>(n - 1, 'R'));

    // 1) 正确的最短路长度（你之前少算了 1）
    int d = (n - 1) + (m - 1);
    if (k < d || ((k - d) % 2 != 0)) {
        cout << "NO\n";
        return;
    }

    // res 表示需要额外增加的边数（相对最短路）
    int res = k - d;

    // 初始化全部为 'R'（已经完成上面），下面按照 AC 代码思路做局部修改
    int colflag = 0; // 用于交替

    if (res % 4 == 0) {
        // 第一列从上到下交替（col[0][i] 对应 map2[i+1][1]）
        for (int i = 0; i < n - 1; ++i) {
            colflag ^= 1;
            col[0][i] = (colflag ? 'R' : 'B');
        }
        // 最后一行从左到右（但只到 m-1 列，也就是 row[n-1][0..m-2]）
        for (int j = 0; j < m - 1; ++j) {
            colflag ^= 1;
            // 原 C 代码是 j from 1..m-1 -> map1[n][j]
            // 这里 row index n-1, column j-1
            if (j < m - 1)
                row[n - 1][j] = (colflag ? 'R' : 'B');
        }
        // 下面三次局部翻转（对应 C 代码里的三个 mapX[...] 赋值）
        colflag ^= 1;
        col[m - 1][n - 2] = (colflag ? 'R' : 'B'); // map2[n-1][m]
        colflag ^= 1;
        row[n - 2][m - 2] = (colflag ? 'R' : 'B'); // map1[n-1][m-1]
        colflag ^= 1;
        col[m - 2][n - 2] = (colflag ? 'R' : 'B'); // map2[n-1][m-1]
    } else {
        // res % 4 != 0 的情形（即 res%4 == 2），按 AC 代码的另一分支
        // 第一列从上到下交替
        for (int i = 0; i < n - 1; ++i) {
            colflag ^= 1;
            col[0][i] = (colflag ? 'R' : 'B');
        }
        // 最后一行到 m-2（map1[n][1..m-2]）
        for (int j = 0; j < m - 2; ++j) {
            colflag ^= 1;
            row[n - 1][j] = (colflag ? 'R' : 'B');
        }
        // 接着一系列局部修改（顺序与 AC 代码保持一致）
        colflag ^= 1;
        col[m - 2][n - 2] = (colflag ? 'R' : 'B'); // map2[n-1][m-1]
        colflag ^= 1;
        row[n - 2][m - 2] = (colflag ? 'R' : 'B'); // map1[n-1][m-1]
        colflag ^= 1;
        col[m - 1][n - 2] = (colflag ? 'R' : 'B'); // map2[n-1][m]
        colflag ^= 1;
        row[n - 1][m - 2] = (colflag ? 'R' : 'B'); // map1[n][m-1]
    }

    cout << "YES\n";

    // 输出横边：n 行，每行 m-1 个
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m - 1; j++) {
            cout << row[i][j];
            if (j + 1 < m - 1)
                cout << ' ';
        }
        cout << '\n';
    }

    // 输出竖边：n-1 行，每行 m 个
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < m; j++) {
            cout << col[j][i];
            if (j + 1 < m)
                cout << ' ';
        }
        cout << '\n';
    }
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
