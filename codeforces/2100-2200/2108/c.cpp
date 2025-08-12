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
    vector<int> a(n);
    For(i, n) { cin >> a[i]; }
    a.push_back(-inf);
    a.insert(a.begin(), -inf);
    int ans = 0;

    int i = 1;
    while (i <= n) {
        int curr = a[i];
        int j = i + 1;
        while (a[j] == a[i]) {
            j++;
        }

        if (curr > a[i - 1] and curr > a[j]) {
            ans++;
        }
        i = j;
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






// void solve() {
// 	int n;
// 	cin >> n;
// 	vector<int> a(n);
// 	for (int i = 0; i < n; i++) cin >> a[i];

// 	a.erase(unique(a.begin(), a.end()), a.end());

// 	int ans = 0;
// 	n = a.size();
// 	if (n == 1) ans = 1;
// 	if (n > 1 and a[0] > a[1]) {
// 		ans++;
// 	}

// 	if (n > 1 and a[n - 1] > a[n - 2]) {
// 		ans++;
// 	}
// 	for (int i = 1; i < n - 1; i++) {
// 		if (a[i] > a[i - 1] and a[i] > a[i + 1]) {
// 			ans++;
// 		}
// 	}
// 	cout << ans << '\n';
// }

// void solve2() {
// 	int n;
// 	cin >> n;
// 	vector<int> a(n);
// 	for (int i = 0; i < n; i++) cin >> a[i];

// 	int ans = 0;
// 	int i = 0;
// 	while (i < n) {
// 		int j = i + 1;
// 		while (j < n and a[j] >= a[j - 1]) {
// 			j += 1;
// 		}
// 		i = j;
// 		while (i < n and a[i] <= a[i - 1]) {
// 			i += 1;
// 		}
// 		ans++;
// 	}
// 	cout << ans << '\n';
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
