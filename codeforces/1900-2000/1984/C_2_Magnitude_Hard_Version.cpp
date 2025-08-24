#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define int ll
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(998244353);
const ll MOD2 = 4611686018427387847;
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    For(i, n) cin >> a[i];

    vector<pair<long long, long long>> st; // {value, ways}
    st.push_back({0, 1});

    for (long long x: a) {
        unordered_map<long long, long long> mp;
        mp.reserve(4);
        for (auto [val, ways]: st) {
            long long v1 = val + x;
            long long v2 = llabs(val + x);
            mp[v1] = (mp[v1] + ways) % MOD;
            mp[v2] = (mp[v2] + ways) % MOD;
        }

        long long mn = LLONG_MAX, mx = LLONG_MIN;
        for (auto &[k, v]: mp) {
            if (k < mn)
                mn = k;
            if (k > mx)
                mx = k;
        }

        st.clear();
        st.push_back({mx, mp[mx] % MOD});
        if (mn != mx)
            st.push_back({mn, mp[mn] % MOD});
    }

    // 第一个元素一定是最大值
    cout << st[0].second % MOD << '\n';
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
