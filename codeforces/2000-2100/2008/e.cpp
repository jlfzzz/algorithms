#include <bits/stdc++.h>
#include <vector>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define fori(n) for (int i = 0; i < (n); ++i)
#define ford(n) for (int i = (n) - 1; i >= 0; --i)
constexpr int MOD = int(1e9 + 7);

void init() {}

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;

    if (n & 1) {
        // 奇数长度
        vector<int> tot1(26, 0), tot2(26, 0); // 后缀
        vector<int> cnt1(26, 0), cnt2(26, 0); // 前缀

        int ans = n;

        for (int i = 0; i < n; i++) {
            if (i % 2 == 0)
                tot1[s[i] - 'a']++;
            else
                tot2[s[i] - 'a']++;
        }

        for (int i = 0; i < n; i++) {
            int maxa = 0, maxb = 0;
            if (i % 2 == 1) {
                // 删除奇数位，右侧奇偶交换
                tot2[s[i] - 'a']--;

                for (int j = 0; j < 26; j++) {
                    maxa = max(maxa, cnt2[j] + tot1[j]); // cnt2变奇 + tot1变奇
                    maxb = max(maxb, cnt1[j] + tot2[j]); // cnt1变偶 + tot2变偶
                }

                cnt2[s[i] - 'a']++;
            } else {
                // 删除偶数位，右侧奇偶不变
                tot1[s[i] - 'a']--;

                for (int j = 0; j < 26; j++) {
                    maxa = max(maxa, cnt1[j] + tot2[j]); // 奇数位
                    maxb = max(maxb, cnt2[j] + tot1[j]); // 偶数位
                }

                cnt1[s[i] - 'a']++;
            }

            ans = min(ans, n - maxa - maxb);
        }

        cout << ans << '\n';
    } else {
        // 偶数长度
        vector<int> mx1(26, 0);
        vector<int> mx2(26, 0);

        for (int i = 0; i < n; i++) {
            if (i % 2 == 0)
                mx1[s[i] - 'a']++;
            else
                mx2[s[i] - 'a']++;
        }

        int maxa = *max_element(mx1.begin(), mx1.end());
        int maxb = *max_element(mx2.begin(), mx2.end());
        cout << (n - maxa - maxb) << '\n';
    }
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
