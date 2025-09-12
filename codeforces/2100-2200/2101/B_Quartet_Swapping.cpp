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
    vector<int> a(n);
    For(i, n) cin >> a[i];

    vector<int> odd, even;
    for (int i = 0; i < n; i++) {
        if (i & 1)
            odd.push_back(a[i]);
        else
            even.push_back(a[i]);
    }

    vector<int> odd0 = odd, even0 = even;
    ranges::sort(odd);
    ranges::sort(even);

    auto inv_parity = [&](const vector<int> &b) {
        int m = (int) n + 2;
        vector<int> bit(m + 1, 0);
        auto add = [&](int idx) {
            for (; idx <= m; idx += idx & -idx)
                bit[idx] ^= 1;
        };
        auto sum = [&](int idx) {
            int s = 0;
            for (; idx > 0; idx -= idx & -idx)
                s ^= bit[idx];
            return s;
        };
        int p = 0;
        for (int x: b) {
            p ^= (sum(m) ^ sum((int) x));
            add((int) x);
        }
        return p & 1;
    };

    int pe = inv_parity(even0);
    int po = inv_parity(odd0);
    bool same = (pe == po);

    vector<int> ans(n, 0);
    bool endEven = ((n - 1) % 2 == 0);
    if (endEven) {
        for (int i = 0; i < (int) odd.size(); i++)
            ans[2 * i + 1] = odd[i];
        int ne = (int) even.size();
        if (ne >= 2) {
            for (int i = 0; i < ne - 2; i++)
                ans[2 * i] = even[i];
            if (same) {
                ans[2 * (ne - 2)] = even[ne - 2];
                ans[2 * (ne - 1)] = even[ne - 1];
            } else {
                ans[2 * (ne - 2)] = even[ne - 1];
                ans[2 * (ne - 1)] = even[ne - 2];
            }
        } else if (ne == 1) {
            ans[0] = even[0];
        }
    } else {
        for (int i = 0; i < (int) even.size(); i++)
            ans[2 * i] = even[i];
        int no = (int) odd.size();
        if (no >= 2) {
            for (int i = 0; i < no - 2; i++)
                ans[2 * i + 1] = odd[i];
            if (same) {
                ans[2 * (no - 2) + 1] = odd[no - 2];
                ans[2 * (no - 1) + 1] = odd[no - 1];
            } else {
                ans[2 * (no - 2) + 1] = odd[no - 1];
                ans[2 * (no - 1) + 1] = odd[no - 2];
            }
        } else if (no == 1) {
            ans[1] = odd[0];
        }
    }

    for (int x: ans)
        cout << x << ' ';
    cout << '\n';
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
