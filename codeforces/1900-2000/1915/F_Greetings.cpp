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

void solve() {
    int n;
    cin >> n;
    vector<pii> pos(n);
    For(i, n) {
        int a, b;
        cin >> a >> b;
        pos[i] = {a, b};
    }

    ranges::sort(pos);

    vector<int> temp;
    for (auto &[a, b]: pos) {
        temp.push_back(b);
    }

    ranges::sort(temp);

    auto get_id = [&](int val) -> int { return ranges::lower_bound(temp, val) - temp.begin() + 1; };

    vector<int> tree(n + 1);

    auto add = [&](int i) -> void {
        for (; i <= n; i += i & -i) {
            tree[i] += 1;
        }
    };

    auto query = [&](int i) -> int {
        int res = 0;
        while (i) {
            res += tree[i];
            i -= i & -i;
        }
        return res;
    };

    int pre = 0;
    int ans = 0;
    for (auto &[a, b]: pos) {
        int id = get_id(b);

        // cout << id << endl;

        int L = query(id);
        int R = pre - L;

        ans += R;

        pre++;
        add(id);
    }

    cout << ans << '\n';
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
