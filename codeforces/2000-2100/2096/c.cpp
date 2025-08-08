#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

long long solveHor(int n, vector<vector<int>> &h, vector<int> &a) {
    vector<vector<long long>> dp(n, vector<long long>(2, INF));
    dp[0][0] = 0;
    dp[0][1] = a[0];

    for (int i = 1; i < n; i++) {
        for (int x = 0; x < 2; x++) {
            for (int y = 0; y < 2; y++) {
                bool ok = true;
                for (int j = 0; j < n; j++) {
                    ok &= (h[i - 1][j] + y != h[i][j] + x);
                }
                if (ok) {
                    if (x == 0) {
                        dp[i][x] = min(dp[i][x], dp[i - 1][y]);
                    }
                    if (x == 1) {
                        dp[i][x] = min(dp[i][x], dp[i - 1][y] + a[i]);
                    }
                }
            }
        }
    }

    return min(dp[n - 1][0], dp[n - 1][1]);
}

void transpose(int n, vector<vector<int>> &h) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            swap(h[i][j], h[j][i]);
        }
    }
}

void test() {
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

    long long horCost = solveHor(n, h, a);
    transpose(n, h);
    long long verCost = solveHor(n, h, b);
    long long totalCost = horCost + verCost;

    if (totalCost >= INF) {
        cout << -1 << '\n';
    } else {
        cout << totalCost << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        test();
    }

    return 0;
}
