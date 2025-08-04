#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);

void init() {}

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;

    for (int period = 1; period <= n; period++) {
        if (n % period == 0) {
            int mismatches = 0;

            // 对于每个周期位置，找到出现最多的字符
            for (int pos = 0; pos < period; pos++) {
                vector<int> count(26, 0);
                int maxCount = 0;
                int totalCount = 0;

                // 统计这个位置上各字符的出现次数
                for (int i = pos; i < n; i += period) {
                    count[s[i] - 'a']++;
                    totalCount++;
                }

                // 找到最大出现次数
                for (int i = 0; i < 26; i++) {
                    maxCount = max(maxCount, count[i]);
                }

                // 需要改变的字符数
                mismatches += totalCount - maxCount;

                if (mismatches > 1)
                    break; // 早期终止
            }

            if (mismatches <= 1) {
                cout << period << '\n';
                return;
            }
        }
    }

    cout << n << '\n';
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
