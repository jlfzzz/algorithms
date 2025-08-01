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
    int n;
    cin >> n;
    string s;
    cin >> s;

    ll ans = 0;
    deque<int> q; // 双端队列存储可以享受折扣的物品

    // 从右往左遍历（从最贵到最便宜）
    for (int i = n - 1; i >= 0; i--) {
        if (s[i] == '1') {
            // 这天会去商店，物品可以享受折扣
            q.push_back(i + 1);
        } else {
            // 这天不去商店，物品必须在其他天购买
            // 如果有可以享受折扣的物品，让最贵的免费
            if (!q.empty()) {
                q.pop_front(); // 弹出最贵的（免费获得）
            }
            ans += i + 1; // 购买这天的物品
        }
    }

    // 处理剩余的物品（都是'1'对应的天数）
    // 使用贪心：最贵的和最便宜的配对
    while (!q.empty()) {
        ans += q.back(); // 买最便宜的
        q.pop_back();
        if (!q.empty()) {
            q.pop_front(); // 最贵的免费
        }
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
