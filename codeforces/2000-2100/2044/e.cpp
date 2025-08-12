#include <bits/stdc++.h>
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
    long long k, l1, r1, l2, r2;
    cin >> k >> l1 >> r1 >> l2 >> r2;

    long long count = 0;
    long long power = 1; // k^n

    // 枚举 k 的所有幂次
    while (power <= r2) {
        // 对于当前的 k^n = power
        // 我们需要 y = x * power，其中 l2 <= y <= r2
        // 所以 l2/power <= x <= r2/power

        long long min_x = (l2 + power - 1) / power; // 向上取整
        long long max_x = r2 / power; // 向下取整

        // x 还必须在 [l1, r1] 范围内
        min_x = max(min_x, l1);
        max_x = min(max_x, r1);

        if (min_x <= max_x) {
            count += max_x - min_x + 1;
        }

        // 防止溢出
        if (power > r2 / k)
            break;
        power *= k;
    }

    cout << count << "\n";
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
