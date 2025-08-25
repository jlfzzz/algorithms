#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = (ll) 4e18;

void solve2() {
    int n;
    cin >> n;
    vector<ll> a(n + 3, 0), s(n + 3, 0), dp(n + 3, INF), g(n + 3, INF);

    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        s[i] = s[i - 1] + a[i];
        dp[i] = INF;
    }

    g[n + 1] = s[n] - (n - 1);
    dp[n] = a[n];
    g[n] = dp[n] + s[n - 1] - (n - 2);

    ll sufmin = INF;
    for (int i = n - 1; i >= 1; --i) {
        dp[i] = min(dp[i], dp[i + 1] + a[i]);

        sufmin = min(sufmin, g[i + 2]);

        ll extra = 0;
        if (i + 1 <= n)
            extra = max(0LL, a[i + 1] - (ll) i);
        ll cand = a[i] + extra - s[i + 1] + (ll) i + sufmin;
        dp[i] = min(dp[i], cand);
        g[i] = dp[i] + s[i - 1] - (ll) (i - 2);
    }

    cout << dp[1] << '\n';
}

void solve() {
    int n;
    cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<ll> dp(n + 1);
    dp[1] = a[0];
    for (int i = 1; i < n; i++) {
        ll curr_chicken = a[i - 1];
        ll nxt_chicken = a[i];
        dp[i + 1] = min(dp[i] + a[i] - 1, dp[i - 1] + curr_chicken + max(0ll, nxt_chicken - i));
    }
    cout << dp[n] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
