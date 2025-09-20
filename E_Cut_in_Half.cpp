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
    int n, k, x;
    cin >> n >> k >> x;

    vector<int> a(n);
    For(i, n) cin >> a[i];

    map<double, int> cnt;
    for (int x: a) {
        cnt[(double) x]++;
    }


    while (true) {
        auto it = prev(cnt.end());
        double x = it->first;
        int c = it->second;
        if (c >= k) {
            cnt.rbegin()->second -= k;
            cnt[x / 2] += k * 2;
            break;
        }

        k -= (int) c;
        cnt[x / 2] += c * 2;
        cnt.erase(x);
    }

    vector<pair<double, int>> temp;
    for (auto &[k, v]: cnt) {
        temp.emplace_back(k, v);
    }

    ranges::sort(temp);
    ranges::reverse(temp);

    for (auto &[k, v]: temp) {
        if (x > v) {
            x -= v;
        } else {
            cout << fixed << setprecision(20) << k << "\n";
            return;
        }
    }
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
