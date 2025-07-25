#include <bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN = 200005;

int factor_count[MAXN];            // 每个数的不同质因子数量（最多记录到 2）
vector<int> prime_factors[MAXN];   // prime_factors[x] 存储 x 的质因子（最多 2 个）

// 筛选出每个数的质因子数量（只处理质因子个数 ≤ 2 的数）
void preprocess(int n) {
	for (int i = 2; i <= n; i++) {
		if (!factor_count[i]) { // i 是质数
			for (long long j = 1; j * i <= n; j++) {
				int x = i * j;
				while (x % i == 0 && factor_count[i * j] != 3) {
					factor_count[i * j]++;
					x /= i;
				}
				prime_factors[i * j].push_back(i);
			}
		}
	}
}

int a[MAXN];       // 输入数组
int freq[MAXN];    // freq[x] 表示 x 的出现次数

void solve() {
	memset(freq, 0, sizeof(freq));

	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		freq[a[i]]++;
		if (factor_count[a[i]] == 1) {
			freq[0]++; // freq[0] 用来存所有质数的出现总次数
		}
	}

	int total = 0;
	int cross_prime = 0;

	for (int i = 1; i <= n; i++) {
		if (factor_count[i] == 2) {
			// 情况3：两个相同半质数的组合 + 单个半质数算一个
			total += freq[i] * (freq[i] - 1) / 2;  // (i, i)
			// 因为题目说索引对i和j可以相等，所以加上单个的
			total += freq[i];                     // 单个半质数
			total += freq[i] * freq[prime_factors[i][0]];  // 半质数和它的质因子之一
			if (prime_factors[i].size() > 1) {
				total += freq[i] * freq[prime_factors[i][1]];
			}
		} else if (factor_count[i] == 1) {
			// 情况1：两个不同质数的组合
			cross_prime += freq[i] * (freq[0] - freq[i]);
		}
	}

	cout << total + cross_prime / 2 << "\n";
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	preprocess(200000);

	int t;
	cin >> t;
	while (t--) {
		solve();
	}

	return 0;
}
