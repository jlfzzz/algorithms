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

int arr[50];

void init() {
    for (int i = 1; i <= 30; i++) {
        arr[i] = i * (i + 1) / 2;
    }
    for (int i = 31; i < 50; i++) {
        arr[i] = inf;
    }
    arr[0] = 0;
}

void solve() {

    int n, k;
    cin >> n >> k;

    vector<int> ans(n);
    int i = upper_bound(arr, arr + 50, k) - arr - 1;

    if (i == 0) {
        fill(ans.begin(), ans.end(), -1);
    } else {
        for (int j = 0; j < i; j++) {
            ans[j] = 2;
        }
        int d = k - arr[i];

        if (d == 0) {
            for (int j = i; j < n; j++) {
                ans[j] = -1000;
            }
        } else {
            for (int j = i + 1; j < n; j++) {
                ans[j] = -1000;
            }

            if (i <= n - 1)
                ans[i] = 2 * (d - i) - 1;
        }
    }

    for (int x: ans)
        cout << x << ' ';
    cout << '\n';
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
