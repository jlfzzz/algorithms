#include <algorithm>
#include <bits/ranges_algo.h>
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
    int N, Q;
    cin >> N >> Q;

    vector<int> A(N);
    For(i, N) cin >> A[i];

    int mx = ranges::max(A);
    ranges::sort(A);
    vector<int> pre(N + 1);
    for (int i = 1; i <= N; i++) {
        pre[i] = pre[i - 1] + A[i - 1];
    }

    For(i, Q) {
        int difficulty;
        cin >> difficulty;

        if (difficulty > mx) {
            cout << -1 << '\n';
            continue;
        }

        int j = ranges::lower_bound(A, difficulty) - A.begin();

        int ans = pre[j] + difficulty + (difficulty - 1) * (N - j - 1);
        cout << ans << '\n';
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    // cin >> T;
    while (T--)
        solve();
    return 0;
}
