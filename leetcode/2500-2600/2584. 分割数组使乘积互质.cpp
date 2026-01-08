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
int INIT = [] { return 0; }();

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


struct Sieve {
    bool is_not_prime[N + 1]{};
    std::vector<int> primes;
    int min_prime_factor[N + 1]{};
    int distinct_factors_count[N + 1]{}; // 不同质因子个数

    int divisor_count[N + 1]{}; // 约数个数
    int cnt_exp[N + 1]{}; // 最小质因子的指数

    Sieve() { init(N); }

    void init(int n) {
        is_not_prime[0] = is_not_prime[1] = true;
        min_prime_factor[0] = min_prime_factor[1] = 0;
        distinct_factors_count[1] = 0;

        divisor_count[1] = 1;
        cnt_exp[1] = 0;

        for (int i = 2; i <= n; ++i) {
            if (!is_not_prime[i]) {
                primes.push_back(i);
                min_prime_factor[i] = i;
                distinct_factors_count[i] = 1;

                cnt_exp[i] = 1;
                divisor_count[i] = 2;
            }

            for (int p: primes) {
                long long x = 1LL * i * p;
                if (x > n)
                    break;
                is_not_prime[i * p] = true;
                min_prime_factor[i * p] = p;

                if (i % p == 0) {
                    distinct_factors_count[i * p] = distinct_factors_count[i];

                    cnt_exp[i * p] = cnt_exp[i] + 1;
                    divisor_count[i * p] = divisor_count[i] / (cnt_exp[i] + 1) * (cnt_exp[i * p] + 1);

                    break;
                } else {
                    distinct_factors_count[i * p] = distinct_factors_count[i] + 1;

                    cnt_exp[i * p] = 1;
                    divisor_count[i * p] = divisor_count[i] * 2;
                }
            }
        }
    }

    [[nodiscard]] bool is_prime(int x) const {
        if (x <= 1 || x > N)
            return false;
        return !is_not_prime[x];
    }
} sieve;

class Solution {
public:
    int findValidSplit(vector<int> &nums) {
        int n = SZ(nums);
        int mx = ranges::max(nums);
        vi last(mx + 1, -1);

        F(i, 0, n - 1) {
            int x = nums[i];
            while (x > 1) {
                int p = sieve.min_prime_factor[x];
                last[p] = i;
                while (x % p == 0)
                    x /= p;
            }
        }

        int R = 0;
        F(i, 0, n - 2) {
            int x = nums[i];
            while (x > 1) {
                int p = sieve.min_prime_factor[x];
                R = max(R, last[p]);
                while (x % p == 0)
                    x /= p;
            }

            if (R == i) {
                return i;
            }
        }

        return -1;
    }
};

// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     Solution sol;
// }
