#include <bits/stdc++.h>
#include <vector>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);

const int N = 200005;

vector<ll> fac(N), ifac(N);

ll quick_mul(ll base, ll power) {
    ll ans = 1;
    while (power) {
        if (power & 1) {
            ans = ans * base % MOD;
        }
        base = base * base % MOD;
        power >>= 1;
    }
    return ans;
}

void init() {
    fac[0] = 1;
    for (int i = 1; i < N; ++i) {
        fac[i] = fac[i - 1] * i % MOD;
    }
    ifac[N - 1] = quick_mul(fac[N - 1], MOD - 2);
    ifac[0] = 1;
    for (int i = N - 2; i >= 1; i--) {
        ifac[i] = ifac[i + 1] * (i + 1) % MOD;
    }
}

ll C(ll n, ll k) { return fac[n] * ifac[k] % MOD * ifac[n - k] % MOD; }

void solve() {
    int n, k;
    cin >> n >> k;

    int cnt_zero = 0;
    int cnt_one = 0;
    vector<int> nums(n);
    For(i, n) {
        cin >> nums[i];
        if (nums[i] == 1) {
            cnt_one++;
        } else {
            cnt_zero++;
        }
    }
    
    ll ans = 0;
    for (int i = k / 2 + 1; i <= min(k, cnt_one); i++) {
        int zeros = k - i;
        if (zeros <= cnt_zero) {
            ans = (ans + C(cnt_one, i) * C(cnt_zero, zeros) % MOD) % MOD;
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    cin >> T;
    init();
    while (T--)
        solve();
    return 0;
}



// // 快速幂
// ll qpow(ll a, ll b) {
//     ll res = 1;
//     a %= MOD;
//     while (b) {
//         if (b & 1)
//             res = res * a % MOD;
//         a = a * a % MOD;
//         b >>= 1;
//     }
//     return res;
// }

// // 预处理阶乘和逆元
// void init() {
//     fac[0] = ifac[0] = 1;
//     for (int i = 1; i < N; ++i)
//         fac[i] = fac[i - 1] * i % MOD;
//     ifac[N - 1] = qpow(fac[N - 1], MOD - 2);
//     for (int i = N - 2; i >= 1; --i)
//         ifac[i] = ifac[i + 1] * (i + 1) % MOD;
// }

// // 组合数 C(n, k)
// ll C(int n, int k) {
//     if (k < 0 || k > n)
//         return 0;
//     return fac[n] * ifac[k] % MOD * ifac[n - k] % MOD;
// }

// void solve() {
//     int n, k;
//     cin >> n >> k;
//     vector<int> a(n);
//     int cnt1 = 0;
//     for (auto &x: a) {
//         cin >> x;
//         cnt1 += x;
//     }
//     int cnt0 = n - cnt1;

//     ll ans = 0;
//     int min1 = (k + 1) / 2;
//     for (int x = min1; x <= k && x <= cnt1; ++x) {
//         int y = k - x;
//         if (y <= cnt0) {
//             ans = (ans + C(cnt1, x) * C(cnt0, y) % MOD) % MOD;
//         }
//     }

//     cout << ans << '\n';
// }

// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     int T;
//     cin >> T;
//     init();
//     while (T--)
//         solve();
//     return 0;
// }
