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
const ll MOD2 = 4611686018427387847;
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

void solve() {
    int x;
    cin >> x;

    int d = 1 - 4 * x;
    set<int> ans;

    int ad = abs(d);
    set<int> div;
    for (int i = 1; i * i <= ad; i++) {
        if (ad % i == 0) {
            div.insert(i);
            div.insert(ad / i);
        }
    }

    for (auto a: div) {
        vector<int> va = {a, -a};
        for (auto av: va) {
            int bv = d / av;
            int num = av + bv - 2;
            if (num % 4 == 0) {
                int n = num / 4;
                ans.insert(n);
            }
        }
    }
    cout << ans.size() << endl;
    for (auto n: ans) {
        cout << n << " ";
    }
    cout << endl;
}


signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    solve();
    return 0;
}
