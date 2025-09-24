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
    int w, f;
    cin >> w >> f;
    int n;
    cin >> n;

    vector<int> s(n + 1);
    For(i, n) cin >> s[i + 1];

    int total = accumulate(s.begin() + 1, s.end(), 0ll);

    static const size_t MAXS = 1000005;
    bitset<MAXS> can;
    can.reset();
    can[0] = 1;
    for (int i = 1; i <= n; i++) {
        can |= (can << (size_t) s[i]);
    }

    int lo = (total + (w + f) - 1) / (w + f);
    int hi = (total + min(w, f) - 1) / min(w, f) + 5;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        int s1 = w * mid, s2 = f * mid;
        int L = max<int>(0, total - s2);
        int R = min<int>(total, s1);
        bool ok = false;
        if (L <= R) {
            for (int x = L; x <= R; x++) {
                if (can[(size_t) x]) {
                    ok = true;
                    break;
                }
            }
        }
        if (ok)
            hi = mid;
        else
            lo = mid + 1;
    }

    cout << lo << '\n';
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
