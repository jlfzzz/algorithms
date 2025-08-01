#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define fori(n) for (int i = 0; i < (n); ++i)
#define ford(n) for (int i = (n) - 1; i >= 0; --i)
constexpr int MOD = int(1e9 + 7);

void init() {}

void solve() {
    string a, b;
    cin >> a >> b;

    int n = a.length();
    int m = b.length();
    int ans = n + m; // 最坏情况：a和b完全不重叠

    // 枚举a在最终字符串中的起始位置
    // 这里我们考虑在a之前需要放置多少b的字符
    for (int prefix = 0; prefix <= m; prefix++) {
        // prefix: 在a之前需要匹配的b的字符数量

        // 检查a能够匹配b中从prefix开始的多少字符
        int matched = 0; // 在a中能匹配到的b的字符数
        int b_pos = prefix; // 当前在b中的位置

        // 遍历a的每个字符，看能匹配b的多少字符
        for (int i = 0; i < n && b_pos < m; i++) {
            if (a[i] == b[b_pos]) {
                matched++;
                b_pos++;
            }
        }

        // 计算总长度
        // prefix: a前面需要的字符数
        // n: a的长度
        // (m - prefix - matched): a后面还需要的字符数
        int total_len = prefix + n + (m - prefix - matched);
        ans = min(ans, total_len);
    }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
