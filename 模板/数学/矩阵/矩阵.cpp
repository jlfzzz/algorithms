#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
#define i128 __int128_t
#define ull unsigned long long
const ll MOD2 = 4611686018427387847;
#define inf 100'000'005

// m x n
vector<vector<int>> rotate90NonSquare(const vector<vector<int>> &matrix) {
    int m = matrix.size();
    int n = matrix[0].size();
    vector<vector<int>> rotated(n, vector<int>(m));

    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            rotated[j][m - 1 - i] = matrix[i][j];

    return rotated;
}

// n x n
void transpose(int n, vector<vector<int>> &h) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            swap(h[i][j], h[j][i]);
        }
    }
}

int main() {
    vector<vector<int>> mat = {{1, 2, 3, 4}, {5, 6, 7, 8}};
    auto rotated = rotate90NonSquare(mat);

    for (auto &row: rotated) {
        for (auto &val: row)
            cout << val << " ";
        cout << "\n";
    }
    return 0;
}
