#include <bits/stdc++.h>

using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long;

const std::string color = "BGRY";

constexpr int inf = 1E9;

int id(int x, int y) {
    assert(x != y);
    if (x > y) {
        std::swap(x, y);
    }
    return y * (y - 1) / 2 + x;
}

void solve() {
    int n, q;
    std::cin >> n >> q;

    std::vector<std::array<int, 2>> c(n);

    for (int i = 0; i < n; i++) {
        std::string s;
        std::cin >> s;

        for (int j = 0; j < 2; j++) {
            c[i][j] = color.find(s[j]);
        }
        assert(c[i][0] < c[i][1]);
    }
    std::vector<std::array<int, 6>> pre(n), nxt(n);
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            pre[i].fill(-1);
        } else {
            pre[i] = pre[i - 1];
        }
        pre[i][id(c[i][0], c[i][1])] = i;
    }
    for (int i = n - 1; i >= 0; i--) {
        if (i == n - 1) {
            nxt[i].fill(n);
        } else {
            nxt[i] = nxt[i + 1];
        }
        nxt[i][id(c[i][0], c[i][1])] = i;
    }

    while (q--) {
        int x, y;
        std::cin >> x >> y;
        x--;
        y--;

        if (x > y) {
            std::swap(x, y);
        }

        int ans = inf;

        for (auto a: c[x]) {
            for (auto b: c[y]) {
                if (a == b) {
                    ans = y - x;
                } else {
                    int w = id(a, b);
                    for (auto z: {nxt[x][w], pre[y][w]}) {
                        if (0 <= z && z < n) {
                            ans = std::min(ans, std::abs(x - z) + std::abs(y - z));
                        }
                    }
                }
            }
        }
        if (ans == inf) {
            ans = -1;
        }
        std::cout << ans << "\n";
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
