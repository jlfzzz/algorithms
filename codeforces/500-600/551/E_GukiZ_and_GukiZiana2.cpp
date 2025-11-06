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
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int b_sz = sqrt(n);
    int blocks = (n + b_sz - 1) / b_sz;
    if (blocks == 0) {
        blocks = 1;
    }

    vector<vector<pii>> b(blocks);
    for (int bid = 0; bid < blocks; bid++) {
        for (int i = 0; i < b_sz; i++) {
            if (bid * b_sz + i >= n) {
                break;
            }
            b[bid].emplace_back(a[bid * b_sz + i], bid * b_sz + i);
        }
    }

    for (int bid = 0; bid < blocks; bid++) {
        ranges::sort(b[bid]);
    }

    vector<int> diff(blocks);

    auto rebuild = [&](int bid) -> void {
        for (int i = bid * b_sz; i < n && i < (bid + 1) * b_sz; i++) {
            a[i] += diff[bid];
        }
        diff[bid] = 0;

        b[bid].clear();

        for (int i = 0; i < b_sz; i++) {
            if (bid * b_sz + i >= n) {
                break;
            }
            b[bid].emplace_back(a[bid * b_sz + i], bid * b_sz + i);
        }
        ranges::sort(b[bid]);
    };

    for (int _ = 0; _ < q; _++) {
        int op;
        cin >> op;

        if (op == 1) {
            int l, r, x;
            cin >> l >> r >> x;
            l--, r--;

            int left = l / b_sz;
            int right = r / b_sz;

            if (left == right) {
                // rebuild(left);
                for (int i = l; i <= r; i++) {
                    a[i] += x;
                }
                rebuild(left);
            } else {
                // rebuild(left);
                for (int i = l; i < (left + 1) * b_sz && i < n; i++) {
                    a[i] += x;
                }
                rebuild(left);

                for (int bid = left + 1; bid < right; bid++) {
                    diff[bid] += x;
                }

                // rebuild(right);
                for (int i = right * b_sz; i <= r; i++) {
                    a[i] += x;
                }
                rebuild(right);
            }
        } else {
            int y;
            cin >> y;

            int l = -1, r = -1;
            for (int bid = 0; bid < blocks; bid++) {
                int target = y - diff[bid];
                auto it1 = std::lower_bound(b[bid].begin(), b[bid].end(), pii{target, -inf});
                auto it2 = std::upper_bound(b[bid].begin(), b[bid].end(), pii{target, inf});


                if (it1 != it2) {
                    for (auto it = it1; it != it2; it++) {
                        int pos = it->second;
                        if (l == -1) {
                            l = pos;
                            r = pos;
                        } else {
                            r = pos;
                        }
                    }
                }
            }
            if (l == -1 && r == -1) {
                cout << -1 << '\n';
            } else {
                cout << r - l << '\n';
            }
        }
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
