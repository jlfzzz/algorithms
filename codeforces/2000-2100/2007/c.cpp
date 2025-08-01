#include <bits/stdc++.h>
#include <climits>
#include <vector>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define fori(n) for (int i = 0; i < (n); ++i)
#define ford(n) for (int i = (n) - 1; i >= 0; --i)
constexpr int MOD = int(1e9 + 7);

void init() {}

void solve() {
    ll n, a, b;
    cin >> n >> a >> b;
    vector<ll> nums(n);
    ll g = gcd(a, b);
    fori(n) {
        ll t;
        cin >> t;
        nums[i] = t % g;
    }

    ranges::sort(nums);
    ll ans = nums[n - 1] - nums[0];
    fori(n - 1) { ans = min(ans, nums[i] + g - nums[i + 1]); }
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
