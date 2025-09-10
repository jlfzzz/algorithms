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
using Matrix = vector<vector<ll>>;

Matrix mat_mul(const Matrix &m1, const Matrix &m2) {
    int n = m1.size();
    int p = m1[0].size();
    int m = m2[0].size();

    Matrix ret(n, vector<ll>(m, 0));
    for (int i = 0; i < n; ++i) {
        for (int k = 0; k < p; ++k) {
            if (m1[i][k] == 0) {
                continue;
            }
            for (int j = 0; j < m; ++j) {
                ret[i][j] = (ret[i][j] + m1[i][k] * m2[k][j]) % MOD;
            }
        }
    }
    return ret;
}

Matrix quick_mul(Matrix mat, int n) {
    int m = mat.size();
    Matrix unit(m, vector<ll>(m, 0));
    for (int i = 0; i < m; ++i) {
        unit[i][i] = 1;
    }

    while (n) {
        if (n & 1) {
            unit = mat_mul(mat, unit);
        }
        mat = mat_mul(mat, mat);
        n >>= 1;
    }
    return unit;
}
void solve() {
    int n;
    cin >> n;

    if (n <= 2) {
        cout << 1 << '\n';
        return;
    }

    Matrix m = {{1, 1}, {1, 0}};
    m = quick_mul(m, n - 2);
    Matrix m2 = {{1, 1}};
    m2 = mat_mul(m2, m);

    cout << m2[0][0] << '\n';
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
