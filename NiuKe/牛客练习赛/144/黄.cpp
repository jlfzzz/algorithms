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

// void solve() {
//     string s;
//     cin >> s;
//     vector<int> cnt(26);
//     For(i, 26) cin >> cnt[i];

//     int n = s.size();
//     char first = s[0];
//     int ans = 0;
//     for (int i = first - 'a' + 1; i < 26; i++) {
//         ans += cnt[i];
//         cnt[i] = 0;
//     }

//     int L = 0;
//     int pre = inf;
//     bool can = false;
//     while (L < n) {
//         int R = L;
//         while (R < n && s[R] == s[L])
//             R++;
//         int len = R - L;
//         int c = s[L] - 'a';

//         if (R < n) {
//             int nxt = s[R] - 'a';
//             int have = 0;
//             for (int j = nxt + 1; j < 26; j++)
//                 have += cnt[j];
//             int add = min(pre, have);
//             if (add > 0) {
//                 ans += add;
//                 can = true;
//                 break;
//             }
//         }

//         int need = min(pre, cnt[c] / len);
//         cnt[c] -= need * len;
//         pre = need;
//         L = R;
//     }

//     if (!can) {
//         int s = 0;
//         for (int j = 0; j < 26; j++)
//             s += cnt[j];
//         ans += min(pre, s);
//     }

//     cout << ans << '\n';
// }

void solve() {
    string s;
    cin >> s;
    vector<int> cnt(26);
    For(i, 26) cin >> cnt[i];

    int n = s.size();
    int l = 0;
    int ans = 0;
    int r = accumulate(cnt.begin(), cnt.end(), 0ll) + 1e9;

    auto check = [&](int n) { // 使用给定的字符能否构造出n个字典序严格大于s的字符串
        std::vector<int> ct = cnt;
        for (char c: s) {
            int i = c - 'a';
            for (int j = i + 1; j < 26; ++j) { // 遍历到了新的字符i，先把严格大于i的填下去
                n -= ct[j];
                ct[j] = 0;
            }
            if (n <= 0) { // 严格大于都够了，直接提前返回
                return true;
            }
            if (ct[i] < n) { // 严格大于不够的，就要用i填满，i不够就无解了
                return false;
            }
            ct[i] -= n;
        }
        return accumulate(ct.begin(), ct.end(), 0) >=
               n; // 现在还剩n个完全等于s的，顺便再末尾填个什么字符就可以字典序严格大于s了
    };
    while (l + 1 != r) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }

    std::cout << l << "\n";
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    // cin >> T;
    while (T--)
        solve();
    return 0;
}
