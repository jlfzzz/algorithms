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
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    vector<int> b(m + 1);
    For(i, n) { cin >> a[i + 1]; }
    For(i, m) cin >> b[i + 1];

    vector<int> pre(m + 2, inf);
    vector<int> suf(m + 2, -inf);
    pre[0] = -inf;
    suf[m + 1] = inf;

    int j = 1;
    For(i, n) {
        if (a[i + 1] >= b[j]) {
            pre[j] = i + 1;
            j++;
        }
        if (j > m) {
            cout << 0 << '\n';
            return;
        }
    }


    j = m;
    for (int i = n; i >= 1; i--) {
        if (a[i] >= b[j]) {
            suf[j] = i;
            j--;
        }
        if (j < 1) {
            cout << 0 << '\n';
            return;
        }
    }


    int ans = inf;
    for (int i = 1; i <= m; i++) {
        int curr = b[i];
        if (pre[i - 1] < suf[i + 1]) {
            ans = min(ans, curr);
        }
    }
    if (ans == inf) {
        ans = -1;
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





// constexpr int INF = 1e9 + 5;

// void solve() {
// 	int n, m;
// 	cin >> n >> m;
// 	vector<int> a(n);
// 	for (int i = 0; i < n; i++) {
// 		cin >> a[i];
// 	}
// 	vector<int> b(m);
// 	for (int i = 0; i < m; i++) {
// 		cin >> b[i];
// 	}

// 	vector<int> backwards(n + 1, 0);
// 	int j = m - 1;
// 	for (int i = n - 1; i >= 0; i--) {
// 		backwards[i] = backwards[i + 1];
// 		if (j >= 0 && a[i] >= b[j]) {
// 			backwards[i] += 1;
// 			j--;
// 		}
// 	}
// 	if (backwards[0] == m) {
// 		cout << 0 << endl;
// 		return;
// 	}
// 	vector<int> forwards(n + 1, 0);
// 	j = 0;
// 	for (int i = 0; i < n; i++) {
// 		forwards[i + 1] = forwards[i];
// 		if (j < m && a[i] >= b[j]) {
// 			forwards[i + 1] += 1;
// 			j += 1;
// 		}
// 	}
// 	if (forwards.back() == m) {
// 		cout << 0 << endl;
// 		return;
// 	}

// 	int ans = INF;
// 	for (int i = 0; i <= n; i++) {
// 		int prev = forwards[i];        // 前缀匹配数量
// 		int back = backwards[i];       // 后缀匹配数量

// 		// 检查插入一朵花后是否能完成任务
// 		if (prev + back >= m - 1) {
// 			// 新插入的花需要满足第(prev+1)个要求，即b[prev]
// 			// if (prev < m) {
// 			// 	ans = min(ans, b[prev]);
// 			// }
// 			ans = min(ans, b[prev]);
// 		}
// 	}
// 	cout << (ans == INF ? -1 : ans) << endl;
// }


// int main() {
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr);
// 	cout.tie(nullptr);
// 	int t;
// 	cin >> t;
// 	while (t--) {
// 		solve();
// 	}
// }
