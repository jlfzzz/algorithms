#include <bits/stdc++.h>
#include <vector>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);

void init() {}

int f(const string &s) {
    int cnt = 0;
    for (int i = 0; i < s.length() - 1; i++) {
        if (s[i] != s[i + 1]) {
            cnt++;
        }
    }
    return cnt;
}

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;

    int cnt = f(s);

    if (cnt >= 3) {
        cout << 0 << '\n';
        return;
    }

    if (n == 4) {
        if (cnt == 0) {
            cout << 2 << '\n';
        } else if (cnt == 1) {
            for (int i = 0; i < 3; i++) {
                if (s[i] != s[i + 1]) {
                    if (i == 0 || i == 2) {
                        cout << 1 << '\n';
                    } else {
                        cout << 2 << '\n';
                    }
                    return;
                }
            }
        } else if (cnt == 2) {
            vector<int> pos;
            for (int i = 0; i < 3; i++) {
                if (s[i] != s[i + 1]) {
                    pos.push_back(i);
                }
            }
            if (pos[1] == pos[0] + 1) {
                cout << 1 << '\n';
            } else {
                cout << 2 << '\n';
            }
        }
    } else {
        if (cnt == 0) {
            cout << 2 << '\n';
        } else if (cnt == 1) {
            cout << 1 << '\n';
        } else if (cnt == 2) {
            cout << 1 << '\n';
        }
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
