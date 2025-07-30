#include <bits/stdc++.h>
using namespace std;

int solve() {
    string a, b, c;
    cin >> a >> b >> c;

    int n = a.length();
    int m = b.length();

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; i++) {
        dp[i][0] = dp[i - 1][0] + (a[i - 1] == c[i - 1]);
    }
    for (int i = 1; i <= m; i++) {
        dp[0][i] = dp[0][i - 1] + (b[i - 1] == c[i - 1]);
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            dp[i][j] = max(dp[i - 1][j] + (a[i - 1] == c[i + j - 1]), dp[i][j - 1] + (b[j - 1] == c[i + j - 1]));
        }
    }

    return c.size() - dp[n][m];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    while (t--) {
        cout << solve() << "\n";
    }

    return 0;
}
