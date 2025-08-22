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

// class Seg {
// public:
//     vector<int> tree;
//     int n_;

//     explicit Seg(int n) : n_(n), tree(4 * n) {}

//     void maintain(int o) { tree[o] = tree[o * 2] + tree[o * 2 + 1]; }

//     void update(int i, int val) { update(1, 0, n_ - 1, i, val); }

//     void update(int o, int l, int r, int i, int val) {
//         if (l == r) {
//             tree[o] += val;
//             return;
//         }

//         int m = (l + r) / 2;
//         if (i <= m) {
//             update(o * 2, l, m, i, val);
//         } else {
//             update(o * 2 + 1, m + 1, r, i, val);
//         }
//         maintain(o);
//     }

//     int get_all() { return tree[1]; }
// };

// void solve() {
//     int q;
//     cin >> q;
//     vector<int> a(N + 1);
//     vector<vector<Seg>> segs;

//     {
//         vector<Seg> t;
//         t.emplace_back(1);
//         segs.emplace_back(std::move(t));
//     }

//     for (int i = 1; i < B; i++) {
//         vector<Seg> t;
//         t.reserve(i);
//         for (int j = 0; j < i; j++) {
//             t.emplace_back(B / i + 10);
//         }
//         segs.emplace_back(std::move(t));
//     }

//     For(_, q) {
//         int op, x, y;
//         cin >> op >> x >> y;

//         if (op == 1) {
//             a[x] += y;
//             for (int i = 1; i < B; i++) {
//                 int rem = x % i;
//                 segs[i][rem].update(x / i, y);
//             }
//         } else {
//             int ans = 0;
//             if (x >= B) {
//                 for (int i = 0; i < N / x + 10; i++) {
//                     int j = i * x + y;
//                     if (j <= N) {
//                         ans += a[j];
//                     }
//                 }
//             } else {
//                 assert(y < x);
//                 ans = segs[x][y].get_all();
//             }
//             cout << ans << '\n';
//         }
//     }
// }

const int N = 5e5 + 10;
const int M = sqrt(N);

void solve() {
    int q;
    cin >> q;
    vector<vector<int>> div(M);
    for (int i = 1; i < M; i++)
        div[i].resize(i);
    vector<int> a(N);
    while (q--) {
        int t, x, y;
        cin >> t >> x >> y;
        if (t == 1) {
            a[x] += y;
            for (int i = 1; i < M; i++) {
                div[i][x % i] += y;
            }
        } else {
            if (x < M) {
                cout << div[x][y] << endl;
            } else {
                int ans = 0;
                for (int i = y; i < N; i += x) {
                    ans += a[i];
                }
                cout << ans << endl;
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
