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
    int n;
    cin >> n;
    vector<pll> points(n);
    fori(n) {
        int x, y;
        cin >> x >> y;
        points[i] = {x, y};
    }

    int sx, sy, tx, ty;
    cin >> sx >> sy >> tx >> ty;

    ll dx = sx - tx, dy = sy - ty;
    ll d = dx * dx + dy * dy;

    for (auto &[x, y]: points) {
        ll px = x - tx, py = y - ty;
        if (px * px + py * py <= d) {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
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
