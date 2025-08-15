#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define int ll
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
const ll MOD2 = 4611686018427387847;
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

int fac[20];

void init() {
    fac[0] = 1;
    for (int i = 1; i < 20; i++) {
        fac[i] = fac[i - 1] * i;
    }
}

void solve() {
    int n, k, s;
    cin >> n >> k >> s;

    vector<int> a(n);
    For(i, n) { cin >> a[i]; }

    auto dfs = [&](this auto &&dfs, int i, int sum, int choose, vector<int> &arr,
                   unordered_map<int, vector<int>> &cnt) -> void {
        if (choose > k || sum > s) {
            return;
        }
        if (i == arr.size()) {
            cnt[sum].push_back(choose);
            return;
        }

        int x = arr[i];
        dfs(i + 1, sum, choose, arr, cnt);
        dfs(i + 1, sum + x, choose, arr, cnt);
        if (x < 20) {
            dfs(i + 1, sum + fac[x], choose + 1, arr, cnt);
        }
    };

    unordered_map<int, vector<int>> cnt1;
    unordered_map<int, vector<int>> cnt2;
    vector<int> left, right;
    for (int i = 0; i < n / 2; i++) {
        left.push_back(a[i]);
    }
    for (int i = n / 2; i < n; i++) {
        right.push_back(a[i]);
    }

    dfs(0, 0, 0, left, cnt1);
    dfs(0, 0, 0, right, cnt2);

    for (auto &pair: cnt2) {
        ranges::sort(pair.second);
    }

    int ans = 0;

    for (auto const &[s1, chooses1]: cnt1) {
        for (int choose1: chooses1) {
            int s2 = s - s1;
            if (cnt2.count(s2)) {
                auto const &chooses2 = cnt2.at(s2);
                int max_choose2 = k - choose1;
                if (max_choose2 >= 0) {
                    auto it = ranges::upper_bound(chooses2, max_choose2);
                    ans += (it - chooses2.begin());
                }
            }
        }
    }
    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    //  cin >> T;
    while (T--)
        solve();
    return 0;
}
