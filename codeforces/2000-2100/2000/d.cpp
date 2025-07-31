#include <bits/stdc++.h>
#include <numeric>
#include <vector>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define fori(n) for (int i = 0; i < (n); ++i)
#define ford(n) for (int i = (n) - 1; i >= 0; --i)
constexpr int MOD = int(1e9 + 7);

void init() {}

void solve() {
    int n;
    cin >> n;
    vector<int> nums(n);
    fori(n) { cin >> nums[i]; }

    string s;
    cin >> s;

    int left = 0;

    int right = n - 1;
    ll sum = 0;
    vector<ll> pre(n + 1, 0LL);
    fori(n) { pre[i + 1] = pre[i] + nums[i]; }


    while (left < right) {
        while (left < right) {
            if (s[left] == 'L') {
                break;
            }
            left++;
        }
        while (right > left) {
            if (s[right] == 'R') {
                break;
            }
            right--;
        }
        if (left >= right) {
            break;
        }
        sum += pre[right + 1] - pre[left];
        left++;
        right--;
    }
    cout << sum << '\n';
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
