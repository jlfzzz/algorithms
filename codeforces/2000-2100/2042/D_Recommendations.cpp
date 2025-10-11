#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> l(n), r(n);
    for (int i = 0; i < n; i++) {
        std::cin >> l[i] >> r[i];
    }

    std::vector<int> L(n, -1), R(n, -1);

    std::vector<int> p(n);
    std::iota(p.begin(), p.end(), 0);

    {
        std::sort(p.begin(), p.end(), [&](int i, int j) {
            if (l[i] != l[j]) {
                return l[i] < l[j];
            }
            return r[i] > r[j];
        });
        std::set<int> s;
        for (int j = 0; j < n; j++) {
            int i = p[j];
            auto it = s.lower_bound(r[i]);
            if (it != s.end()) {
                R[i] = *it;
            }
            s.insert(r[i]);
            if (j + 1 < n && l[i] == l[p[j + 1]] && r[i] == r[p[j + 1]]) {
                R[i] = r[i];
            }
        }
    }

    {
        std::sort(p.begin(), p.end(), [&](int i, int j) {
            if (r[i] != r[j]) {
                return r[i] > r[j];
            }
            return l[i] < l[j];
        });
        std::set<int> s;
        for (int j = 0; j < n; j++) {
            int i = p[j];
            auto it = s.upper_bound(l[i]);
            if (it != s.begin()) {
                L[i] = *std::prev(it);
            }
            s.insert(l[i]);
            if (j + 1 < n && l[i] == l[p[j + 1]] && r[i] == r[p[j + 1]]) {
                L[i] = l[i];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        int ans;
        if (L[i] == -1) {
            ans = 0;
        } else {
            ans = R[i] - L[i] - (r[i] - l[i]);
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
