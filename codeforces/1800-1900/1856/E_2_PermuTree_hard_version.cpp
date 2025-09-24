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

void solve() {
    int n;
    cin >> n;

    vector<vector<int>> g(n + 1);
    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        g[p].push_back(i);
        g[i].push_back(p);
    }

    bitset<32> b32;
    bitset<64> b64;
    bitset<128> b128;
    bitset<256> b256;
    bitset<512> b512;
    bitset<1024> b1024;
    bitset<2048> b2048;
    bitset<4096> b4096;
    bitset<8192> b8192;
    bitset<16384> b16384;
    bitset<32768> b32768;
    bitset<65536> b65536;
    bitset<131072> b131072;
    bitset<262144> b262144;
    bitset<524288> b524288;
    bitset<1000005> bmax;

    int ans = 0;
    vector<int> sz(n + 1);
    auto dfs = [&](this auto &&dfs, int u, int fa) -> void {
        sz[u] = 1;
        int mx = 0;
        for (int v: g[u]) {
            if (v == fa)
                continue;
            dfs(v, u);
            sz[u] += sz[v];
            mx = max(mx, sz[v]);
        }

        int S = sz[u] - 1;
        if (S <= 0)
            return;

        if (mx * 2 >= S) {
            ans += mx * (S - mx);
            return;
        }

        vector<int> cnt(S + 1);
        for (int v: g[u])
            if (v != fa)
                cnt[sz[v]]++;
        vector<int> items;
        for (int w = 1; w <= S; w++)
            if (cnt[w]) {
                int c = cnt[w], t = 1;
                while (c) {
                    int use = min(c, t);
                    items.push_back(use * w);
                    c -= use;
                    t <<= 1;
                }
            }

        auto f = [&](int lim) -> int {
            int best = 0;
            auto dp = [&](auto &bs) {
                bs.reset();
                bs[0] = 1;
                for (int w: items)
                    bs |= (bs << w);
                for (int i = S / 2; i >= 0; --i)
                    if (bs[i]) {
                        best = max(best, i * (S - i));
                        break;
                    }
            };

            if (lim <= 32)
                dp(b32);
            else if (lim <= 64)
                dp(b64);
            else if (lim <= 128)
                dp(b128);
            else if (lim <= 256)
                dp(b256);
            else if (lim <= 512)
                dp(b512);
            else if (lim <= 1024)
                dp(b1024);
            else if (lim <= 2048)
                dp(b2048);
            else if (lim <= 4096)
                dp(b4096);
            else if (lim <= 8192)
                dp(b8192);
            else if (lim <= 16384)
                dp(b16384);
            else if (lim <= 32768)
                dp(b32768);
            else if (lim <= 65536)
                dp(b65536);
            else if (lim <= 131072)
                dp(b131072);
            else if (lim <= 262144)
                dp(b262144);
            else if (lim <= 524288)
                dp(b524288);
            else
                dp(bmax);

            return best;
        };

        ans += f(S + 1);
    };

    dfs(1, -1);
    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    while (T--)
        solve();
    return 0;
}
