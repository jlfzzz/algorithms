#include <bits/stdc++.h>
#include <numeric>
#include <unordered_map>
#include <vector>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);

void init() {}

void solve() {
    int n;
    cin >> n;
    vector<int> nums(n);
    For(i, n) { cin >> nums[i]; }

    map<int, int> cnt;
    vector<int> b(n);
    ll s = 0;
    ll mx = 0;
    For(i, n) {
        int x = nums[i];
        cnt[x] += 1;
        if (cnt[x] > 1) {
            mx = max(mx, (ll) x);
        }
        b[i] = mx;
        s += x;
    }


    ll ans = s;

    s = 0;
    mx = 0;
    cnt.clear();
    For(i, n) {
        int x = b[i];
        cnt[x] += 1;
        if (cnt[x] > 1) {
            mx = max(mx, (ll) x);
        }
        b[i] = mx;
        s += x;
    }
    ans += s;
    ll s_b = accumulate(b.begin(), b.end(), 0LL);
    for (int i = n - 1; i >= 0; i--) {
        ans += s_b;
        s_b -= b[i];
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
