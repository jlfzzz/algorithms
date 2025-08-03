#include <bits/stdc++.h>
#include <thread>
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

    ll lcm_ = 1;
    For(i, n) { lcm_ = lcm(lcm_, nums[i]); }
    ll sum = 0;
    For(i, n) { sum += lcm_ / nums[i]; }

    if (sum >= lcm_) {
        cout << -1 << '\n';
    } else {
        For(i, n) { cout << lcm_ / nums[i] << ' '; }
        cout << '\n';
    }
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
