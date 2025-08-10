#include <algorithm>
#include <iostream>


void solve() {
    long long x, y;
    std::cin >> x >> y;
    if (x == y) {
        std::cout << -1 << std::endl;
        return;
    }

    std::cout << ((1ll << 48) - std::max(x, y)) << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
