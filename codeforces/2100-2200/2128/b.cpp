#include <bits/stdc++.h>
#include <vector>
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
    vector<int> p(n);
    For(i, n) cin >> p[i];

    string s;
    int left = 0;
    int right = n - 1;
    while (left <= right) {
        if (s.size() & 1) {
            if (p[left] > p[right]) {
                s += 'L';
                left++;
            } else {
                s += 'R';
                right--;
            }
        } else {
            if (p[left] < p[right]) {
                s += 'L';
                left++;
            } else {
                s += 'R';
                right--;
            }
        }
    }
    cout << s << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
