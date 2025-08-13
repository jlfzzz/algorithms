#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int a[N];
vector<int> v[N];
void solve() {
    int n, ans = 0;
    cin >> n;
    for (int i = 1; i <= n; i++)
        a[i] = 0;
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        a[x]++, a[y]++;
        v[x].push_back(y);
        v[y].push_back(x);
    }
    multiset<int> s;
    for (int i = 1; i <= n; i++)
        s.insert(a[i]);
    for (int i = 1; i <= n; i++) {
        int sum = 1;
        s.erase(s.find(a[i]));
        for (int y: v[i]) {
            s.erase(s.find(a[y]));
            s.insert(a[y] - 1);
        }
        sum += a[i] - 1;
        sum += *s.rbegin() - 1;
        for (int y: v[i]) {
            s.erase(s.find(a[y] - 1));
            s.insert(a[y]);
        }
        s.insert(a[i]);
        ans = max(ans, sum);
    }
    cout << ans << endl;
    for (int i = 1; i <= n; i++)
        v[i].clear();
}
int main() {
    int T;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
