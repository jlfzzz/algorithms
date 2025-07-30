#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
constexpr int MOD = int(1e9 + 7);

void init() {}

void solve() {
    int a, b;
    cin >> a >> b;

    int x = min(b, 3 * a - 2 * b);
    int y = 3 * a - b - x;
    cout << 3 << '\n';
    cout << x << ' ' << b << ' ' << y << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
