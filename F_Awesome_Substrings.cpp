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
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

void solve() {
    string s;
    cin >> s;
    int n = s.size();
    vector<int> pref(n + 1, 0);
    vector<int> pos;
    for (int i = 0; i < n; ++i) {
        pref[i + 1] = pref[i] + (s[i] == '1');
        if (s[i] == '1')
            pos.push_back(i);
    }
    int m = pos.size();
    int B = floor(sqrt((long double) n));
    if (B < 1)
        B = 1;
    long long ans = 0;
    int T = (int) (n / B);
    for (int t = 1; t <= T; ++t) {
        unordered_map<long long, int> cnt;
        cnt.reserve((size_t) (n * 2 + 10));
        cnt.max_load_factor(0.7f);
        for (int i = 0; i <= n; ++i) {
            long long key = (long long) i - (long long) t * (long long) pref[i];
            auto it = cnt.find(key);
            if (it != cnt.end()) {
                ans += it->second;
                ++(it->second);
            } else {
                cnt.emplace(key, 1);
            }
        }
    }
    if (m > 0) {
        for (int one = 1; one < B; one++) {
            int left = 0;
            int window = 0;

            for (int right = 0; right < n; right++) {
                if (s[right] == '1') {
                    window++;
                }

                if (window < one) {
                    continue;
                }


                int left_idx = pos[left];
                int len1 = right - left_idx + 1;
                int len2 = 0;
                if (left_idx > 0) {
                    int left_left = left_idx - 1;
                    int i = pos[left_left];
                    int zeros = pos[left_idx] - i - 1;
                    len2 += zeros;
                }
                if (left + one < pos.size()) {
                    int right_idx = pos[left + one];
                    int zeros = right_idx - right - 1;
                    len2 += zeros;
                }

                int contrib = len1 / one;
                int extra = len1 % one;
                len2 += extra;
                contrib += len2 / one;
                ans += contrib;

                window--;
                left++;
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
    cin >> T;
    while (T--)
        solve();
    return 0;
}
