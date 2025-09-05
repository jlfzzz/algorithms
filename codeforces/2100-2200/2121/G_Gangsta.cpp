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
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

void solve1() {
    int n;
    string s;
    cin >> n >> s;
    vector<int> a(n + 1);
    a[0] = 0;
    for (int i = 1; i <= n; ++i)
        a[i] = a[i - 1] + (s[i - 1] == '1' ? 1 : -1);

    struct fwt {
        int n;
        vector<int> tree;
        fwt(int n) : n(n), tree(n + 1) {}

        void update(int i, int val) {
            for (; i <= n; i += i & -i) {
                tree[i] += val;
            }
        }

        int query(int i) {
            int res = 0;
            for (; i; i -= i & -i) {
                res += tree[i];
            }
            return res;
        }
    } pre_sum(n + 1), pre_cnt(n + 1);

    auto b = a;
    ranges::sort(b);
    b.erase(unique(b.begin(), b.end()), b.end());

    auto get_id = [&](int val) { return ranges::lower_bound(b, val) - b.begin() + 1; };

    int total = 0;
    int ans = 0;
    for (int i = 0; i <= n; i++) {
        int x = a[i];
        int id = get_id(x);

        int cnt_l = pre_cnt.query(id);
        int sum_l = pre_sum.query(id);

        int cnt_r = i - cnt_l;
        int sum_r = total - sum_l;

        ans += x * cnt_l - sum_l + (sum_r - cnt_r * x);

        total += x;
        pre_sum.update(id, x);
        pre_cnt.update(id, 1);
    }

    for (int i = 1; i <= n; i++) {
        ans += i * (i + 1) / 2;
    }

    cout << ans / 2 << '\n';
}

void solve() {
    int n;
    string s;
    cin >> n >> s;
    vector<int> a(n + 1);
    a[0] = 0;
    for (int i = 1; i <= n; ++i)
        a[i] = a[i - 1] + (s[i - 1] == '1' ? 1 : -1);

    int ans = 0;

    ranges::sort(a);

    for (int i = 0; i <= n; i++) {
        int x = a[i];
        ans += 2 * i * x - n * x;
    }

    for (int i = 1; i <= n; i++) {
        ans += i * (i + 1) / 2;
    }

    cout << ans / 2 << '\n';
}


signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
