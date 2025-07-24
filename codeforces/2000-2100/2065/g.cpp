#include "bits/stdc++.h"
using namespace std;
using ll = long long;

constexpr int N = 2e5 + 50;
bool is_prime[N];
bool is_semiprime[N];
int prime_factor[N];
vector<int> primes;

void init() {
	memset(is_prime, true, sizeof(is_prime));
	memset(prime_factor, 0, sizeof(prime_factor));
	memset(is_semiprime, false, sizeof(is_semiprime));
	is_prime[0] = is_prime[1] = false;

	// 线性筛生成质数
	for (int i = 2; i < N; i++) {
		if (is_prime[i]) {
			primes.push_back(i);
			prime_factor[i] = i;
		}
		for (int p: primes) {
			if (p * i >= N) {
				break;
			}
			is_prime[p * i] = false;
			prime_factor[p * i] = p;
			if (i % p == 0) {
				break;
			}
		}
	}

	// 标记半质数
	int n = primes.size();
	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			long long prod = 1LL * primes[i] * primes[j];
			if (prod >= N) break;
			is_semiprime[prod] = true;
		}
	}
}

void solve() {
	int n;
	cin >> n;
	vector<int> nums(n);
	for (int i = 0; i < n; i++) {
		cin >> nums[i];
	}

	unordered_map<int, int> semiprime_cnt;
	unordered_map<int, int> prime_cnt;
	int total_primes = 0;
	int ans = 0;

	for (int i = 0; i < n; i++) {
		if (is_semiprime[nums[i]]) {
			ans++;
		}
	}

	// 情况1：两个不同质数的组合
	// 情况2：质数与半质数的组合
	// 情况3：两个相同半质数的组合
	for (int i = 0; i < n; i++) {
		int x = nums[i];
		if (is_prime[x]) {
			// 情况1：与前面不同质数的组合
			ans += total_primes - prime_cnt[x];

			// 情况2：与前面半质数的组合（如果当前质数是半质数的因子）
			for (auto &[semi, cnt]: semiprime_cnt) {
				if (semi % x == 0) {
					ans += cnt;
				}
			}

			prime_cnt[x] += 1;
			total_primes += 1;
		} else if (is_semiprime[x]) {
			// 情况3：与前面相同半质数的组合
			ans += semiprime_cnt[x];

			for (auto &[p, cnt]: prime_cnt) {
				if (x % p == 0) {
					ans += cnt;
				}
			}

			semiprime_cnt[x] += 1;
		}
	}

	cout << ans << "\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int t;
	cin >> t;

	init();

	while (t--) {
		solve();
	}

	return 0;
}


// long long T, n;
// long long nums[200005];
// long long prefixPrimeCount[200005];    // sum[]
// long long primeFreq[200005];           // ji[]
// long long semiprimeFreq[200005];       // jib[]
// bool isPrime[200005];                  // ck[]
// long long isSemiprime[200005];         // ck2[]
// long long semiprimeFactor[200005];     // ck3[]
//
// inline bool checkPrime(long long x) {
//     for (long long i = 2; i * i <= x; i++) {
//         if (x % i == 0) return false;
//     }
//     return true;
// }
//
// inline long long checkSemiprime(long long x) {
//     for (long long i = 2; i * i <= x; i++) {
//         if (x % i == 0 && (!isPrime[i] || !isPrime[x / i])) return -1;
//     }
//     return 1;
// }
//
// inline long long getSmallestPrimeFactor(long long x) {
//     for (long long i = 2; i * i <= x; i++) {
//         if (x % i == 0) return i;
//     }
//     return 0;
// }
//
// int main() {
//     // 初始化质数与半质数信息
//     for (long long i = 1; i <= 200000; i++) {
//         isPrime[i] = checkPrime(i);
//     }
//     for (long long i = 1; i <= 200000; i++) {
//         if (!isPrime[i]) {
//             isSemiprime[i] = checkSemiprime(i);
//             semiprimeFactor[i] = getSmallestPrimeFactor(i);
//         }
//     }
//
//     scanf("%lld", &T);
//     while (T--) {
//         long long answer = 0;
//         scanf("%lld", &n);
//
//         for (long long i = 1; i <= n; i++) {
//             prefixPrimeCount[i] = 0;
//             primeFreq[i] = 0;
//             semiprimeFreq[i] = 0;
//             scanf("%lld", &nums[i]);
//         }
//
//         for (long long i = 1; i <= n; i++) {
//             // 当前是prime。加前面[i-1]里面的prime数量减去当前的出现次数
//             if (isPrime[nums[i]]) {
//                 answer += (prefixPrimeCount[i - 1] - primeFreq[nums[i]]);
//                 primeFreq[nums[i]]++;
//             }
//             prefixPrimeCount[i] = prefixPrimeCount[i - 1] + isPrime[nums[i]];
//
//             // 当前是半质数，两个半质数相组合
//             // 半质数与自身组合
//             if (isSemiprime[nums[i]] == 1) {
//                 semiprimeFreq[nums[i]]++;
//                 answer += semiprimeFreq[nums[i]];
//             }
//         }
//
//         for (long long i = 1; i <= n; i++) {
//             if (isSemiprime[nums[i]] == 1) {
//                 long long p = semiprimeFactor[nums[i]];
//                 answer += primeFreq[p] + primeFreq[nums[i] / p];
//                 if (p * p == nums[i]) answer -= primeFreq[p];
//             }
//         }
//
//         printf("%lld\n", answer);
//     }
// }
