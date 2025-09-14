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

void init() {}

void solve() {
    int N;
    cin >> N;
    vector<int> L(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> L[i];
    }

    int left = N + 1;
    for (int i = 1; i <= N; i++) {
        if (L[i] == 1) {
            left = i;
            break;
        }
    }

    int right = 0;
    for (int i = N; i >= 1; i--) {
        if (L[i] == 1) {
            right = i;
            break;
        }
    }

    if (left > N && right == 0) {
        cout << 0 << endl;
    } else {
        cout << max(0ll, right - left) << endl;
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    // cin >> T;
    while (T--)
        solve();
    return 0;
}
