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
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    For(i, n) cin >> a[i];

    int cnt1 = 0, cnt2 = 0;
    for (int x: a) {
        if (x == 1) {
            cnt1++;
        } else {
            cnt2++;
        }
    }

    int mx = (cnt2 - 1) * 2 + cnt1 - 1;
    if (cnt1 && cnt2) {
        mx++;
    }

    if (k > mx || k < n - 1) {
        cout << -1 << '\n';
        return;
    }

    int lo = n - 1;
    int need = k - lo;

    vector<int> ans;
    for (int i = 0; i < need; i++) {
        ans.push_back(2);
    }
    ans.push_back(2);
    cnt2 -= need + 1;

    int f = true;
    while (cnt1 || cnt2) {
        if (f) {
            ans.push_back(1);
            cnt1--;
        } else {
            if (cnt2 > 0) {
                ans.push_back(2);
                cnt2--;
            } else {
                ans.push_back(1);
                cnt1--;
            }
        }
        f = !f;
    }
    for (int x: ans) {
        cout << x << ' ';
    }
    cout << '\n';
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
