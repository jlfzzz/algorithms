#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define fori(n) for (int i = 0; i < (n); ++i)
#define ford(n) for (int i = (n) - 1; i >= 0; --i)
constexpr int MOD = int(1e9 + 7);

void init() {}

void solve() {
    ll x, y, z, k;
    cin >> x >> y >> z >> k;
    ll mn = min({x, y, z});
    ll mx = max({x,y,z});

    ll ans = 0;

    // 枚举所有可能的因数分解 k = a * b * c
    for (ll a = 1; a <= mx; a++) {
        if (k % a == 0) {
            ll remaining = k / a;
            for (ll b = 1; b <= mx; b++) {
                if (remaining % b == 0) {
                    ll c = remaining / b;

                    // 直接尝试所有6种排列，避免创建vector
                    ll dims[3] = {x, y, z};
                    ll vals[3] = {a, b, c};

                    for (int i = 0; i < 3; i++) {
                        for (int j = 0; j < 3; j++) {
                            for (int k = 0; k < 3; k++) {
                                if (i == j || i == k || j == k) {
                                    continue; // 确保是排列（每个位置不重复）
                                }

                                // vals[i]对应dims[0], vals[j]对应dims[1], vals[k]对应dims[2]
                                if (vals[i] <= dims[0] && vals[j] <= dims[1] && vals[k] <= dims[2]) {
                                    ll ways =
                                        (dims[0] - vals[i] + 1) * (dims[1] - vals[j] + 1) * (dims[2] - vals[k] + 1);
                                    ans = max(ans, ways);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    cout << ans << "\n";
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
