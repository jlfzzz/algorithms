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
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    For(i, n) { cin >> a[i]; }

    int lo = 0, ans = 0, hi = 2e5 + 5;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;

        auto check = [&](int target) -> bool {
            int cnt = 0;
            unordered_set<int> st;
            for (int i = 0; i < n; i++) {
                int x = a[i];
                if (x < target) {
                    st.insert(x);
                }

                if (st.size() == target) {
                    st.clear();
                    cnt++;
                }
            }
            return cnt >= k;
        };

        if (check(mid)) {
            ans = mid;
            lo = mid + 1;
        } else {
            hi = mid;
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






// void solve() {
// 	int n, k;
// 	cin >> n >> k;
// 	vector<int> a(n);
// 	for (int i = 0; i < n; i++) cin >> a[i];

// 	int lo = 0;
// 	int hi = n + 1;
// 	int ans = INT_MAX;

// 	while (lo < hi) {
// 		int mid = lo + (hi - lo) / 2;

// 		auto check = [&](int target)-> bool {
// 			int cnt = 0;
// 			unordered_set<int> st;
// 			for (int i = 0; i < n; i++) {
// 				int x = a[i];
// 				//if (x == target) return false;
// 				if (x < target) st.insert(x);
// 				if (st.size() == target) {
// 					st.clear();
// 					cnt += 1;
// 				}
// 			}
// 			if (st.size() == target) {
// 				cnt += 1;
// 			}
// 			return cnt >= k;
// 		};
// 		if (check(mid)) {
// 			ans = mid;
// 			lo = mid + 1;
// 		} else {
// 			hi = mid;
// 		}
// 	}
// 	cout << (ans == INT_MAX ? 0 : ans) << '\n';
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
