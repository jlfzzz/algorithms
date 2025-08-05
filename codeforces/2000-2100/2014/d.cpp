#include <bits/stdc++.h>
#include <vector>
using namespace std;
using ll = long long;
#define i128 __int128_t
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
const ll MOD2 = 4611686018427387847;

void init() {}

void solve() {
    int n, d, k;
    cin >> n >> d >> k;

    vector<int> cnt(n + 5, 0); // 差分数组，注意长度要 >= n - d + 1

    for (int i = 0; i < k; i++) {
        int l, r;
        cin >> l >> r;

        // 有效起点范围是 [max(1, l - d + 1), min(r, n - d + 1)]
        int start = max(1, l - d + 1);
        int end = min(r, n - d + 1);
        if (start > end)
            continue;

        cnt[start]++;
        cnt[end + 1]--;
    }

    // 恢复差分
    vector<int> pre(n + 5, 0);
    for (int i = 1; i <= n - d + 1; i++) {
        pre[i] = pre[i - 1] + cnt[i];
    }

    int maxVal = -1, minVal = k + 1;
    int ans1 = 1, ans2 = 1;
    for (int i = 1; i <= n - d + 1; i++) {
        if (pre[i] > maxVal) {
            maxVal = pre[i];
            ans1 = i;
        }
        if (pre[i] < minVal) {
            minVal = pre[i];
            ans2 = i;
        }
    }

    cout << ans1 << ' ' << ans2 << '\n';
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
