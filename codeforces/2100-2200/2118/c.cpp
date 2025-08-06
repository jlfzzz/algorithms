#include <bit>
#include <bits/stdc++.h>
#include <functional>
#include <queue>
#include <vector>
using namespace std;
using ll = long long;
#define i128 __int128_t
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
const ll MOD2 = 4611686018427387847;
#define ull unsigned long long

void init() {}

void solve() {
    ll n, k;
    cin >> n >> k;

    vector<ll> nums(n);
    For(i, n) cin >> nums[i];

    ll ans = 0;
    priority_queue<ll, vector<ll>, greater<>> pq;
    for (ll x: nums) {
        ans += popcount((unsigned long long) x);
        for (int i = 0; i <= bit_width((ull) k); i++) {
            if (!(x >> i & 1)) {
                pq.emplace(1ll << i);
            }
        }
    }

    while (!pq.empty() && k > 0) {
        ll t = pq.top();
        pq.pop();
        if (k >= t) {
            ans++;
            k -= t;
        } else {
            break;
        }
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
