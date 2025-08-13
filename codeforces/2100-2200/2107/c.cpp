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
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 6;

void init() {}

void solve() {
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    s = '0' + s;
    vector<int> a(n + 1);
    For(i, n) { cin >> a[i + 1]; }

    int i = 1;
    while (i <= n) {
        if (s[i] == '0') {
            i++;
            continue;
        }
        int j = i;
        int mx = 0;
        int sm = 0;
        while (j <= n and s[j] == '1') {
            sm = max(sm + a[j], a[j]);
            mx = max(mx, sm);
            j++;
        }
        if (mx > k) {
            cout << "NO\n";
            return;
        }
        i = j;
    }

    int pos = -1;
    for (int i = n; i >= 1; i--) {
        if (s[i] == '0') {
            pos = i;
            break;
        }
    }

    // cout << pos << '\n';
    if (pos == -1) {
        int mx = 0;
        int sm = 0;
        for (int i = 1; i <= n; i++) {
            sm = max(sm + a[i], a[i]);
            mx = max(mx, sm);
        }

        // cout << mx << '\n';
        // cout << k << '\n';
        if (mx != k) {
            cout << "NO\n";
            return;
        } else {
            cout << "YES\n";
            for (int i = 1; i <= n; i++) {
                cout << a[i] << ' ';
            }
            cout << '\n';
            return;
        }
    }

    for (int i = 1; i < pos; i++) {
        if (s[i] == '0') {
            a[i] = -inf;
        }
    }

    if (pos != -1) {
        int left_mx = 0, right_mx = 0;
        int sm = 0;
        for (int i = pos - 1; i >= 1; i--) {
            int x = a[i];
            if (x == -inf) {
                break;
            }
            sm += x;
            left_mx = max(left_mx, sm);
        }

        sm = 0;
        for (int i = pos + 1; i <= n; i++) {

            int x = a[i];
            // cout << x << endl;
            if (x == -inf) {
                break;
            }
            sm += x;
            // cout << sm << endl;
            right_mx = max(right_mx, sm);
        }

        // cout << left_mx << endl;
        // cout << right_mx << endl;
        a[pos] = k - left_mx - right_mx;
    }

    cout << "YES\n";
    for (int i = 1; i <= n; i++) {
        cout << a[i] << ' ';
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





// int main() {
// 	int t;
// 	cin >> t;
// 	while (t--) {
// 		int n;
// 		long long k;
// 		cin >> n >> k;
// 		string s;
// 		cin >> s;
// 		vector<long long> a(n);
// 		for (auto &x: a) cin >> x;

// 		int pos = -1;
// 		for (int i = 0; i < n; i++) {
// 			if (s[i] == '0') {
// 				pos = i;
// 				a[i] = -1e13;
// 			}
// 		}

// 		long long mx = 0;
// 		long long curr = 0;
// 		for (int i = 0; i < n; i++) {
// 			curr = max(curr + a[i], a[i]);
// 			mx = max(mx, curr);
// 		}
// 		if (mx > k || (mx != k && pos == -1)) {
// 			cout << "No\n";
// 			continue;
// 		}
// 		if (pos != -1) {
// 			mx = 0, curr = 0;
// 			long long L, R;

// 			for (int i = pos + 1; i < n; i++) {
// 				curr += a[i];
// 				mx = max(mx, curr);
// 			}
// 			L = mx;
// 			mx = 0;
// 			curr = 0;
// 			for (int i = pos - 1; i >= 0; i--) {
// 				curr += a[i];
// 				mx = max(mx, curr);
// 			}
// 			R = mx;

// 			a[pos] = k - L - R;
// 		}

// 		cout << "Yes\n";
// 		for (int i = 0; i < n; i++) {
// 			cout << a[i] << " \n"[i + 1 == n];
// 		}
// 	}
// 	return 0;
// }
