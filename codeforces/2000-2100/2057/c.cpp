#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
constexpr int MOD = int(1e9 + 7);

void init() {}

#define getbit(x, y) ((x >> y) & 1)

void solve() {
    ll l, r;
    cin >> l >> r;
    ll now = 0;
    for (ll i = 30; i >= 0; i--) {
        if (getbit(l, i) != getbit(r, i)) {
            ll x = (1ll << i) - 1, y = 0;
            x += now, y += now + (1ll << i);
            cout << x << " " << y << " ";
            if (x != l && y != l)
                cout << l << "\n";
            else
                cout << r << "\n";
            return;
        }
        now += getbit(l, i) ? (1ll << i) : 0;
    }
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
