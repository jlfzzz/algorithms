#include <bits/stdc++.h>
#include <vector>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);

void init() {}

void solve() {
    int n, k, q;
    cin >> n >> k >> q;
    vector<int> signs(k + 1, 0);
    vector<int> times(k + 1, 0);

    // 读取k个路标位置
    for (int i = 1; i <= k; i++) {
        cin >> signs[i];
    }
    // 读取k个时间
    for (int i = 1; i <= k; i++) {
        cin >> times[i];
    }

    for (int i = 0; i < q; i++) {
        int d;
        cin >> d;

        // 找到第一个 >= d 的位置
        auto it = lower_bound(signs.begin() + 1, signs.end(), d);
        int pos = distance(signs.begin(), it);

        if (it != signs.end() && *it == d) {
            // 恰好在路标位置
            cout << times[pos] << ' ';
        } else {
            int prev_sign = signs[pos - 1];
            int next_sign = signs[pos];
            int prev_time = times[pos - 1];
            int next_time = times[pos];

            // 线性插值
            long long result =
                prev_time + (long long) (d - prev_sign) * (next_time - prev_time) / (next_sign - prev_sign);
            cout << result << ' ';
        }
    }
    cout << '\n';
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
