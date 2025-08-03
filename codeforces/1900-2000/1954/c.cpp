#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);

void init() {}

void solve() {
    string x, y;
    cin >> x >> y;
    int n = x.size();

    int i = 0;
    while (i < n and x[i] == y[i]) {
        i++;
    }
    if (i == n) {
        cout << x << '\n' << y << '\n';
    } else {
        if (x[i] > y[i]) {
            i++;
            while (i < n) {
                if (x[i] > y[i]) {
                    char t = x[i];
                    x[i] = y[i];
                    y[i] = t;
                }
                i++;
            }
        } else {
            i++;
            while (i < n) {
                if (x[i] < y[i]) {
                    char t = x[i];
                    x[i] = y[i];
                    y[i] = t;
                }
                i++;
            }
        }
        cout << x << '\n' << y << '\n';
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
