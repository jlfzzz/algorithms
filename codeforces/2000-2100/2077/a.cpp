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

void init() {}

void solve() {
    int n;
    cin >> n;
    vector<int> b(2 * n);
    For(i, 2 * n) cin >> b[i];

    ranges::sort(b);
    ranges::reverse(b);
    int sum = 0;
    for (int i = 0; i < n + 1; i++) {
        sum += b[i];
    }
    int sum2 = 0;
    for (int i = n + 1; i < 2 * n; i++) {
        sum2 += b[i];
    }

    int t = sum - sum2;
    cout << b[0] << ' ';
    vector<int> t1(n);
    for (int i = 0; i < n; i++) {
        t1[i] = b[i + 1];
    }
    vector<int> t2(n);
    for (int i = 0; i < n - 1; i++) {
        t2[i] = b[i + n + 1];
    }
    t2[n - 1] = t;
    for (int i = 0; i < 2 * n; i++) {
        if (i & 1) {
            cout << t1[i / 2] << ' ';
        } else {
            cout << t2[i / 2] << ' ';
        }
    }
    cout << '\n';
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






// void solve() {
// 	int n;
// 	cin >> n;

// 	vector<i64> b(2 * n);  // 输入数组 b，长度 2n
// 	for (i64 &x : b) cin >> x;

// 	sort(b.begin(), b.end());  // 升序排列

// 	i64 odd_sum = 0, even_sum = 0;

// 	// 交换相邻位置，使较大值在奇数位（1-based），较小值在偶数位
// 	for (int i = 0; i < 2 * n; i += 2) {
// 		swap(b[i], b[i + 1]);  // b[i] → 奇数位，大数；b[i+1] → 偶数位，小数
// 		odd_sum += b[i];       // 奇数位累加（a1, a3, a5, ...）
// 		even_sum += b[i + 1];  // 偶数位累加（a2, a4, a6, ...）
// 	}

// 	// 最后一个值将作为 a_{2n+1}，加入奇数和，并从偶数和中移除
// 	i64 last_value = b.back();
// 	odd_sum += last_value;
// 	even_sum -= last_value;

// 	i64 a_2n = odd_sum - even_sum;  // 公式：a_{2n} = sum(odd) - sum(even)

// 	b.push_back(a_2n);  // 加入 a_{2n} 到最后
// 	swap(b[2 * n], b[2 * n - 1]);  // 将 a_{2n} 放到正确位置（倒数第二位）

// 	for (i64 x : b) cout << x << ' ';
// 	cout << '\n';
// }

// int main() {
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr);

// 	int t;
// 	cin >> t;
// 	while (t--) solve();
// }
