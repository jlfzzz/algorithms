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
    int n;
    cin >> n;
    vector<int> arr(n + 1);
    For(i, n) { cin >> arr[i + 1]; }

    vector<int> cnt(n + 1);
    for (int i = 1; i <= n; i++) {
        cnt[arr[i]]++;
    }

    int pos = -1;
    int multi = -1;
    for (int i = 1; i <= n; i++) {
        if (cnt[i] == 0) {
            pos = i;
        } else if (cnt[i] > 1) {
            multi = i;
        }
    }
    if (pos != -1) {
        cout << "?" << ' ' << pos << ' ' << multi << endl;
        int x;
        cin >> x;
        if (x == 0) {
            cout << "! A" << endl;
        } else {
            cout << "! B" << endl;
        }
    } else {
        int idx_for_1, idx_for_n; // 用更清晰的变量名
        for (int i = 1; i <= n; i++) {
            if (arr[i] == 1) {
                idx_for_1 = i;
            }
            if (arr[i] == n) {
                idx_for_n = i;
            }
        }

        // 第一次查询：从 x 坐标为 1 的点到 x 坐标为 n 的点
        cout << "? " << idx_for_1 << " " << idx_for_n << endl;
        int r1; // response 1
        cin >> r1;

        if (r1 < n - 1) {
            // 结果小于 n-1，不可能是对象 B，必然是对象 A
            cout << "! A" << endl;
        } else if (r1 > n - 1) {
            // 结果大于 n-1，不可能是对象 A，必然是对象 B
            cout << "! B" << endl;
        } else {
            // 当 r1 == n-1 时，情况模棱两可，需要第二次查询
            // 第二次查询：反向查询
            cout << "? " << idx_for_n << " " << idx_for_1 << endl;
            int r2; // response 2
            cin >> r2;

            if (r2 == n - 1) {
                // 距离对称，结果仍然是 n-1，必然是对象 B
                cout << "! B" << endl;
            } else {
                // 距离不对称，结果变小 (如 0 或 1)，必然是对象 A
                cout << "! A" << endl;
            }
        }
    }
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
