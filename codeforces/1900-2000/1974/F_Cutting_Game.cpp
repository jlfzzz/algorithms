#include <bits/stdc++.h>
using namespace std;
int t, n, m, k, kk, a, b, l, r, u, d, x, y, p, sum[2];
char c;
set<pair<int, int>> s1, s2;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> t;
    while (t--) {
        s1.clear(); // 多测清空
        s2.clear();
        cin >> n >> m >> k >> kk;
        for (int i = 1; i <= k; i++) {
            cin >> a >> b;
            s1.insert({a, b});
            s2.insert({b, a}); // 分别以不同的优先级插入set中
        }
        l = u = 1;
        p = sum[0] = sum[1] = 0;
        r = m;
        d = n;
        while (kk--) {
            cin >> c >> a;
            if (c == 'U') {
                while (!s1.empty() && (*s1.begin()).first < u + a) {
                    x = (*s1.begin()).first;
                    y = (*s1.begin()).second;
                    s1.erase({x, y}); // 在两个set中删除元素
                    s2.erase({y, x});
                    sum[p]++; // 将答案加1
                }
                u += a; // 统计删除到哪了
            } else if (c == 'D') {
                while (!s1.empty()) {
                    auto o = prev(s1.end());
                    if ((*o).first <= d - a)
                        break;
                    x = (*o).first;
                    y = (*o).second;
                    s1.erase({x, y});
                    s2.erase({y, x});
                    sum[p]++;
                }
                d -= a;
            } else if (c == 'L') {
                while (!s2.empty() && (*s2.begin()).first < l + a) {
                    x = (*s2.begin()).first;
                    y = (*s2.begin()).second;
                    s1.erase({y, x});
                    s2.erase({x, y});
                    sum[p]++;
                }
                l += a;
            } else {
                while (!s2.empty()) {
                    auto o = prev(s2.end());
                    if ((*o).first <= r - a)
                        break;
                    x = (*o).first;
                    y = (*o).second;
                    s1.erase({y, x});
                    s2.erase({x, y});
                    sum[p]++;
                }
                r -= a;
            }
            p ^= 1; // 变更操作人
        }
        cout << sum[0] << ' ' << sum[1] << '\n'; // 输出答案
    }
    return 0;
}
