#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
const ll MOD2 = 4611686018427387847;
#define int ll
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

const int N = 2e5 + 5;
vector<int> primes;
int is_prime[N];
int spf[N]; // smallest prime factor

void init() {
    fill(spf, spf + N, 0);
    is_prime[0] = is_prime[1] = 1;

    for (int i = 2; i < N; i++) {
        if (!is_prime[i]) {
            primes.push_back(i);
            spf[i] = i;
        }
        for (int p: primes) {
            if (i * p >= N)
                break;
            is_prime[i * p] = 1;
            spf[i * p] = p;
            if (i % p == 0)
                break;
        }
    }
}

bool is_semiprime(int x) {
    if (x >= N || !is_prime[x])
        return false; // x is not composite or out of range

    int p1 = spf[x];
    int remaining = x / p1;

    // Check if remaining is prime (can be same as p1)
    return (remaining < N && !is_prime[remaining]);
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    unordered_map<int, int> prime_cnt;
    int prime_total_cnt = 0;
    unordered_map<int, int> semiprime_cnt;
    unordered_map<int, int> semiprime_by_factor;
    int ans = 0;

    for (int i = 0; i < n; i++) {
        int x = a[i];

        if (x < N && !is_prime[x]) { // x is prime
            // Count pairs with existing semiprimes
            ans += semiprime_by_factor[x];

            // Count pairs with existing primes
            ans += prime_total_cnt - prime_cnt[x];

            prime_total_cnt++;
            prime_cnt[x]++;

        } else if (is_semiprime(x)) { // x is semiprime
            // Count pairs with existing semiprimes of same value
            ans += semiprime_cnt[x] + 1;

            // Count pairs with existing primes that divide x
            int p1 = spf[x];
            int p2 = x / p1;
            if (p1 == p2) {
                // Same prime factor (like 4=2*2, 9=3*3)
                ans += prime_cnt[p1];
            } else {
                // Different prime factors
                ans += prime_cnt[p1] + prime_cnt[p2];
            }
            semiprime_by_factor[p1]++;
            if (p1 != p2) {
                semiprime_by_factor[p2]++;
            }

            semiprime_cnt[x]++;
        }
    }

    cout << ans << '\n';
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




// const int MAXN = 200005;

// int factor_count[MAXN];            // 每个数的不同质因子数量（最多记录到 2）
// vector<int> prime_factors[MAXN];   // prime_factors[x] 存储 x 的质因子（最多 2 个）

// // 筛选出每个数的质因子数量（只处理质因子个数 ≤ 2 的数）
// void preprocess(int n) {
// 	for (int i = 2; i <= n; i++) {
// 		if (!factor_count[i]) { // i 是质数
// 			for (long long j = 1; j * i <= n; j++) {
// 				int x = i * j;
// 				while (x % i == 0 && factor_count[i * j] != 3) {
// 					factor_count[i * j]++;
// 					x /= i;
// 				}
// 				prime_factors[i * j].push_back(i);
// 			}
// 		}
// 	}
// }

// int a[MAXN];       // 输入数组
// int freq[MAXN];    // freq[x] 表示 x 的出现次数

// void solve() {
// 	memset(freq, 0, sizeof(freq));

// 	int n;
// 	cin >> n;

// 	for (int i = 1; i <= n; i++) {
// 		cin >> a[i];
// 		freq[a[i]]++;
// 		if (factor_count[a[i]] == 1) {
// 			freq[0]++; // freq[0] 用来存所有质数的出现总次数
// 		}
// 	}

// 	int total = 0;
// 	int cross_prime = 0;

// 	for (int i = 1; i <= n; i++) {
// 		if (factor_count[i] == 2) {
// 			// 情况3：两个相同半质数的组合 + 单个半质数算一个
// 			total += freq[i] * (freq[i] - 1) / 2;  // (i, i)
// 			// 因为题目说索引对i和j可以相等，所以加上单个的
// 			total += freq[i];                     // 单个半质数
// 			total += freq[i] * freq[prime_factors[i][0]];  // 半质数和它的质因子之一
// 			if (prime_factors[i].size() > 1) {
// 				total += freq[i] * freq[prime_factors[i][1]];
// 			}
// 		} else if (factor_count[i] == 1) {
// 			// 情况1：两个不同质数的组合
// 			cross_prime += freq[i] * (freq[0] - freq[i]);
// 		}
// 	}

// 	cout << total + cross_prime / 2 << "\n";
// }

// signed main() {
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr);

// 	preprocess(200000);

// 	int t;
// 	cin >> t;
// 	while (t--) {
// 		solve();
// 	}

// 	return 0;
// }
