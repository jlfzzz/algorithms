#include <bits/stdc++.h>
#include <type_traits>
#include <vector>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
constexpr int MOD = int(1e9 + 7);

void init() {}

void solve() {
    int n;
    cin >> n;

    string s1;
    string s2;

    cin >> s1 >> s2;

    vector<vector<bool>> grid(n, vector<bool>(2, false));
    for (int i = 0; i < n; i++) {
        if (s1[i] == '#') {
            grid[i][0] = true;
        }
        if (s2[i] == '#') {
            grid[i][1] = true;
        }
    }

    bool multiple = false;
    for (int i = 0; i < n; i++) {
        if (grid[i][0] and grid[i][1]) {
            continue;
        }

        if (!grid[i][0] and grid[i][1]) {
            if (i + 1 == n or s1[i + 1] == '#') {
                cout << "None\n";
                return;
            }
            grid[i][0] = true;
            grid[i + 1][0] = true;
        } else if (grid[i][0] and !grid[i][1]) {
            if (i + 1 == n or s2[i + 1] == '#') {
                cout << "None\n";
                return;
            }
            grid[i][1] = true;
            grid[i + 1][1] = true;
        } else {
            if (i + 1 < n and s1[i + 1] == '.' and s2[i + 1] == '.') {
                multiple = true;
            }

            if (i + 1 == n) {
                break;
            }

            if (s1[i + 1] == '#' and s2[i + 1] == '#') {
                continue;
            } else if ((s1[i + 1] == '#' and s2[i + 1] == '.') or (s1[i + 1] == '.' and s2[i + 1] == '#')) {
                continue;
            } else {
                multiple = true;
                grid[i + 1][0] = true;
                grid[i + 1][1] = true;
            }
        }
    }

    if (multiple) {
        cout << "Multiple\n";
    } else {
        cout << "Unique\n";
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
