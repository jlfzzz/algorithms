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
    int n;
    cin >> n;
    vector<int> a(n);
    For(i, n) cin >> a[i];

    vector<int> moved;
    vector<int> stay;
    int mn = inf;
    for (int i = n - 1; i >= 0; i--) {
        if (a[i] > mn) {
            moved.push_back(a[i] + 1);
        } else {
            stay.push_back(a[i]);
        }
        mn = min(mn, a[i]);
    }


    ranges::sort(stay);
    ranges::sort(moved);

    if (moved.empty()) {
        for (int x: stay)
            cout << x << ' ';
        cout << '\n';
        return;
    }

    int moved_mn = moved[0];
    auto it = ranges::upper_bound(stay, moved_mn);
    for (auto it2 = it; it2 != stay.end(); it2++) {
        moved.push_back(*it2 + 1);
    }

    stay.erase(it, stay.end());
    ranges::sort(moved);
    for (int x: stay)
        cout << x << ' ';
    for (int x: moved)
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
