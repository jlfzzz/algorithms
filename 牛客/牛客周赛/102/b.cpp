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
    int first, second, third;
    int i = 0;
    while (i < n) {
        if (s[i] == '1') {
            first = i;
            break;
        }
        i++;
    }
    i++;
    while (i < n) {
        if (s[i] == '1') {
            second = i;
            break;
        }
        i++;
    }
    i++;
    while (i < n) {
        if (s[i] == '1') {
            third = i;
            break;
        }
        i++;
    }
    if (third - second == second - first) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
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
