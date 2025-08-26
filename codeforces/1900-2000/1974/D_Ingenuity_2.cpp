#include <bits/stdc++.h>
using namespace std;

int t, n, x, y;
string s;

void solve() {
    cin >> n >> s;
    vector<int> a(n), b(5);
    for (int i = 0; i < n; i++) {
        a[i] = "NESW"s.find(s[i]); // 操作转换为整数
        b[a[i]]++;
    }

    x = b[1] - b[3], y = b[0] - b[2];
    if (x % 2 || y % 2 || (x == 0 && y == 0 && n < 3)) { // 不可能
        cout << "NO\n";
        return;
    }

    for (int i = 0; i < n; i++) { // 输出
        cout << "HR"[(a[i] + b[a[i]]++) % 2]; // 奇偶
    }
    cout << '\n';
}

int main() {
    cin >> t;
    while (t--)
        solve();
    return 0;
}
