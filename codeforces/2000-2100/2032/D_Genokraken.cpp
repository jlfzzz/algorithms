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
    int n;
    cin >> n;

    auto ask = [&](int a, int b) -> int {
        cout << "? " << a << ' ' << b << endl;
        int t;
        cin >> t;
        return t;
    };

    int first = -1;
    vector<int> ans(n, -1);
    ans[1] = 0;

    for (int i = 2; i < n; i++) {
        int t = ask(1, i);
        if (t == 0) {
            first = i;
            break;
        } else {
            ans[i] = 0;
        }
    }

    if (first == -1) {
        cout << "! ";
        for (int i = 1; i < n; i++) {
            cout << 0 << ' ';
        }
        cout << endl;
        return;
    }

    ans[first] = 1;

    int p1 = 2;
    for (int i = first + 1; i < n; i++) {
        while (ask(p1, i) == 1)
            p1++;
        ans[i] = p1;
        p1++;
    }

    cout << "! ";
    for (int i = 1; i < n; i++) {
        cout << ans[i] << ' ';
    }
    cout << endl;
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
