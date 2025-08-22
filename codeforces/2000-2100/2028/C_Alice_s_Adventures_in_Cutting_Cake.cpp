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
    int n, m, v;
    cin >> n >> m >> v;
    vector<int> a(n);
    For(i, n) cin >> a[i];

    vector<int> pre(n + 1);
    for (int i = 0; i < n; i++) {
        pre[i + 1] = pre[i] + a[i];
    }

    vector<int> pre_i;
    pre_i.push_back(-1);
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
        if (sum >= v) {
            pre_i.push_back(i);
            sum = 0;
        }
    }

    vector<int> suf_i;
    suf_i.push_back(n);
    sum = 0;
    for (int i = n - 1; i >= 0; i--) {
        sum += a[i];
        if (sum >= v) {
            suf_i.push_back(i);
            sum = 0;
        }
    }

    // ranges::reverse(suf_i);
    // suf_i.insert(suf_i.begin(), -1);

    int ans = -1;
    for (int suf_choose = 0; suf_choose <= m; suf_choose++) {
        int pre_choose = m - suf_choose;
        if (pre_choose < pre_i.size() && pre_choose <= m) {
            int left = pre_i[pre_choose];
            if (suf_choose < suf_i.size()) {
                int right = suf_i[suf_choose];
                if (left < right)
                    ans = max(ans, pre[right] - pre[left + 1]);
            }
        }
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
