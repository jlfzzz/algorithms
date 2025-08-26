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
    int n;
    cin >> n;
    string digit = to_string(n);
    int d = digit.size();

    vector<pii> ans;

    for (int a = 1; a <= 10000; a++) {
        int len = a * d; // 总字符串长度
        for (int b = max(1ll, len - 18); b < len; b++) {
            int total_len = len - b;
            if (total_len > 18)
                continue;

            int L = total_len / d;
            int R = total_len % d;

            string s;
            s.reserve(total_len);
            for (int i = 0; i < L; i++)
                s += digit;
            if (R > 0)
                s += digit.substr(0, R);

            if (n * a - b == stoll(s)) {
                ans.emplace_back(a, b);
            }
        }
    }

    cout << ans.size() << '\n';
    for (auto [a, b]: ans) {
        cout << a << ' ' << b << '\n';
    }
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
