#include <cstdio>
#include <iostream>
#define il inline
#define ll long long
#define pii pair<int, int>
#define mp make_pair
#define st first
#define nd second
using namespace std;
const int N = 2e5 + 5;
int n;
ll a[N], b[N], c[N], tot;
pii ans[3 + 5];
il bool check(ll *a, ll *b, ll *c, int o1, int o2, int o3) {
    int l = 0, r = n + 1;
    ll sa = 0, sb = 0, sc = 0; // 不要在意这个变量名
    while (sa < tot)
        sa += a[++l];
    while (sc < tot)
        sc += c[--r];
    ++l, --r;
    for (int i = l; i <= r; ++i)
        sb += b[i];
    if (sb < tot)
        return 0;
    ans[1].st = 1, ans[1].nd = l - 1;
    ans[2].st = l, ans[2].nd = r;
    ans[3].st = r + 1, ans[3].nd = n;
    cout << ans[o1].st << ' ' << ans[o1].nd << ' ';
    cout << ans[o2].st << ' ' << ans[o2].nd << ' ';
    cout << ans[o3].st << ' ' << ans[o3].nd << '\n';
    return 1;
}
il void solve() {
    cin >> n;
    tot = 0;
    for (int i = 1; i <= n; ++i)
        cin >> a[i], tot += a[i];
    for (int i = 1; i <= n; ++i)
        cin >> b[i];
    for (int i = 1; i <= n; ++i)
        cin >> c[i];
    tot = (tot + 2) / 3;
    if (check(a, b, c, 1, 2, 3))
        return;
    if (check(a, c, b, 1, 3, 2))
        return;
    if (check(b, a, c, 2, 1, 3))
        return;
    if (check(b, c, a, 3, 1, 2))
        return;
    if (check(c, a, b, 2, 3, 1))
        return;
    if (check(c, b, a, 3, 2, 1))
        return;
    cout << "-1\n";
    return;
}
int main() {
    ios::sync_with_stdio(0);
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int T;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
