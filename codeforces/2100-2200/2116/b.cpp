#include <bits/stdc++.h>
#include <utility>
#include <vector>
using namespace std;
using ll = long long;
#define i128 __int128_t
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(998244353);
const ll MOD2 = 4611686018427387847;


void init() {}

ll q_pow(ll base, ll power) {
    ll ans = 1;
    while (power) {
        if (power & 1) {
            ans = ans * base % MOD;
        }
        base = base * base % MOD;
        power /= 2;
    }
    return ans;
}

void solve() {
    int n;
    cin >> n;
    vector<ll> p(n);
    For(i, n) cin >> p[i];
    vector<ll> q(n);
    For(i, n) cin >> q[i];

    auto mx1 = make_pair(0LL, 0); // 修正：初始化为0LL确保类型一致
    auto mx2 = make_pair(0LL, 0);
    For(i, n) {
        if (p[i] > mx1.first) { // 修正：应该是p[i]，而不是p[0]
            mx1 = {p[i], i};
        }
        if (q[i] > mx2.first) { // 修正：应该是q[i]，而不是q[0]
            mx2 = {q[i], i};
        }
        ll t = 0; // 修正：初始化t变量
        if (mx1.first > mx2.first) {
            t = (q_pow(2, mx1.first) + q_pow(2, q[i - mx1.second])) % MOD;
        } else if (mx2.first > mx1.first) {
            t = (q_pow(2, mx2.first) + q_pow(2, p[i - mx2.second])) % MOD;
        } else {
            // 修正：完成这个分支的逻辑
            if (q[i - mx1.second] > p[i - mx2.second]) {
                t = (q_pow(2, mx1.first) + q_pow(2, q[i - mx1.second])) % MOD;
            } else {
                t = (q_pow(2, mx2.first) + q_pow(2, p[i - mx2.second])) % MOD;
            }
        }
        cout << t << ' ';
    }
    cout << '\n';
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
