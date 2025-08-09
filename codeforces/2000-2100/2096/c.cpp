#include <bits/stdc++.h>
#include <vector>
using namespace std;
using ll = long long;
#define i128 __int128_t
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
const ll MOD2 = 4611686018427387847;
#define int ll
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

void solve() {
    int n;
    cin >> n;

    vector<vector<int>> h(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> h[i][j];
        }
    }

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> b(n);
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }

    auto check = [&](int i, int dx, int dy, vector<vector<int>> &heights) -> bool {
        for (int j = 0; j < n; j++) {
            if (heights[j][i - 1] + dx == heights[j][i] + dy) {
                return false;
            }
        }
        return true;
    };

    auto f = [&](vector<vector<int>> &heights, vector<int> &arr) -> int {
        vector<vector<int>> dp(n, vector<int>(2, inf));
        dp[0][0] = 0;
        dp[0][1] = arr[0];

        for (int i = 1; i < n; i++) {
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++) {
                    if (check(i, j, k, heights)) {
                        if (k == 1) {
                            dp[i][k] = min(dp[i][k], dp[i - 1][j] + arr[i]);
                        } else {
                            dp[i][k] = min(dp[i][k], dp[i - 1][j]);
                        }
                    }
                }
            }
        }
        return min(dp[n - 1][0], dp[n - 1][1]);
    };

    int ans = f(h, b);

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            swap(h[i][j], h[j][i]);
        }
    }
    ans += f(h, a);
    cout << (ans < inf ? ans : -1) << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
// long long solveHor(int n, vector<vector<int>> &h, vector<int> &a) {
//     vector<vector<long long>> dp(n, vector<long long>(2, INF));
//     dp[0][0] = 0;
//     dp[0][1] = a[0];

//     for (int i = 1; i < n; i++) {
//         for (int x = 0; x < 2; x++) {
//             for (int y = 0; y < 2; y++) {
//                 bool ok = true;
//                 for (int j = 0; j < n; j++) {
//                     ok &= (h[i - 1][j] + y != h[i][j] + x);
//                 }
//                 if (ok) {
//                     if (x == 0) {
//                         dp[i][x] = min(dp[i][x], dp[i - 1][y]);
//                     }
//                     if (x == 1) {
//                         dp[i][x] = min(dp[i][x], dp[i - 1][y] + a[i]);
//                     }
//                 }
//             }
//         }
//     }

//     return min(dp[n - 1][0], dp[n - 1][1]);
// }

// void transpose(int n, vector<vector<int>> &h) {
//     for (int i = 0; i < n; i++) {
//         for (int j = i + 1; j < n; j++) {
//             swap(h[i][j], h[j][i]);
//         }
//     }
// }

// void test() {
//     int n;
//     cin >> n;

//     vector<vector<int>> h(n, vector<int>(n));
//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < n; j++) {
//             cin >> h[i][j];
//         }
//     }

//     vector<int> a(n);
//     for (int i = 0; i < n; i++) {
//         cin >> a[i];
//     }

//     vector<int> b(n);
//     for (int i = 0; i < n; i++) {
//         cin >> b[i];
//     }

//     long long horCost = solveHor(n, h, a);
//     transpose(n, h);
//     long long verCost = solveHor(n, h, b);
//     long long totalCost = horCost + verCost;

//     if (totalCost >= INF) {
//         cout << -1 << '\n';
//     } else {
//         cout << totalCost << '\n';
//     }
// }

// int main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(nullptr);

//     int t;
//     cin >> t;
//     for (int i = 0; i < t; i++) {
//         test();
//     }

//     return 0;
// }
