#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
using ordered_set = tree<int, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update>;
using ordered_map = tree<int, int, less<>, rb_tree_tag, tree_order_statistics_node_update>;
using ordered_multiset =
    tree<pair<long long, long long>, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update>;

constexpr int N = int(5e5 + 5);
constexpr int MAX_COMB = 20050;

long long fact[MAX_COMB];
long long inv[MAX_COMB];

long long quick_pow(long long a, long long b) {
    long long res = 1;
    a %= 1000000007;
    while (b) {
        if (b & 1)
            res = (res * a) % 1000000007;
        a = (a * a) % 1000000007;
        b >>= 1;
    }
    return res;
}

void precompute() {
    fact[0] = 1;
    inv[0] = 1;
    for (int i = 1; i < MAX_COMB; i++) {
        fact[i] = (fact[i - 1] * i) % 1000000007;
    }
    inv[MAX_COMB - 1] = quick_pow(fact[MAX_COMB - 1], 1000000007 - 2);
    for (int i = MAX_COMB - 2; i >= 1; i--) {
        inv[i] = (inv[i + 1] * (i + 1)) % 1000000007;
    }
}

int INIT = [] {
    precompute();
    return 0;
}();

using ll = long long;
#define i128 __int128_t
#define db long double
#define pb emplace_back
#define pf emplace_front
#define pob pop_back
#define ep emplace
#define ins insert
#define all(x) (x).begin(), (x).end()
#define all2(x, i) (x).begin() + (i), (x).end()
using pii = pair<ll, ll>;
#define ull unsigned long long
#define vi vector<int>
#define vp vector<pii>
#define vl vector<long long>
#define vvi vector<vector<int>>
#define vvp vector<vector<pii>>
#define vvl vector<vector<long long>>
#define D(i, j, k) for (int(i) = (j); (i) >= (k); (i)--)
#define SZ(a) ((int) (a).size())
#define prq priority_queue
#define fi first
#define se second
constexpr int MOD = int(1e9 + 7);
constexpr long long INF = 0x3f3f3f3f3f3f3f3f;
constexpr int inf = 0x3f3f3f3f;
#define F(i, j, k) for (int(i) = (j); (i) <= (k); (i)++)

class Solution {
public:
    long long comb(int n, int m) {
        if (m < 0 || m > n)
            return 0;
        return fact[n] * inv[m] % MOD * inv[n - m] % MOD;
    }

    vector<int> waysToFillArray(vector<vector<int>> &queries) {
        vi ans;

        for (auto &q: queries) {
            int n = q[0];
            int k = q[1];

            ll tot = 1;

            for (int i = 2; i * i <= k; ++i) {
                if (k % i == 0) {
                    int cnt = 0;
                    while (k % i == 0) {
                        cnt++;
                        k /= i;
                    }
                    tot = (tot * comb(cnt + n - 1, cnt)) % MOD;
                }
            }

            if (k > 1) {
                tot = (tot * (ll) n) % MOD;
            }

            ans.pb((int) tot);
        }
        return ans;
    }
};
