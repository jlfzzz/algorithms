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
    vector<int> a(n);
    for (int &x: a)
        cin >> x;

    int count = 0;
    for (int i = 0; i < n; ++i) {
        int next = (i + 1) % n;
        if (a[i] == 1 && a[next] == 0)
            count++;
    }

    cout << (count <= 1 ? "YES\n" : "NO\n");
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
