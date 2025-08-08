#include <bits/stdc++.h>
#include <deque>
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

void init() {}

void solve() {
    int n;
    cin >> n; // 先读入n
    vector<int> d(n);
    for (int i = 0; i < n; i++)
        cin >> d[i];

    vector<int> lo(n);
    vector<int> hi(n);
    for (int i = 0; i < n; i++) {
        cin >> lo[i] >> hi[i];
    }

    int r = 0;
    deque<int> dq;
    for (int i = 0; i < n; i++) {
        int curr = d[i];
        if (curr != -1) {
            r += curr;
        } else {
            dq.push_back(i);
        }
        if (r > hi[i]) {
            cout << -1 << '\n';
            return;
        }
        while (r < lo[i]) {
            if (dq.empty()) {
                cout << -1 << '\n';
                return;
            }
            d[dq.back()] = 1;
            r++;
            dq.pop_back();
        }
    }

    // 验证最终结果
    r = 0;
    for (int i = 0; i < n; i++) {
        r += (d[i] == -1 ? 0 : d[i]); // 剩余的-1设为0
        if (r < lo[i] || r > hi[i]) {
            cout << -1 << '\n';
            return;
        }
    }

    // 输出结果
    for (int i = 0; i < n; i++) {
        cout << (d[i] == -1 ? 0 : d[i]) << ' ';
    }
    cout << '\n';
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
