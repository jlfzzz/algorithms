#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, x[200005], y[200005];
multiset<int> sx, sy;
signed main() {
    int T;
    cin >> T;
    while (T--) {
        sx.clear(), sy.clear(); // 别忘记多测清空
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> x[i] >> y[i], sx.insert(x[i]), sy.insert(y[i]);
        if (n == 1) { // 特判，否则 multiset 会为空
            puts("1");
            continue;
        }
        int ans = (*sx.rbegin() - *sx.begin() + 1) * (*sy.rbegin() - *sy.begin() + 1); // 记得处理不删点
        for (int i = 1; i <= n; i++) {
            sx.erase(sx.find(x[i])), sy.erase(sy.find(y[i])); // 一定要删点的下标，否则集合会删除所有的与之相同的元素
            ans = min(ans, (*sx.rbegin() - *sx.begin() + 1) * (*sy.rbegin() - *sy.begin() + 1));
            if (ans == n - 1)
                ans += min(*sx.rbegin() - *sx.begin(), *sy.rbegin() - *sy.begin()) +
                       1; // 如果矩形已经满了，则需要额外添加一行或一列。
            sx.insert(x[i]), sy.insert(y[i]);
        }
        cout << ans << endl;
    }
    return 0;
}
