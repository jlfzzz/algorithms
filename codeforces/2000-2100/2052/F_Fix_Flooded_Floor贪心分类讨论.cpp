#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define int ll
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
const ll MOD2 = 4611686018427387847;

void init() {}

void solve() {
    int n;
    cin >> n;
    string a, b;
    cin >> a >> b;
    vector<vector<int>> grid(n, vector<int>(2));
    For(i, n) {
        if (a[i] == '.') {
            grid[i][0] = 1;
        }
        if (b[i] == '.') {
            grid[i][1] = 1;
        }
    }

    bool multiple = false;
    For(i, n) {
        if (!grid[i][0] and !grid[i][1]) {
            continue;
        }

        if (grid[i][0] and grid[i][1] and i + 1 < n and grid[i + 1][0] and grid[i + 1][1]) {
            multiple = true;
            grid[i + 1][0] = grid[i + 1][1] = 0;
            continue;
        }

        if (grid[i][0] and grid[i][1]) {
            continue;
        } else {
            if (grid[i][0]) {
                if (i == n - 1 or !grid[i + 1][0]) {
                    cout << "None\n";
                    return;
                }

                grid[i + 1][0] = 0;
            } else {
                if (i == n - 1 or !grid[i + 1][1]) {
                    cout << "None\n";
                    return;
                }

                grid[i + 1][1] = 0;
            }
        }
    }

    if (multiple) {
        cout << "Multiple\n";
    } else {
        cout << "Unique\n";
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
